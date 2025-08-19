#pragma once
#include "core/src/buffers/gryphn_buffer.h"
#include "glad/glad.h"
#include "utils/gryphn_cpp_function.h"

typedef struct gnPlatformBuffer_t {
    GLuint id;
    GLenum type, usage;
} gnPlatformBuffer;

gnReturnCode openglCreateBuffer(gnBufferHandle buffer, gnDevice device, gnBufferInfo info);
void openglBufferData(gnBufferHandle buffer, size_t dataSize, void* data);
void openglBufferSubData(gnBufferHandle buffer, size_t offset, size_t dataSize, gnBufferMemory data);
void* openglMapBuffer(gnBufferHandle buffer);
void openglUnmapBuffer(gnBufferHandle buffer);
void openglDestroyBuffer(gnBufferHandle buffer);


GN_CPP_FUNCTION GLenum gnBufferTypeToGLEnum(gnBufferType type);
