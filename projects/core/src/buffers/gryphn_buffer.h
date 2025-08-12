#pragma once
#include "stdlib.h"
#include "core/gryphn_return_code.h"
#include "utils/lists/gryphn_array_list.h"
#include <gryphn_handles.h>

typedef enum gnIndexType {
    GN_UINT16, GN_UINT32
} gnIndexType;

typedef enum gnBufferType {
    GN_VERTEX_BUFFER  = 1 << 0,
    GN_INDEX_BUFFER   = 1 << 2,
    GN_UNIFORM_BUFFER = 1 << 3,
    GN_STORAGE_BUFFER = 1 << 4
} gnBufferType; // I need to support more buffer types

// i love that OpenGL does this so im stealing it
// at some point GN_STAGING_BUFFER will be a buffer type so you can do all this manually
// and then I think that I will find a way to allow for mapping of GN_STATIC_DRAW
// I might do that by just making GN_STATIC_DRAW do nothing on vulkan/directx/metal
typedef enum gnBufferUsage {
    GN_STATIC_DRAW, GN_DYNAMIC_DRAW
} gnBufferUsage;

typedef struct gnBufferInfo {
    size_t size;
    gnBufferType type;
    gnBufferUsage usage;
} gnBufferInfo;

#ifdef GN_REVEAL_IMPL
struct gnBuffer_t {
    struct gnPlatformBuffer_t* buffer;
    gnDeviceHandle device;
    gnBufferInfo info;
};
#endif
typedef void* gnBufferMemory;
GN_ARRAY_LIST_HEADER(gnBuffer);
GN_ARRAY_LIST_HEADER(gnBufferMemory);

gnReturnCode gnCreateBuffer(gnBufferHandle* buffer, gnOutputDeviceHandle device, gnBufferInfo info);
void gnBufferData(gnBufferHandle buffer, size_t dataSize, gnBufferMemory data);
void gnBufferSubData(gnBufferHandle buffer, size_t offset, size_t dataSize, gnBufferMemory data);
gnBufferMemory gnMapBuffer(gnBufferHandle buffer);
void gnUnmapBuffer(gnBufferHandle buffer);
void gnDestroyBuffer(gnBufferHandle buffer);
