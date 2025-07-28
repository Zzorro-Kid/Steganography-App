#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <functional>
#include "Stenographer.h"

std::vector<bool> message_to_binary(const std::string& message) {
    std::vector<bool> binary;
    for (unsigned char c : message)
        for (int i = 7; i >= 0; --i)
            binary.push_back((c >> i) & 1);
    for (int i = 0; i < 8; ++i) binary.push_back(false);
    return binary;
}
std::string binary_to_message(const std::vector<bool>& bits) {
    std::string msg;
    char cur = 0;
    for (size_t i = 0; i < bits.size(); ++i) {
        cur = (cur << 1) | bits[i];
        if (i % 8 == 7) {
            if (cur == '\0') break;
            msg += cur;
            cur = 0;
        }
    }
    return msg;
}
bool is_bmp_24_bit(const std::string& file_path) {
    std::ifstream in(file_path, std::ios::binary);
    if (!in) { std::cerr<<"Cannot open file: "<<file_path<<"\n"; return false; }
    char hdr[54];
    in.read(hdr, 54);
    if (hdr[0]!='B' || hdr[1]!='M') {
        std::cerr<<"Not a BMP.\n"; return false;
    }
    unsigned short bpp = *reinterpret_cast<unsigned short*>(&hdr[28]);
    if (bpp != 24) {
        std::cerr<<"BMP is not 24-bit.\n"; return false;
    }
    return true;
}
static void skip_ws_and_comments(std::ifstream& in) {
    char c;
    while (in >> std::ws && in.peek() == '#') {
        in.get(c);
        while (in.get(c) && c != '\n');
    }
}
bool is_ppm(const std::string& file_path) {
    std::ifstream in(file_path);
    if (!in) { std::cerr<<"Cannot open file: "<<file_path<<"\n"; return false; }
    std::string magic;
    in >> magic;
    if (magic != "P6" && magic != "P3") {
        std::cerr<<"Not a PPM (P3/P6).\n";
        return false;
    }
    return true;
}
static bool embed_binary_ppm(const std::string& file_path, const std::vector<bool>& bits) {
    std::ifstream in(file_path, std::ios::binary);
    if (!in) { std::cerr<<"Cannot open file: "<<file_path<<"\n"; return false; }
    std::vector<unsigned char> data((std::istreambuf_iterator<char>(in)), {});
    in.close();
    size_t pos = 2;
    auto is_ws = [&](unsigned char c){ return c==' '||c=='\n'||c=='\r'||c=='\t'; };
    std::function<std::string()> read_tok = [&]() -> std::string {
        if (pos < data.size() && data[pos] == '#') {
            while (pos < data.size() && data[pos] != '\n') pos++;
            pos++;
            return read_tok();
        }
        while (pos < data.size() && is_ws(data[pos])) pos++;
        size_t s = pos;
        while (pos < data.size() && !is_ws(data[pos])) pos++;
        return std::string(reinterpret_cast<char*>(&data[s]), pos - s);
    };
    read_tok(); read_tok(); read_tok();
    if (pos < data.size() && is_ws(data[pos])) pos++;
    size_t header_end = pos;
    if (data.size() - header_end < bits.size()) {
        std::cerr<<"PPM too small for message.\n";
        return false;
    }
    for (size_t i = 0; i < bits.size(); ++i)
        data[header_end + i] = (data[header_end + i] & 0xFE) | bits[i];
    std::ofstream out(file_path, std::ios::binary);
    if (!out) { std::cerr<<"Cannot write file: "<<file_path<<"\n"; return false; }
    out.write(reinterpret_cast<char*>(data.data()), data.size());
    return true;
}
static std::string decode_binary_ppm(const std::string& file_path) {
    std::ifstream in(file_path, std::ios::binary);
    if (!in) { std::cerr<<"Cannot open file: "<<file_path<<"\n"; return ""; }
    std::vector<unsigned char> data((std::istreambuf_iterator<char>(in)), {});
    in.close();
    size_t pos = 2;
    auto is_ws = [&](unsigned char c){ return c==' '||c=='\n'||c=='\r'||c=='\t'; };
    std::function<std::string()> read_tok = [&]() -> std::string {
        if (pos < data.size() && data[pos] == '#') {
            while (pos < data.size() && data[pos] != '\n') pos++;
            pos++;
            return read_tok();
        }
        while (pos < data.size() && is_ws(data[pos])) pos++;
        size_t s = pos;
        while (pos < data.size() && !is_ws(data[pos])) pos++;
        return std::string(reinterpret_cast<char*>(&data[s]), pos - s);
    };
    read_tok(); read_tok(); read_tok();
    if (pos < data.size() && is_ws(data[pos])) pos++;
    std::vector<bool> bits;
    bits.reserve(data.size() - pos);
    for (size_t i = pos; i < data.size(); ++i)
        bits.push_back(data[i] & 1);
    return binary_to_message(bits);
}
static bool embed_ascii_ppm(const std::string& file_path, const std::vector<bool>& bits) {
    std::ifstream in(file_path);
    if (!in) { std::cerr<<"Cannot open file: "<<file_path<<"\n"; return false; }
    std::string magic;
    in >> magic;
    if (magic != "P3") { std::cerr<<"Not a P3 PPM.\n"; return false; }
    skip_ws_and_comments(in);
    int w,h,maxv;
    in >> w; skip_ws_and_comments(in);
    in >> h; skip_ws_and_comments(in);
    in >> maxv;
    std::vector<int> pix;
    pix.reserve(w*h*3);
    for (int v, cnt=w*h*3; cnt-- && (in>>v); )
        pix.push_back(v);
    if (pix.size() < bits.size()) {
        std::cerr<<"PPM too small for message.\n";
        return false;
    }
    for (size_t i = 0; i < bits.size(); ++i)
        pix[i] = (pix[i] & ~1) | bits[i];
    std::ofstream out(file_path);
    if (!out) { std::cerr<<"Cannot write file: "<<file_path<<"\n"; return false; }
    out<<"P3\n"<<w<<" "<<h<<"\n"<<maxv<<"\n";
    for (size_t i = 0; i < pix.size(); ++i) {
        out<<pix[i]<<((i%12==11) ? "\n" : " ");
    }
    out<<"\n";
    return true;
}
static std::string decode_ascii_ppm(const std::string& file_path) {
    std::ifstream in(file_path);
    if (!in) { std::cerr<<"Cannot open file: "<<file_path<<"\n"; return ""; }
    std::string magic;
    in >> magic;
    if (magic != "P3") { std::cerr<<"Not a P3 PPM.\n"; return ""; }
    skip_ws_and_comments(in);
    int w,h,maxv;
    in >> w; skip_ws_and_comments(in);
    in >> h; skip_ws_and_comments(in);
    in >> maxv;
    std::vector<bool> bits;
    for (int v; in>>v; )
        bits.push_back(v & 1);
    return binary_to_message(bits);
}
bool can_embed_message_ppm(const std::string& file_path, const std::string& message) {
    std::ifstream in(file_path);
    if (!in) { std::cerr<<"Cannot open file: "<<file_path<<"\n"; return false; }
    std::string magic; in >> magic;
    size_t req = (message.size()+1)*8;
    if (magic == "P6") {
        in.seekg(0, std::ios::end);
        size_t total = in.tellg();
        return (total - 15) >= req;
    }
    if (magic == "P3") {
        skip_ws_and_comments(in);
        int w,h,mx;
        in>>w; skip_ws_and_comments(in);
        in>>h; skip_ws_and_comments(in);
        in>>mx;
        return size_t(w)*h*3 >= req;
    }
    std::cerr<<"Unsupported PPM magic: "<<magic<<"\n";
    return false;
}
bool embed_message_into_ppm(const std::string& file_path, const std::string& message) {
    std::ifstream in(file_path);
    if (!in) { std::cerr<<"Cannot open: "<<file_path<<"\n"; return false; }
    std::string magic; in >> magic; in.close();
    auto bits = message_to_binary(message);
    if (magic == "P6") return embed_binary_ppm(file_path, bits);
    if (magic == "P3") return embed_ascii_ppm (file_path, bits);
    std::cerr<<"Unsupported PPM format: "<<magic<<"\n";
    return false;
}
std::string decode_message_from_ppm(const std::string& file_path) {
    std::ifstream in(file_path);
    if (!in) { std::cerr<<"Cannot open: "<<file_path<<"\n"; return ""; }
    std::string magic; in >> magic; in.close();
    if (magic == "P6") return decode_binary_ppm(file_path);
    if (magic == "P3") return decode_ascii_ppm (file_path);
    std::cerr<<"Unsupported PPM format: "<<magic<<"\n";
    return "";
}
bool embed_message_into_image(const std::string& file_path,
                              const std::string& message) {
    auto pos = file_path.find_last_of('.');
    std::string ext = (pos == std::string::npos)
                      ? ""
                      : file_path.substr(pos + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    auto bits = message_to_binary(message);
    if (ext == "bmp") {
        if (!is_bmp_24_bit(file_path)) {
            std::cerr << "Error: BMP bit depth is not 24-bit\n";
            return false;
        }
        std::ifstream in(file_path, std::ios::binary);
        if (!in) {
            std::cerr << "Error: cannot open file " << file_path << "\n";
            return false;
        }
        std::vector<unsigned char> img(
            std::istreambuf_iterator<char>(in),
            {});
        in.close();
        const size_t HEADER_SIZE = 54;
        if (img.size() <= HEADER_SIZE) {
            std::cerr << "Error: BMP file too small to contain header\n";
            return false;
        }
        size_t pixelBytes = img.size() - HEADER_SIZE;
        if (bits.size() > pixelBytes) {
            std::cerr << "Error: BMP image data too small, need "
                      << bits.size() << " bits but only "
                      << pixelBytes << " available\n";
            return false;
        }
        for (size_t i = 0; i < bits.size(); ++i) {
            img[HEADER_SIZE + i] = (img[HEADER_SIZE + i] & 0xFE) | bits[i];
        }
        std::ofstream out(file_path, std::ios::binary);
        if (!out) {
            std::cerr << "Error: cannot write to file " << file_path << "\n";
            return false;
        }
        out.write(reinterpret_cast<char*>(img.data()), img.size());
        return true;
    }
    else if (ext == "ppm") {
        bool ok = embed_message_into_ppm(file_path, message);
        return ok;
    }
    else {
        std::cerr << "Error: unsupported format: ." << ext << "\n";
        return false;
    }
}
std::string decode_message_from_image(const std::string& file_path) {
    auto pos = file_path.find_last_of('.');
    std::string ext = pos == std::string::npos ? "" : file_path.substr(pos+1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    if (ext == "bmp") {
        std::ifstream in(file_path, std::ios::binary);
        std::vector<unsigned char> img((std::istreambuf_iterator<char>(in)), {});
        in.close();
        std::vector<bool> bits;
        for (size_t i = 54; i < img.size(); ++i)
            bits.push_back(img[i] & 1);
        return binary_to_message(bits);
    }
    else if (ext == "ppm") {
        return decode_message_from_ppm(file_path);
    }
    std::cerr<<"Unsupported format: ."<<ext<<"\n";
    return "";
}
bool can_embed_message(const std::string& file_path, const std::string& message) {
    auto pos = file_path.find_last_of('.');
    std::string ext = pos == std::string::npos ? "" : file_path.substr(pos+1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    if (ext == "bmp") {
        std::ifstream in(file_path, std::ios::binary|std::ios::ate);
        size_t total = in.tellg();
        size_t req = (message.size()+1)*8;
        return (total - 54) >= req;
    }
    else if (ext == "ppm") {
        return can_embed_message_ppm(file_path, message);
    }
    std::cerr<<"Unsupported format: ."<<ext<<"\n";
    return false;
}
