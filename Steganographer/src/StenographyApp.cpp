#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include "Stenographer.h"

namespace fs = std::filesystem;
static void skip_ws_and_comments(std::ifstream& in) {
    char c;
    while (in >> std::ws && in.peek() == '#') {
        in.get(c);
        while (in.get(c) && c != '\n');
    }
}
static void print_image_info(const std::string& path) {
    std::error_code ec;
    uintmax_t filesize = fs::file_size(path, ec);
    if (ec) {
        std::cerr << "Error getting file size: " << ec.message() << "\n";
        return;
    }
    struct stat st{};
    if (stat(path.c_str(), &st) != 0) {
        std::cerr << "Error getting file modification time\n";
        return;
    }
    std::time_t mtime = st.st_mtime;
    std::tm* tm_ptr = std::localtime(&mtime);
    if (!tm_ptr) {
        std::cerr << "Error converting time\n";
        return;
    }
    auto pos = path.find_last_of('.');
    std::string ext = (pos == std::string::npos) ? "" : path.substr(pos + 1);
    std::transform(ext.begin(), ext.end(), ext.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    std::cout << "File: " << path << "\n";
    std::cout << "Size: " << filesize << " bytes\n";
    std::cout << "Last modified: "
              << std::put_time(tm_ptr, "%Y-%m-%d %H:%M:%S")
              << "\n";
    if (ext == "bmp") {
        std::ifstream in(path, std::ios::binary);
        if (!in) {
            std::cerr << "Error: cannot open BMP for dims\n";
            return;
        }
        char hdr[54];
        in.read(hdr, 54);
        int width  = *reinterpret_cast<int*>(&hdr[18]);
        int height = *reinterpret_cast<int*>(&hdr[22]);
        std::cout << "Format: 24-bit BMP\n";
        std::cout << "Dimensions: " << width << " x " << height << "\n";
    }
    else if (ext == "ppm") {
        std::ifstream in(path);
        if (!in) {
            std::cerr << "Error: cannot open PPM for dims\n";
            return;
        }
        std::string magic;
        in >> magic;
        skip_ws_and_comments(in);
        int width, height, maxv;
        in >> width;  skip_ws_and_comments(in);
        in >> height; skip_ws_and_comments(in);
        in >> maxv;
        std::cout << "Format: PPM (" << magic << ")\n";
        std::cout << "Dimensions: " << width << " x " << height << "\n";
    }
    else {
        std::cerr << "Error: Unsupported format: ." << ext << "\n";
        std::exit(1);
    }
}
void show_help() {
    std::cout
        << "Use .bmp and .ppm\n"
        << "Options:\n"
        << "  -i, --info [file_path]             : Display info (format, size, dims, timestamp).\n"
        << "  -e, --encrypt [file_path] \"message\" : Embed a message into the image.\n"
        << "  -d, --decrypt [file_path]          : Decode a message from the image.\n"
        << "  -c, --check [file_path] \"message\"   : Check capacity for embedding.\n"
        << "  -h, --help                         : Display this help.\n";
}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        show_help();
        return 0;
    }
    std::string opt = argv[1];
    if (opt == "-h" || opt == "--help") {
        if (argc != 2) {
            std::cerr << "Error: " << opt << " does not take any arguments\n";
            return 1;
        }
        show_help();
        return 0;
    }
    else if (opt == "-i" || opt == "--info") {
        if (argc != 3) {
            std::cerr << "Error: " << opt << " requires one argument: <file>\n";
            return 1;
        }
        {
            std::string path = argv[2];
            auto pos = path.find_last_of('.');
            std::string ext = (pos == std::string::npos) ? "" : path.substr(pos + 1);
            std::transform(ext.begin(), ext.end(), ext.begin(),
                           [](unsigned char c){ return std::tolower(c); });
            if (ext != "bmp" && ext != "ppm") {
                std::cerr << "Error: No such file or directory\n";
                std::cerr << "Error: Unsupported format: " << ext << "\n";
                return 1;
            }
        }
        print_image_info(argv[2]);
        return 0;
    }
    else if (opt == "-e" || opt == "--encrypt") {
        if (argc != 4) {
            std::cerr << "Error: " << opt << " requires two arguments: <file> <message>\n";
            return 1;
        }
        {
            std::string path = argv[2];
            auto pos = path.find_last_of('.');
            std::string ext = (pos == std::string::npos) ? "" : path.substr(pos + 1);
            std::transform(ext.begin(), ext.end(), ext.begin(),
                           [](unsigned char c){ return std::tolower(c); });
            if (ext != "bmp" && ext != "ppm") {
                std::cerr << "Error: No such file or directory\n";
                std::cerr << "Error: Unsupported format: " << ext << "\n";
                return 1;
            }
        }
        std::cout << "Embedding into: " << argv[2] << "\n";
        if (!embed_message_into_image(argv[2], argv[3])) {
            return 1;
        }
        std::cout << "Success!\n";
        return 0;
    }
    else if (opt == "-d" || opt == "--decrypt") {
        if (argc != 3) {
            std::cerr << "Error: " << opt << " requires one argument: <file>\n";
            return 1;
        }
        {
            std::string path = argv[2];
            auto pos = path.find_last_of('.');
            std::string ext = (pos == std::string::npos) ? "" : path.substr(pos + 1);
            std::transform(ext.begin(), ext.end(), ext.begin(),
                           [](unsigned char c){ return std::tolower(c); });
            if (ext != "bmp" && ext != "ppm") {
                std::cerr << "Error: No such file or directory\n";
                std::cerr << "Error: Unsupported format: " << ext << "\n";
                return 1;
            }
        }
        std::cout << "Decoding from: " << argv[2] << "\n";
        std::string msg = decode_message_from_image(argv[2]);
        std::cout << "Decoded: " << msg << "\n";
        return 0;
    }
    else if (opt == "-c" || opt == "--check") {
        if (argc != 4) {
            std::cerr << "Error: " << opt << " requires two arguments: <file> <message>\n";
            return 1;
        }
        {
            std::string path = argv[2];
            auto pos = path.find_last_of('.');
            std::string ext = (pos == std::string::npos) ? "" : path.substr(pos + 1);
            std::transform(ext.begin(), ext.end(), ext.begin(),
                           [](unsigned char c){ return std::tolower(c); });
            if (ext != "bmp" && ext != "ppm") {
                std::cerr << "Error: No such file or directory\n";
                std::cerr << "Error: Unsupported format: " << ext << "\n";
                return 1;
            }
        }
        std::cout << "Checking capacity in: " << argv[2] << "\n";
        bool ok = can_embed_message(argv[2], argv[3]);
        std::cout << (ok ? "Enough space.\n" : "Not enough space.\n");
        return ok ? 0 : 1;
    }
    else {
        std::cerr << "Error: Unknown option: " << opt << "\n";
        std::cerr << "Use -h or --help for usage\n";
        return 1;
    }
    return 0;
}
