#include "loader/nbt.h"
#include "utils/trans.h"

#include <iostream>
#include <cassert>
#include <utility>

static std::string parseString(u8*& data) {
	u16 length = *(u16*)data;
	std::string res;
	length = BE2LE_16BIT(length);
	data += 2;
	while (length--) {
		res += *data;
		data++;
	}
	return res;
}
static u8 parseU8(u8*& data) {
	u8 res = *data;
	data += 1;
	return res;
}
static u16 parseU16(u8*& data) {
	std::swap(data[0], data[1]);
	u16 res = *(u16*)data;
	data += 2;
	return res;
}
static u32 parseU32(u8*& data) {
	std::swap(data[0], data[3]);
	std::swap(data[1], data[2]);
	u32 res = *(u32*)data;
	data += 4;
	return res;
}
static u64 parseU64(u8*& data) {
	std::swap(data[0], data[7]);
	std::swap(data[1], data[6]);
	std::swap(data[2], data[5]);
	std::swap(data[3], data[4]);
	u64 res = *(u64*)data;
	data += 8;
	return res;
}
static pNBT parsePayload(u8 type, u8*& data) {
	switch (type) {
	case 0u: return pNBT(new End());
	case 1u: return pNBT(new Byte(data));
	case 2u: return pNBT(new Short(data));
	case 3u: return pNBT(new Int(data));
	case 4u: return pNBT(new Long(data));
	case 5u: return pNBT(new Float(data));
	case 6u: return pNBT(new Double(data));
	case 7u: return pNBT(new ByteArray(data));
	case 8u: return pNBT(new String(data));
	case 9u: return pNBT(new List(data));
	case 10u: return pNBT(new Compound(data));
	case 11u: return pNBT(new IntArray(data));
	case 12u: return pNBT(new LongArray(data));
	}
	assert(false);
	return nullptr;
}
pNBT parseNBT(u8*& data) {
	u8 type = parseU8(data);
	if (type == 0u) return pNBT(new End());
	auto name = parseString(data);
	auto p = parsePayload(type, data);
	p->name = name;
	return p;
}

#define helper(NAME, TYPE, BIT)  \
NAME::NAME(u8*& data) {  \
	val = static_cast<TYPE>(parseU##BIT(data));  \
}
helper(Byte, i8, 8)
helper(Short, i16, 16)
helper(Int, i32, 32)
helper(Long, i64, 64)
helper(Float, float, 32)
helper(Double, double, 64)

ByteArray::ByteArray(u8*& data) {
	i32 size = static_cast<i32>(parseU32(data));
	for (i32 i = 0; i < size; i++) val.push_back(static_cast<i8>(parseU8(data)));
};
IntArray::IntArray(u8*& data) {
	i32 size = static_cast<i32>(parseU32(data));
	for (i32 i = 0; i < size; i++) val.push_back(static_cast<i32>(parseU32(data)));
};
LongArray::LongArray(u8*& data) {
	i32 size = static_cast<i32>(parseU32(data)); 
	for (i32 i = 0; i < size; i++) val.push_back(static_cast<i64>(parseU64(data)));
};

#define typer(NAME)  \
u8 NAME::getType() {  \
	return this->type;  \
}
typer(End);
typer(Byte);
typer(Short);
typer(Int);
typer(Long);
typer(Float);
typer(Double);
typer(ByteArray);
typer(String);
typer(List);
typer(Compound);
typer(IntArray);
typer(LongArray);
u8 NBT::getType() {
	return -1;
}

NBT::NBT() {}
End::End() {}
String::String(u8*& data) {
	val = parseString(data);
}
List::List(u8*& data) {
	valtype = parseU8(data);
	i32 size = static_cast<i32>(parseU32(data));
	for (i32 i = 0; i < size; i++) val.push_back(parsePayload(valtype, data));
}
Compound::Compound(u8*& data) {
	while (true) {
		pNBT p = parseNBT(data);
		if (p->getType() == 0u) return;
		val.insert(std::make_pair(p->name, std::move(p)));
	}
}