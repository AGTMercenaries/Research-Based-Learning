#include "resource/location.h"

std::string getPath(Location loc, Extension ext) {
	return "resource\\" + loc + "." + ext;
}