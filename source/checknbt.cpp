#include <iostream>
#include <fstream>

#include "loader/utils/misc.h"
#include "loader/utils/nbt.h"

#include <vector>
#include <format>
#include <memory>
#include <map>

struct FOO {
	~FOO() {
		std::cout << "FOO delete" << std::endl;
	}
};
struct BOO {
	FOO t;
};

void checknbt() {

	//std::ifstream ifs(getFullPath("temp\\.nbt"), std::ios::binary | std::ios::in);

	//ifs.read((char*)buf, sizeof(buf));
	//auto p = buf;

	//std::cout << "!!??!!" << ifs.eof() << std::endl;
	//for (int i = 0; i < 1543; i++) std::cout << i << " : " << int(buf[i]) << std::endl;

	//auto nbt = parseNBT(p);
	//std::cout << "!!??!!" << p - buf << std::endl;
	//std::cout << "!!! " << int(nbt->getType()) << std::endl;
	//nbt->print();
	////std::cout << parseString(p) << std::endl;
}