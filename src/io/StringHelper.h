#ifndef __STRINGHELPER__
#define __STRINGHELPER__

#include <Arduino_AVRSTL.h>
#include <string.h>
#include <vector>

namespace StringHelper {
	extern const std::string DELIMITER;
	
	std::string extractFirstElement(std::string& string);
	std::vector<std::string> splitIntoElements(std::string string);
	
	std::string toString(const int& i);
	
	int toInt(const std::string& string);
	
	std::string padFront(std::string string, const char& fillCharacter, const std::string::size_type& length);
	std::string padCenter(std::string string, const char& fillCharacter, const std::string::size_type& length);
	std::string padBack(std::string string, const char& fillCharacter, const std::string::size_type& length);
}

#endif
