#pragma once
#include "stdint.h"

typedef uint32_t gnVersion; // uint32_t is the loser way to right this I can write it anyway I want

#define gnCreateVersion(major, minor, patch) ((((uint32_t)(major)) << 22U) | (((uint32_t)(minor)) << 12U) | ((uint32_t)(patch)))
