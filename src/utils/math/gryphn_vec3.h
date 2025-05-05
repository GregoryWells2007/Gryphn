#pragma once

// very shitty vec3 class
// i really want to write some math for this shit but im a lazy little cunt and im not doing all that shit

#include "stdint.h"

template <typename T>
struct gnType3 {
    union {
    struct { T a, b, c; };
    struct { T x, y, z; };
    };
public:
    gnType3(T a, T b, T c) { this->a = a; this->b = b; this->c = c; }
    gnType3() {};

    bool operator==(const gnType3& other) const {
        return this->a == other.a && this->b == other.b && this->c == other.c;
    }
};

template <typename T1, typename T2, typename T3>
struct gnMultiType3 {
    union {
    struct { T1 a; T2 b; T3 c; };
    struct { T1 x; T2 y; T3 z; };
    };
public:
    gnMultiType3(T1 a, T2 b, T3 c) { this->a = a; this->b = b; this->c = c; }
    gnMultiType3() {};
};

typedef gnType3<float> gnVec3;
typedef gnVec3 gnFloat3;
typedef gnType3<uint32_t> gnUInt3;
typedef gnType3<int32_t> gnInt3;
