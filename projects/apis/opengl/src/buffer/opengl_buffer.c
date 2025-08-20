#include "opengl_buffer.h"
#include "string.h"

GLenum gnBufferTypeToGLEnum(gnBufferType type) {
    switch (type) {
    case GN_VERTEX_BUFFER: return GL_ARRAY_BUFFER;
    case GN_INDEX_BUFFER: return GL_ELEMENT_ARRAY_BUFFER;
    case GN_UNIFORM_BUFFER: return GL_UNIFORM_BUFFER;
    case GN_STORAGE_BUFFER: return GL_SHADER_STORAGE_BUFFER;
    }
}

gnReturnCode openglCreateBuffer(gnBufferHandle buffer, gnDevice device, gnBufferInfo info) {
    buffer->buffer = malloc(sizeof(gnPlatformBuffer));
    glCreateBuffers(1, &buffer->buffer->id);
    buffer->buffer->type = gnBufferTypeToGLEnum(info.type);
    buffer->buffer->usage = (info.usage == GN_DYNAMIC_DRAW) ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
    glNamedBufferStorage(buffer->buffer->id, info.size, NULL,  GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT |  GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT);
    return GN_SUCCESS;
}
void openglBufferData(gnBufferHandle buffer, size_t dataSize, void* data) {
    openglBufferSubData(buffer, 0, dataSize, data);
}
#include "stdio.h"
void openglBufferSubData(gnBufferHandle buffer, size_t offset, size_t dataSize, gnBufferMemory data) {
    void* buff = glMapNamedBufferRange(buffer->buffer->id, offset, buffer->info.size, GL_MAP_WRITE_BIT);
    memcpy(buff, data, dataSize);
    glUnmapNamedBuffer(buffer->buffer->id);
}
void* openglMapBuffer(gnBufferHandle buffer) {
    return glMapNamedBufferRange(buffer->buffer->id, 0, buffer->info.size, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
}
void openglUnmapBuffer(gnBufferHandle buffer) {
    glUnmapNamedBuffer(buffer->buffer->id);
}
void openglDestroyBuffer(gnBufferHandle buffer) {
    glDeleteBuffers(1, &buffer->buffer->id);
}
