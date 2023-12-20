#pragma once
#include "loader/misc.h"

#include <string>
#include <string_view>
#include <map>
#include <vector>
#include <memory>

#define helper(NAME, ...)          \
struct NAME : NBT {                \
	__VA_ARGS__ val;               \
	std::string_view type = #NAME; \
	virtual void print(int dep = 0) override; \
}


struct NBT {
	std::string_view type = "Raw";
	std::string name;

	virtual void print(int dep = 0);
};
using pNBT = std::unique_ptr<NBT>;
helper(Byte, char);
helper(Bool, bool);
helper(Short, short);
helper(Int, int);
helper(Long, long long);
helper(Float, float);
helper(Double, double);
helper(String, std::string);
helper(Compound, std::map<std::string, pNBT>);
helper(List, std::vector<pNBT>);
helper(ByteArray, std::vector<char>);
helper(IntArray, std::vector<int>);
helper(LongArray, std::vector<long long>);


pNBT parseNBT(u8* data);





