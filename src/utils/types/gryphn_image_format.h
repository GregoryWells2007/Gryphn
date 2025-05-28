#pragma once

typedef enum gnImageFormat_e {
    GN_FORMAT_NONE,
    GN_FORMAT_BGRA8_SRGB
} gnImageFormat;

typedef enum gnColorSpace_e {
    GN_COLOR_SPACE_SRGB_NONLINEAR
} gnColorSpace;

typedef enum gnImageSharingMode_e {
    GN_SHARING_MODE_EXCLUSIVE, GN_SHARING_MODE_CONCURRENT
} gnImageSharingMode;

typedef enum gnImageLayout_e {
    GN_LAYOUT_UNDEFINED, GN_LAYOUT_PRESENTATION_QUEUE_IMAGE, GN_LAYOUT_TRANSFER_DESTINATION, GN_COLOR_ATTACHMENT
} gnImageLayout;
