#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

extern const std::string path;
std::string getFile(std::string locate);
std::string getFullPath(std::string locate);
