#include "StringUtils.hpp"

namespace utils {
namespace str {

std::string& ltrim(std::string& s, const char* whitespaces)
{
	s.erase(0, s.find_first_not_of(whitespaces));
	return s;
}

std::string& rtrim(std::string& s, const char* whitespaces)
{
	s.erase(s.find_last_not_of(whitespaces) + 1);
	return s;
}

 std::string& trim(std::string& s, const char* whitespaces)
{
	return ltrim(rtrim(s, whitespaces), whitespaces);
}

 std::vector<std::string> split(const std::string& str, const char delim)
 {
	 std::size_t current, previous = 0;
	 current = str.find(delim);
	 std::vector<std::string> splittedStr;
	 while (current != std::string::npos) {
		 splittedStr.push_back(str.substr(previous, current - previous));
		 previous = current + 1;
		 current = str.find(delim, previous);
	 }
	 splittedStr.push_back(str.substr(previous, current - previous));
	 return splittedStr;
 }

} // namespace str
} // namespace utils
