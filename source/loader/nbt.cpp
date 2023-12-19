#include "loader/nbt.h"

#include "utils/file.h"
#include <Windows.h>
#include <iostream>

std::string getsNBT(std::string locate) {
	std::string rNBT = getFullPath(locate);
	std::string sNBT = getFullPath("temp\\.snbt");
	std::string exe = getFullPath("tool\\SnbtCmd.exe");
	std::string command = exe + R"( path ")" + rNBT + R"(" to-snbt > )" + sNBT;
	std::cout << command << std::endl;
	system(command.c_str());
	std::string result = getFile("temp\\.snbt");
	std::cout << result << std::endl;
	return result;
}

static std::string sNBT;
static pNBT parse(int l, int r) {
	return pNBT(new NBT());
}
pNBT getoNBT(std::string sNBT) {
	::sNBT = sNBT;
	return parse(0, 0);
}
