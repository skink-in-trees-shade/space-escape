#ifndef COMPONENTS_MESSAGE_HPP
#define COMPONENTS_MESSAGE_HPP

#include <string>

struct Message final {
	Message(std::string text) : text(text) {}
	std::string text;
};

#endif