#pragma once
#include "stdlib.h"
#include "utils/gryphn_error_code.h"
#include "utils/lists/gryphn_array_list.h"
#include <gryphn_handles.h>

typedef enum gnIndexType {
    GN_UINT16, GN_UINT32
} gnIndexType;

typedef enum gnBufferType {
    GN_VERTEX_BUFFER  = 0x00000001,
    GN_INDEX_BUFFER   = 0x00000002,
    GN_UNIFORM_BUFFER = 0x00000004,
    GN_STORAGE_BUFFER = 0x00000008
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
    gnBufferInfo info;
};
#endif
typedef void* gnBufferMemory;
GN_ARRAY_LIST(gnBuffer);
GN_ARRAY_LIST(gnBufferMemory);

gnReturnCode gnCreateBuffer(gnBufferHandle* buffer, gnOutputDeviceHandle device, gnBufferInfo info);
void gnBufferData(gnBufferHandle buffer, size_t dataSize, gnBufferMemory data);
void gnBufferSubData(gnBufferHandle buffer, size_t offset, size_t dataSize, gnBufferMemory data);
gnBufferMemory gnMapBuffer(gnBufferHandle buffer);
void gnDestroyBuffer(gnBufferHandle buffer);
