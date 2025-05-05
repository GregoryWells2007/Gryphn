#pragma once
#include <gryphn/gryphn_utils.h>
#include "../gryphn_uniform.h"
#include "core/buffers/gryphn_buffer.h"

struct gnPlatformBufferUniform;

struct gnBufferUniform {
ACCESS_LEVEL:
    gnPlatformBufferUniform* bufferUniform = nullptr;
    gnSize size = 0;
    gnSize offset = 0;
    gnUInt binding = 0;
    gnUInt index = 0;
    gnBuffer* buffer = nullptr;
    gnUniform* uniform;
public:
    gnBufferUniform() {}
};

void gnBufferUniformBindBuffer(gnBufferUniform& uniformBuffer, const gnBuffer& buffer);
void gnBufferUniformSetSize(gnBufferUniform& uniformBuffer, gnSize size);
void gnBufferUniformSetOffset(gnBufferUniform& uniformBuffer, gnSize offset);
void gnBufferUniformSetBinding(gnBufferUniform& uniformBuffer, gnUInt binding);
void gnBufferUniformSetUniformIndex(gnBufferUniform& uniformBuffer, gnUInt index);
void gnBufferUniformSetUniform(gnBufferUniform& uniformBuffer, const gnUniform& uniform);

inline void (*gnUpdateBufferUniform)(gnBufferUniform& uniformBuffer, const gnOutputDevice& outputDevice);
