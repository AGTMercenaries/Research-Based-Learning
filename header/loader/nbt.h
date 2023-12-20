#pragma once
#include "loader/misc.h"

#include <string>
#include <string_view>
#include <map>
#include <vector>
#include <memory>

#define helper(NAME, TYPE, ...)          \
struct NAME : NBT {                \
	__VA_ARGS__ val{};             \
	u8 type = TYPE##u; \
	NAME(u8*& data); \
	virtual void print(int dep = 0) override; \
	virtual u8 getType() override;  \
}


struct NBT {
	std::string name{};

	NBT(); // only with payload
	virtual void print(int dep = 0);
	virtual u8 getType();
};
using pNBT = std::unique_ptr<NBT>;

struct End : NBT {
	u8 type = 0;
	
	End();
	virtual void print(int dep = 0) override;
	virtual u8 getType() override;
};
helper(Byte, 1, char);
helper(Short, 2, short);
helper(Int, 3, int);
helper(Long, 4, long long);
helper(Float, 5, float);
helper(Double, 6, double);
helper(String, 8, std::string);
helper(Compound, 10, std::map<std::string, pNBT>);
helper(ByteArray, 7, std::vector<char>);
helper(IntArray, 11, std::vector<int>);
helper(LongArray, 12, std::vector<long long>);

struct List : NBT {
	std::vector<pNBT> val;
	u8 type = 9u;
	u8 valtype;

	List(u8*& data);
	virtual void print(int dep = 0) override;
	virtual u8 getType() override;
};

pNBT parseNBT(u8*& data);
#undef helper




