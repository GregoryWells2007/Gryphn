#pragma once
#include <unordered_map>
#include <string>

// very shitty vec2 class

#include "stdint.h"

template <typename T>
struct gnType2 {
    union {
    struct { T a, b; };
    struct { T x, y; };
    };
public:
    gnType2(T a, T b) { this->a = a; this->b = b; }
    gnType2() {};

    gnType2 operator-(const gnType2& other) {
        gnType2 returnGnVec2;
        returnGnVec2.x = this->x - other.x;
        returnGnVec2.y = this->y - other.y;
        return returnGnVec2;
    }

    bool operator==(const gnType2& other) const {
        return this->a == other.a && this->b == other.b;
    }
};


typedef gnType2<float> gnVec2;
typedef gnType2<float> gnFloat2;
typedef gnType2<uint32_t> gnUInt2;
typedef gnType2<int32_t> gnInt2;

namespace std {
    template<>
    struct hash<gnUInt2> {
        std::size_t operator()(const gnUInt2& k) const {
            return std::hash<uint32_t>()(k.x) ^ (std::hash<uint32_t>()(k.y) << 1);
        }
    };
}
