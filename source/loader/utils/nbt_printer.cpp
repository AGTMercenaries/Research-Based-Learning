#include "loader/utils/nbt.h"

#include <iostream>
#include <cassert>
#include <format>

#define helper(NAME)                                            \
void NAME::print(int dep) {                                     \
	putTab(dep);                                                \
	std::cout << typeName[type] << std::format(R"(('{}'): {})", name, val); \
}                                                        
#define lister(NAME)                                                                                      \
void NAME::print(int dep) {                                                                               \
	putTab(dep), std::cout << typeName[type] << std::format(R"(('{}'): )", name);                                     \
	std::cout << "[";                                                                                     \
	for (auto i = val.begin(); i != val.end(); i++) {                                                     \
		std::cout << i64(*i);                                                                                  \
		if (next(i) != val.end()) std::cout << ", ";                                                      \
	}                                                                                                     \
	putTab(dep), std::cout << "]" << std::endl;                                                           \
}        

static void putTab(int dep) {
	for (int i = 1; i <= dep * 2; i++) std::cout << " ";
}
static const std::string typeName[] = {
	"Null", "Byte", "Short", "Int", "Long", "Float", "Double", "ByteArray", "String", "List", "Compound", "IntArray", "LongArray"
};

void Byte::print(int dep) {
	putTab(dep);
	std::cout << typeName[type] << std::format(R"(('{}'): {})", name, int(val)); 
}
helper(Short)
helper(Int)
helper(Long)
helper(Float)
helper(Double)
helper(String)
lister(ByteArray)
lister(IntArray)
lister(LongArray)

void Compound::print(int dep) {
	putTab(dep), std::cout << typeName[type] << std::format(R"(('{}'): {} entries)", name, val.size()) << std::endl;
	putTab(dep), std::cout << "{" << std::endl;
	for (auto& [_, ptr] : val) ptr->print(dep + 1), std::cout << std::endl;
	std::cout << std::endl, putTab(dep), std::cout << "}" << std::endl;
}
void NBT::print(int dep) {
	std::cout << "NBT::print a null nbt" << std::endl;
	assert(false);
}
void End::print(int dep) {
	std::cout << "NBT::print a null nbt" << std::endl;
	assert(false);
}
void List::print(int dep) {
	putTab(dep), std::cout << typeName[type] << std::format(R"(('{}'): {} entries)", name, val.size()) << std::endl;
	putTab(dep), std::cout << "{" << std::endl;
	for (auto& ptr : val) ptr->print(dep + 1);
	std::cout << std::endl, putTab(dep), std::cout << "}" << std::endl;
}