#pragma once
#include <vector>
#include <string>

std::vector<bool> message_to_binary(const std::string& message);
std::string binary_to_message(const std::vector<bool>& binary_message);

bool embed_message_into_image(const std::string& file_path, const std::string& message);
std::string decode_message_from_image(const std::string& file_path);
bool can_embed_message(const std::string& file_path, const std::string& message);

bool is_bmp_24_bit(const std::string& file_path);

bool is_ppm(const std::string& file_path);
bool embed_message_into_ppm(const std::string& file_path, const std::string& message);
std::string decode_message_from_ppm(const std::string& file_path);
bool can_embed_message_ppm(const std::string& file_path, const std::string& message);