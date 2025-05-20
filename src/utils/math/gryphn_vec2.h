#pragma once
#include "stdint.h"

typedef struct gnVec2 {
    union {
        struct { float a, b; };
        struct { float x, y; };
    };

#ifdef GN_UTILS_CPP
    gnVec2(float x, float y) { this->x = x; this->y = y; }
    gnVec2(float s) { this->x = s; this->y = s; }
    gnVec2() {};

    gnVec2 operator-(const gnVec2& other) {
        gnVec2 returnGnVec2;
        returnGnVec2.x = this->x - other.x;
        returnGnVec2.y = this->y - other.y;
        return returnGnVec2;
    }

    bool operator==(const gnVec2& other) const {
        return this->a == other.a && this->b == other.b;
    }
#endif
} gnVec2;

typedef gnVec2 gnFVec2;
typedef gnVec2 gnFloat2;

typedef struct gnUInt2 {
    union {
        struct { uint32_t a, b; };
        struct { uint32_t x, y; };
    };

#ifdef GN_UTILS_CPP
    gnUInt2(uint32_t x, uint32_t y) { this->x = x; this->y = y; }
    gnUInt2(uint32_t s) { this->x = s; this->y = s; }
    gnUInt2() {};

    gnUInt2 operator-(const gnUInt2& other) {
        gnUInt2 returnGnVec2;
        returnGnVec2.x = this->x - other.x;
        returnGnVec2.y = this->y - other.y;
        return returnGnVec2;
    }

    bool operator==(const gnUInt2& other) const {
        return this->a == other.a && this->b == other.b;
    }
#endif
} gnUInt2;

typedef struct gnInt2 {
    union {
        struct { int a, b; };
        struct { int x, y; };
    };

#ifdef GN_UTILS_CPP
    gnInt2(int x, int y) { this->x = x; this->y = y; }
    gnInt2(int s) { this->x = s; this->y = s; }
    gnInt2() {};

    gnInt2 operator-(const gnInt2& other) {
        gnInt2 returnGnVec2;
        returnGnVec2.x = this->x - other.x;
        returnGnVec2.y = this->y - other.y;
        return returnGnVec2;
    }

    bool operator==(const gnInt2& other) const {
        return this->a == other.a && this->b == other.b;
    }
#endif
} gnInt2;
