#pragma once
#include "utils/strings/gryphn_string.h"

typedef enum gnRenderingAPI_t {
    GN_RENDERINGAPI_NONE, // idk why im putting this
    GN_RENDERINGAPI_SOFTWARE, // i kinda wanna write a software renderer

    GN_RENDERINGAPI_OPENGL,
    GN_RENDERINGAPI_VULKAN,
    GN_RENDERINGAPI_DIRECTX11, GN_RENDERINGAPI_DIRECTX12,
    GN_RENDERINGAPI_METAL
} gnRenderingAPI;

gnString gnRenderingAPIName(gnRenderingAPI api) {
    switch (api) {
        case GN_RENDERINGAPI_NONE: return gnCreateString("GN_RENDERINGAPI_NONE");
        case GN_RENDERINGAPI_SOFTWARE: return gnCreateString("GN_RENDERINGAPI_SOFTWARE");
        case GN_RENDERINGAPI_OPENGL: return gnCreateString("GN_RENDERINGAPI_OPENGL");
        case GN_RENDERINGAPI_VULKAN: return gnCreateString("GN_RENDERINGAPI_VULKAN");
        case GN_RENDERINGAPI_DIRECTX11: return gnCreateString("GN_RENDERINGAPI_DIRECTX11");
        case GN_RENDERINGAPI_DIRECTX12: return gnCreateString("GN_RENDERINGAPI_DIRECTX12");
        case GN_RENDERINGAPI_METAL: return gnCreateString("GN_RENDERINGAPI_METAL");
    }
    return gnCreateString("GN_INVALID_API");
}
