#pragma once

// very shitty vec4 class
// I also use this same thing to make my color class dont worry abt it

#include "stdint.h"

template <typename T>
struct gnType4 {
    union {
    struct { T a, b, c, d; };
    struct { T x, y, z, w; };
    };
public:
    gnType4(T a, T b, T c, T d) { this->a = a; this->b = b; this->c = c; this->d = d; }
    gnType4() {};
};

template <typename T1, typename T2, typename T3, typename T4>
struct gnMultiType4 {
    union {
    struct { T1 r; T2 g; T3 b; T4 a; };
    struct { T1 x; T2 y; T3 z; T4 w; };
    };
public:
    gnMultiType4(T1 r, T2 g, T3 b, T4 a) { this->r = r; this->g = g; this->b = b; this->a = a; }
    gnMultiType4() {};
};

typedef gnType4<float> gnVec4;
typedef gnVec4 gnFloat4;
typedef gnType4<uint32_t> gnUInt4;
typedef gnType4<int32_t> gnInt4;
