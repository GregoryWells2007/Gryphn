#pragma once

typedef enum gnRenderingAPI_t {
    GN_RENDERINGAPI_NONE, // idk why im putting this
    GN_RENDERINGAPI_SOFTWARE, // i kinda wanna write a software renderer

    GN_RENDERINGAPI_OPENGL,
    GN_RENDERINGAPI_VULKAN,
    GN_RENDERINGAPI_DIRECTX11, GN_RENDERINGAPI_DIRECTX12,
    GN_RENDERINGAPI_METAL
} gnRenderingAPI;
