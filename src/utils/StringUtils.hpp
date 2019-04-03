#pragma once

#include <string>
#include <vector>

namespace utils {
namespace str {

std::string& ltrim(std::string& s, const char* whitespaces = " \t\n\r\f\v");
std::string& rtrim(std::string& s, const char* whitespaces = " \t\n\r\f\v");
std::string& trim(std::string& s, const char* whitespaces = " \t\n\r\f\v");
std::vector<std::string> split(const std::string& ss, const char delim = ' ');

}  // namespace str
} // namespace utils
