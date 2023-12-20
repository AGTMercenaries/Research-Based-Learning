#pragma once

#define BE2LE_64BIT(x) ()
#define BE2LE_32BIT(x) ((x & 0x000000ff) << 24) | ((x & 0x0000ff00) << 8) | ((x & 0x00ff0000) >> 8) | ((x & 0xff000000) >> 24)
#define BE2LE_16BIT(x) ((x & 0x00ff) << 8) | ((x & 0xff00) >> 8)
