#pragma once
#include <gryphn/gryphn_utils.h>
#include "core/output_device/gryphn_output_device.h"

struct gnPlatformBuffer;

typedef enum gnBufferType {
    GN_VERTEX_BUFFER = 0, GN_INDEX_BUFFER = 1, GN_UNIFORM_BUFFER = 2
} gnBufferType;

typedef enum gnBufferDataType {
    GN_UINT8, GN_UINT16, GN_UINT32
} gnBufferDataType;

struct gnBuffer {
ACCESS_LEVEL:
    gnPlatformBuffer* buffer = nullptr;
    gnSize size;
    gnBufferType bufferType;
    gnBufferDataType dataType;
public:
    gnBuffer() {}
};

void gnBufferSetSize(gnBuffer& buffer, gnSize size);
void gnBufferSetType(gnBuffer& buffer, gnBufferType type);
void gnBufferSetDataType(gnBuffer& buffer, gnBufferDataType type);

inline gnErrorCode (*gnCreateBuffer)(gnBuffer* buffer, const gnOutputDevice& outputDevice);
inline void (*gnBufferData)(gnBuffer& buffer, void* data);
inline void (*gnBufferMapData)(gnBuffer& buffer, void** data); // used to map data to a pointer without copying
inline void (*gnBufferSubData)(gnBuffer& buffer, gnSize offset, gnSize size, void* data);
inline void (*gnBufferClearData)(gnBuffer& buffer);
inline void (*gnDestroyBuffer)(gnBuffer& buffer);
