#pragma once
#include <vector>
#include <string>
#include <stdexcept>

namespace stego {

class InvalidImageFormat : public std::runtime_error {
public:
    explicit InvalidImageFormat(const std::string& msg)
        : std::runtime_error(msg) {}
};

std::string get_image_info(const std::string& path);
// Базовые преобразования
std::vector<bool> message_to_binary(const std::string& message);
std::string binary_to_message(const std::vector<bool>& binary_message);

// Основной интерфейс
bool embed_message_into_image(const std::string& file_path, const std::string& message);
std::string decode_message_from_image(const std::string& file_path);
bool check_capacity(const std::string& file_path, const std::string& message);

// Валидация форматов
bool is_valid_bmp(const std::string& file_path);
bool is_valid_ppm(const std::string& file_path);

// Формат-специфичные реализации (можно сделать детальями реализации)
namespace detail {
bool embed_into_bmp(const std::string& file_path, const std::vector<bool>& binary_msg);
std::string extract_from_bmp(const std::string& file_path);

bool embed_into_ppm(const std::string& file_path, const std::vector<bool>& binary_msg);
std::string extract_from_ppm(const std::string& file_path);
}

}
