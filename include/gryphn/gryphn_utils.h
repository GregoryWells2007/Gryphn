#pragma once
#include <utils/gryphn_bool.h>
#include <utils/lists/gryphn_list.h>
#include <utils/gryphn_error_code.h>
#include <utils/version/gryphn_version.h>
#include <utils/math/gryphn_vec2.h>
#include <utils/math/gryphn_vec3.h>
#include <utils/math/gryphn_vec4.h>
#include <utils/types/gryphn_color.h>
#include <utils/types/gryphn_color_format.h>
#include <utils/types/gryphn_image_format.h>
#include <utils/gryphn_access_level.h>

#include <cstdint>
typedef uint32_t gnUInt;
typedef gnChar gnByte;
typedef unsigned char gnUByte;
typedef int gnInt;
typedef float gnFloat;
typedef size_t gnSize;

#define GN_EXPORT extern "C"
