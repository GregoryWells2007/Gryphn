#pragma once
#include "stdlib.h"
#include "utils/gryphn_error_code.h"
#include <core/gryphn_handles.h>

typedef enum gnBufferType {
    GN_VERTEX_BUFFER = 0x00000001
} gnBufferType;

typedef enum gnBufferUsage {
    GN_STATIC_DRAW, GN_DYNAMIC_DRAW
} gnBufferUsage; // i love that OpenGL does this so im stealing it

typedef struct gnBufferInfo {
    size_t size;
    gnBufferType type;
    gnBufferUsage usage;
} gnBufferInfo;

#ifdef GN_REVEAL_IMPL
struct gnBuffer_t {
    struct gnPlatformBuffer_t* buffer;
    gnDeviceHandle device;
};
#endif

gnReturnCode gnCreateBuffer(gnBufferHandle* buffer, gnOutputDeviceHandle device, gnBufferInfo info);
void gnBufferData(gnBufferHandle buffer, size_t dataSize, void* data);
void gnDestroyBuffer(gnBufferHandle buffer);
