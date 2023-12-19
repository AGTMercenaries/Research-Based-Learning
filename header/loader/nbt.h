#pragma once
#include <string>
#include <string_view>
#include <map>
#include <vector>
#include <memory>

// sNBT conventer
std::string getsNBT(std::string locate);

// object NBT and conventer
#define helper(NAME, ...)          \
struct NAME : NBT {                 \
	__VA_ARGS__ val;                       \
	std::string_view type = #NAME; \
}


struct NBT {
	std::string_view type = "Raw";
};
using pNBT = std::unique_ptr<NBT>;
helper(Byte, char);
helper(Bool, bool);
helper(Short, short);
helper(Int, int);
helper(Long, long);
helper(Float, float);
helper(Double, double);
helper(String, std::string);
helper(Compound, std::map<std::string, pNBT>);
struct List : NBT {
	std::vector<pNBT> val;
	std::string_view vType;
	std::string_view type = "List";
};

pNBT getoNBT(std::string sNBT);





