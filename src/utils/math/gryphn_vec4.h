// typedef gnType4<uint32_t> gnUInt4;
// typedef gnType4<int32_t> gnInt4;


#pragma once
#include "stdint.h"

typedef struct gnVec4 {
    union {
        struct { float a, b, c, d; };
        struct { float x, y, z, w; };
    };

#ifdef GN_UTILS_CPP
    gnVec4(float x, float y, float z, float w) { this->x = x; this->y = y; this->z = z; this->w = w; }
    gnVec4(float s) { this->x = s; this->y = s; this->z = s; this->w = w; }
    gnVec4() {};

    gnVec4 operator-(const gnVec4& other) {
        gnVec4 returnGnVec4;
        returnGnVec4.x = this->x - other.x;
        returnGnVec4.y = this->y - other.y;
        returnGnVec4.z = this->z - other.z;
        returnGnVec4.w = this->w - other.w;
        return returnGnVec4;
    }

    bool operator==(const gnVec4& other) const {
        return this->a == other.a && this->b == other.b && this->c == other.c && this->d == other.d;
    }
#endif
} gnVec4;

typedef gnVec4 gnFVec4;
typedef gnVec4 gnFloat4;

typedef struct gnUInt4 {
    union {
        struct { uint32_t a, b, c, d; };
        struct { uint32_t x, y, z, w; };
    };

#ifdef GN_UTILS_CPP
    gnUInt4(uint32_t x, uint32_t y, uint32_t z, uint32_t w) { this->x = x; this->y = y; this->z = z; this->w = w; }
    gnUInt4(uint32_t s) { this->x = s; this->y = s; this->z = s; this->w = s; }
    gnUInt4() {};

    gnUInt4 operator-(const gnUInt4& other) {
        gnUInt4 returnGnVec4;
        returnGnVec4.x = this->x - other.x;
        returnGnVec4.y = this->y - other.y;
        returnGnVec4.z = this->z - other.z;
        returnGnVec4.w = this->w - other.w;
        return returnGnVec4;
    }

    bool operator==(const gnUInt4& other) const {
        return this->a == other.a && this->b == other.b && this->c == other.c && this->d == other.d;
    }
#endif
} gnUInt4;

typedef struct gnInt4 {
    union {
        struct { int a, b, c, d; };
        struct { int x, y, z, w; };
    };

#ifdef GN_UTILS_CPP
    gnInt4(int x, int y, int z, int w) { this->x = x; this->y = y; this->z = z; this->w = w; }
    gnInt4(int s) { this->x = s; this->y = s; this->z = s; this->w = s; }
    gnInt4() {};

    gnInt4 operator-(const gnInt4& other) {
        gnInt4 returnGnVec4;
        returnGnVec4.x = this->x - other.x;
        returnGnVec4.y = this->y - other.y;
        returnGnVec4.z = this->z - other.z;
        returnGnVec4.w = this->w - other.w;
        return returnGnVec4;
    }

    bool operator==(const gnInt4& other) const {
        return this->a == other.a && this->b == other.b && this->c == other.c;
    }
#endif
} gnInt4;
