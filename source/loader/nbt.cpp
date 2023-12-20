#include "loader/nbt.h"
#include "utils/file.h"

#include <iostream>
#include <cassert>
#include <format>

static void putTab(int dep) {
	for (int i = 1; i <= dep * 2; i++) std::cout << " ";
}

void NBT::print(int dep) {
	std::cout << "NBT::print a null nbt" << std::endl;
	assert(false);
}
#define helper(NAME)                                            \
void NAME::print(int dep) {                                     \
	putTab(dep);                                                \
	std::cout << type << std::format(R"(({}): {})", name, val); \
}                                                        

helper(Byte)
helper(Bool)
helper(Short)
helper(Int)
helper(Long)
helper(Float)
helper(Double)
helper(String, std::string)
void Compound::print(int dep) {
	putTab(dep), std::cout << type << std::format(R"(({}): {} entries)", name, val.size()) << std::endl;
	putTab(dep), std::cout << "{" << std::endl;
	for (auto& [_, ptr] : val) ptr->print(dep + 1);
	putTab(dep), std::cout << "}" << std::endl;
}

#define lister(NAME)                                                                                      \
void NAME::print(int dep) {                                                                               \
	putTab(dep), std::cout << type << std::format(R"(({}): {} entries)", name, val.size()) << std::endl;  \
	putTab(dep), std::cout << "[" << std::endl;                                                           \
	for (auto& ptr : val) ptr->print(dep + 1);                                                            \
	putTab(dep), std::cout << "]" << std::endl;                                                           \
}        
helper(ByteArray)
helper(IntArray)
helper(LongArray)


pNBT parseNBT(u8* data) {
	u8 type = *data;
	switch (type) {
	case 0: 
	}
}