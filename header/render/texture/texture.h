#pragma once
#include <string>

struct Texture {
private:
	unsigned int ID;

public:
	Texture(std::string name);

	void use();
};