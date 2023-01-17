#include "StringHelper.h"

#include <Arduino.h>

const std::string StringHelper::DELIMITER = ".";

std::string StringHelper::extractFirstElement(std::string& string) {
	std::string::size_type i = string.find(DELIMITER);
	
	std::string firstElement;
	
	// if delimiter wasnt found, theres only one element
	if(i == std::string::npos) {
		firstElement = string;
		string = "";
	}
	
	else {
		firstElement = string.substr(0, i); // get first element from string
		string = string.substr(i + DELIMITER.length(), string.length()); // remove element including the delimiter from the string
	}
	
	return firstElement;
}

std::vector<std::string> StringHelper::splitIntoElements(std::string string){
	std::vector<std::string> elements;
	
	std::string::size_type i;
	// while another delimiter is found
	while((i = string.find(DELIMITER)) != std::string::npos) {
		elements.push_back(string.substr(0, i)); // add first element from string to elements
		string = string.substr(i + DELIMITER.length(), string.length()); // remove element including the delimiter from the string
	}
	// add last element to elements
	elements.push_back(string);
	
	return elements;
}

std::string StringHelper::toString(const int& i) {
	return std::string(String(i).c_str());
}

int StringHelper::toInt(const std::string& string) {
	return String(string.c_str()).toInt();
}

std::string StringHelper::padFront(std::string string, const char& fillCharacter, const std::string::size_type& length) {
	std::string::size_type stringLength = string.length();
	
	if(stringLength == length) {
		return string;
	}
	else if(stringLength > length) {
		string = string.substr(stringLength - length, length);
	}
	else {
		string = std::string(length - stringLength, fillCharacter) + string;
	}
	
	return string;
}

std::string StringHelper::padCenter(std::string string, const char& fillCharacter, const std::string::size_type& length) {
	std::string::size_type stringLength = string.length();
	
	if(stringLength == length) {
		return string;
	}
	else if(stringLength > length) {
		string = string.substr((stringLength - length) / 2, length);
	}
	else {
		string = std::string((length - stringLength) / 2, fillCharacter) + string + std::string((length - stringLength + 1) / 2, fillCharacter);
	}
	
	return string;
}

std::string StringHelper::padBack(std::string string, const char& fillCharacter, const std::string::size_type& length) {
	std::string::size_type stringLength = string.length();
	
	if(stringLength == length) {
		return string;
	}
	else if(stringLength > length) {
		string = string.substr(0, length);
	}
	else {
		string = string + std::string(length - stringLength, fillCharacter);
	}
	
	return string;
}
