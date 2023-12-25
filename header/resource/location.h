#pragma once
#include <string>

using Location = std::string;
using Extension = std::string;

std::string getPath(Location loc, Extension ext);
