#include <iostream>
#include <fstream>

#include "utils/file.h"
#include "loader/misc.h"
#include "loader/nbt.h"

#include <vector>
#include <format>

u8 buf[10000];

void checknbt() {
	std::ifstream ifs(getFullPath("temp\\.nbt"));
	ifs.read((char*)buf, sizeof(buf));
	pNBT p = parseNBT(buf);

}