#pragma once

typedef enum gnImageFormat {
    GN_FORMAT_NONE,
    GN_FORMAT_BGRA8_SRGB,
    GN_FORMAT_BGRA8,
    GN_FORMAT_RGBA8_SRGB,
    GN_FORMAT_D24S8_UINT,
    GN_FORMAT_D32S8_UINT,
} gnImageFormat;

typedef enum gnColorSpace {
    GN_COLOR_SPACE_NONE,
    GN_COLOR_SPACE_SRGB_NONLINEAR
} gnColorSpace;

typedef enum gnImageSharingMode {
    GN_SHARING_MODE_EXCLUSIVE, GN_SHARING_MODE_CONCURRENT
} gnImageSharingMode;

typedef enum gnImageLayout {
    GN_LAYOUT_UNDEFINED,
    GN_LAYOUT_PRESENTATION_QUEUE_IMAGE,
    GN_LAYOUT_TRANSFER_DESTINATION,
    GN_LAYOUT_DEPTH_STENCIL,
    GN_LAYOUT_COLOR_ATTACHMENT
} gnImageLayout;
