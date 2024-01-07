#pragma once
#include "resource/location.h"
#include <string>

struct Text {
	std::string context;

	Text(Path loc);
};