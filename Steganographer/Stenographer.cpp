#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <functional> // Added for std::function used in PPM embedding/decoding
#include "Stenographer.h" //

namespace fs = std::filesystem;

// Улучшенная версия функции пропуска комментариев
static void skip_whitespace_and_comments(std::ifstream& in) {
    char c;
    while (in >> std::ws && in.peek() == '#') {
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// All functions declared in Stenographer.h's stego namespace must be defined within it here.
namespace stego { // Start of the stego namespace

// From Stenographer.h: std::string get_image_info(const std::string& path);
std::string get_image_info(const std::string& path) {
    std::ostringstream info_stream;

    // Проверка существования файла
    if (!fs::exists(path)) {
        throw std::runtime_error("File does not exist: " + path);
    }

    // Получение размера файла
    std::error_code ec;
    uintmax_t filesize = fs::file_size(path, ec);
    if (ec) {
        throw std::runtime_error("Error getting file size: " + ec.message());
    }

    // Получение времени изменения
    struct stat st{};
    if (stat(path.c_str(), &st) != 0) {
        throw std::runtime_error("Error getting file modification time");
    }

    std::tm* tm_ptr = std::localtime(&st.st_mtime);
    if (!tm_ptr) {
        throw std::runtime_error("Error converting time");
    }

    // Получение расширения файла
    auto pos = path.find_last_of('.');
    std::string ext = (pos == std::string::npos) ? "" : path.substr(pos + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    // Формирование информации
    info_stream << "File: " << path << "\n"
                << "Size: " << filesize << " bytes\n"
                << "Last modified: "
                << std::put_time(tm_ptr, "%Y-%m-%d %H:%M:%S") << "\n";

    // Обработка разных форматов
    if (ext == "bmp") {
        std::ifstream in(path, std::ios::binary);
        if (!in) {
            throw std::runtime_error("Cannot open BMP file");
        }

        char hdr[54];
        in.read(hdr, 54);
        int width = *reinterpret_cast<int*>(&hdr[18]);
        int height = *reinterpret_cast<int*>(&hdr[22]);

        info_stream << "Format: 24-bit BMP\n"
                    << "Dimensions: " << width << " x " << height << "\n";
    }
    else if (ext == "ppm") {
        std::ifstream in(path);
        if (!in) {
            throw std::runtime_error("Cannot open PPM file");
        }

        std::string magic;
        in >> magic;
        // Re-use the existing static helper in this file, or define a new one in the namespace if preferred.
        // For now, let's keep it global if it's truly a helper, or move it if it needs stego context.
        // Assuming skip_whitespace_and_comments is a general helper, keeping it outside `stego` namespace is fine.
        // However, the original code had `skip_whitespace_and_comments(in);` inside stego::get_image_info without a direct definition in the stego namespace.
        // The one provided in the error output has `skip_ws_and_comments`. Let's assume `skip_whitespace_and_comments` is correctly defined or needs to be adapted.
        // For consistency with the provided snippet, use `::skip_ws_and_comments` if it's truly global.
        // Or better, define a local version `static void skip_whitespace_and_comments_local(std::ifstream& in)`
        // or move the `skip_whitespace_and_comments` into the `stego` namespace if it's only used there.
        // Given the error, the `skip_whitespace_and_comments` from `Stenographer.cpp` was being called,
        // so let's stick with that definition and make sure it's accessible.
        // For now, let's just make sure the `stego` namespace is correctly applied.
        skip_whitespace_and_comments(in); // Call the global helper

        int width, height, maxv;
        in >> width;  skip_whitespace_and_comments(in); // Call the global helper
        in >> height; skip_whitespace_and_comments(in); // Call the global helper
        in >> maxv;

        info_stream << "Format: PPM (" << magic << ")\n"
                    << "Dimensions: " << width << " x " << height << "\n";
    }
    else {
        throw std::runtime_error("Unsupported format: ." + ext);
    }

    return info_stream.str();
}

// Base conversions
std::vector<bool> message_to_binary(const std::string& message) { //
    std::vector<bool> binary;
    for (unsigned char c : message)
        for (int i = 7; i >= 0; --i)
            binary.push_back((c >> i) & 1);
    for (int i = 0; i < 8; ++i) binary.push_back(false); // Null terminator
    return binary;
}

std::string binary_to_message(const std::vector<bool>& bits) { //
    std::string msg;
    char cur = 0;
    for (size_t i = 0; i < bits.size(); ++i) {
        cur = (cur << 1) | bits[i];
        if (i % 8 == 7) {
            if (cur == '\0') break; // Stop at null terminator
            msg += cur;
            cur = 0;
        }
    }
    return msg;
}

// Helper functions (could be in detail namespace or kept private static)
// Assuming these are meant to be private helpers within stego, or moved to 'detail' namespace as declared.
// For now, moving them inside 'stego' will resolve linker errors.

// Validation functions from Stenographer.h
bool is_valid_bmp(const std::string& file_path) { // Corresponds to `is_bmp_24_bit` in the provided C++ snippet
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

bool is_valid_ppm(const std::string& file_path) { // Corresponds to `is_ppm` in the provided C++ snippet
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


namespace detail { // Nested namespace for format-specific implementations

// Note: The `embed_into_bmp` and `extract_from_bmp` in `Stenographer.h` are likely implemented
// directly within `embed_message_into_image` and `decode_message_from_image` in the provided `Stenographer.cpp`.
// I'll adapt the provided `embed_message_into_image` and `decode_message_from_image` to fit the `detail` namespace structure if they are meant to be separate.
// For now, I'll put the PPM specific ones that were defined as `static` in the snippet into `detail`.

// Original static helpers for PPM
bool embed_into_ppm(const std::string& file_path, const std::vector<bool>& bits) { // Corresponds to `embed_binary_ppm` and `embed_ascii_ppm` combined, or a new wrapper
    std::ifstream in(file_path);
    if (!in) { std::cerr<<"Cannot open: "<<file_path<<"\n"; return false; }
    std::string magic; in >> magic; in.close();

    if (magic == "P6") {
        // This logic matches `embed_binary_ppm` from your snippet
        std::ifstream in_binary(file_path, std::ios::binary);
        if (!in_binary) { std::cerr<<"Cannot open file: "<<file_path<<"\n"; return false; }
        std::vector<unsigned char> data((std::istreambuf_iterator<char>(in_binary)), {});
        in_binary.close();

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
    else if (magic == "P3") {
        // This logic matches `embed_ascii_ppm` from your snippet
        std::ifstream in_ascii(file_path);
        if (!in_ascii) { std::cerr<<"Cannot open file: "<<file_path<<"\n"; return false; }

        std::string magic_ascii;
        in_ascii >> magic_ascii;
        if (magic_ascii != "P3") { std::cerr<<"Not a P3 PPM.\n"; return false; }

        skip_whitespace_and_comments(in_ascii); // Use the general helper
        int w,h,maxv;
        in_ascii >> w; skip_whitespace_and_comments(in_ascii);
        in_ascii >> h; skip_whitespace_and_comments(in_ascii);
        in_ascii >> maxv;

        std::vector<int> pix;
        pix.reserve(w*h*3);
        for (int v, cnt=w*h*3; cnt-- && (in_ascii>>v); )
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
    std::cerr<<"Unsupported PPM format for embedding: "<<magic<<"\n";
    return false;
}

std::string extract_from_ppm(const std::string& file_path) { // Corresponds to `decode_binary_ppm` and `decode_ascii_ppm` combined, or a new wrapper
    std::ifstream in(file_path);
    if (!in) { std::cerr<<"Cannot open: "<<file_path<<"\n"; return ""; }
    std::string magic; in >> magic; in.close();

    if (magic == "P6") {
        // This logic matches `decode_binary_ppm` from your snippet
        std::ifstream in_binary(file_path, std::ios::binary);
        if (!in_binary) { std::cerr<<"Cannot open file: "<<file_path<<"\n"; return ""; }
        std::vector<unsigned char> data((std::istreambuf_iterator<char>(in_binary)), {});
        in_binary.close();

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
    else if (magic == "P3") {
        // This logic matches `decode_ascii_ppm` from your snippet
        std::ifstream in_ascii(file_path);
        if (!in_ascii) { std::cerr<<"Cannot open file: "<<file_path<<"\n"; return ""; }

        std::string magic_ascii;
        in_ascii >> magic_ascii;
        if (magic_ascii != "P3") { std::cerr<<"Not a P3 PPM.\n"; return ""; }

        skip_whitespace_and_comments(in_ascii); // Use the general helper
        int w,h,maxv;
        in_ascii >> w; skip_whitespace_and_comments(in_ascii);
        in_ascii >> h; skip_whitespace_and_comments(in_ascii);
        in_ascii >> maxv;

        std::vector<bool> bits;
        for (int v; in_ascii>>v; )
            bits.push_back(v & 1);

        return binary_to_message(bits);
    }
    std::cerr<<"Unsupported PPM format for decoding: "<<magic<<"\n";
    return "";
}

bool embed_into_bmp(const std::string& file_path, const std::vector<bool>& binary_msg) { // Assuming this is needed as per Stenographer.h
    if (!is_valid_bmp(file_path)) { // Use the stego::is_valid_bmp
        std::cerr << "Error: BMP is not 24-bit or invalid.\n";
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
    if (binary_msg.size() > pixelBytes) {
        std::cerr << "Error: BMP image data too small, need "
                  << binary_msg.size() << " bits but only "
                  << pixelBytes << " available\n";
        return false;
    }

    for (size_t i = 0; i < binary_msg.size(); ++i) {
        img[HEADER_SIZE + i] = (img[HEADER_SIZE + i] & 0xFE) | binary_msg[i];
    }

    std::ofstream out(file_path, std::ios::binary);
    if (!out) {
        std::cerr << "Error: cannot write to file " << file_path << "\n";
        return false;
    }
    out.write(reinterpret_cast<char*>(img.data()), img.size());
    return true;
}

std::string extract_from_bmp(const std::string& file_path) { // Assuming this is needed as per Stenographer.h
    std::ifstream in(file_path, std::ios::binary);
    if (!in) {
        std::cerr << "Error: cannot open file " << file_path << "\n";
        return "";
    }
    std::vector<unsigned char> img((std::istreambuf_iterator<char>(in)), {});
    in.close();
    std::vector<bool> bits;
    for (size_t i = 54; i < img.size(); ++i)
        bits.push_back(img[i] & 1);
    return binary_to_message(bits);
}

} // End of detail namespace

// Main interface functions, using the detail namespace helpers where appropriate
bool embed_message_into_image(const std::string& file_path, const std::string& message) { //
    auto pos = file_path.find_last_of('.');
    std::string ext = (pos == std::string::npos) ? "" : file_path.substr(pos + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    auto bits = message_to_binary(message);

    if (ext == "bmp") {
        return detail::embed_into_bmp(file_path, bits); // Use the detail helper
    }
    else if (ext == "ppm") {
        return detail::embed_into_ppm(file_path, bits); // Use the detail helper
    }
    else {
        std::cerr << "Error: unsupported format: ." << ext << "\n";
        return false;
    }
}

std::string decode_message_from_image(const std::string& file_path) { //
    auto pos = file_path.find_last_of('.');
    std::string ext = pos == std::string::npos ? "" : file_path.substr(pos+1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    if (ext == "bmp") {
        return detail::extract_from_bmp(file_path); // Use the detail helper
    }
    else if (ext == "ppm") {
        return detail::extract_from_ppm(file_path); // Use the detail helper
    }
    std::cerr<<"Unsupported format: ."<<ext<<"\n";
    return "";
}

bool check_capacity(const std::string& file_path, const std::string& message) { // Corresponds to `can_embed_message`
    auto pos = file_path.find_last_of('.');
    std::string ext = pos == std::string::npos ? "" : file_path.substr(pos+1);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    size_t req = (message.size()+1)*8; // Message bits + null terminator bits

    if (ext == "bmp") {
        std::ifstream in(file_path, std::ios::binary|std::ios::ate);
        if (!in) {
            std::cerr << "Error: cannot open file " << file_path << " for capacity check.\n";
            return false;
        }
        size_t total = in.tellg();
        return (total >= 54 + req); // BMP header size is 54 bytes
    }
    else if (ext == "ppm") {
        // This part needs to derive from the `can_embed_message_ppm` logic.
        std::ifstream in(file_path);
        if (!in) { std::cerr<<"Cannot open file: "<<file_path<<"\n"; return false; }
        std::string magic; in >> magic;

        if (magic == "P6") {
            in.seekg(0, std::ios::end);
            size_t total = in.tellg();
            // Estimate header size for P6 for capacity check, or parse it properly.
            // The value '15' in `(total - 15)` from previous `can_embed_message_ppm` seems like an approximation.
            // A more robust check would involve parsing the header to find the exact pixel data start.
            // For now, let's use the provided logic from `can_embed_message_ppm`.
            // The provided `can_embed_message_ppm` already accounts for this.
            return (total - 15) >= req; // Using the '15' constant from the snippet's `can_embed_message_ppm`
        }
        if (magic == "P3") {
            skip_whitespace_and_comments(in);
            int w,h,mx;
            in>>w; skip_whitespace_and_comments(in);
            in>>h; skip_whitespace_and_comments(in);
            in>>mx;
            return size_t(w)*h*3 >= req;
        }
        std::cerr<<"Unsupported PPM magic for capacity check: "<<magic<<"\n";
        return false;
    }
    std::cerr<<"Unsupported format for capacity check: ."<<ext<<"\n";
    return false;
}

// show_help function (not declared in Stenographer.h, so keep it outside stego or make it static if only used internally)
void show_help() { //
    std::cout << "Image Steganography Tool\n"
              << "Usage:\n"
              << "  -i, --info <file>        Show image info\n"
              << "  -e, --embed <file> <msg> Embed message\n"
              << "  -d, --extract <file>     Extract message\n"
              << "  -c, --check <file> <msg> Check capacity\n"
              << "  -h, --help               Show this help\n";
}


} // End of stego namespace
