#include "opengl_buffer.h"

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
    return GN_SUCCESS;
}
void openglBufferData(gnBufferHandle buffer, size_t dataSize, void* data) {
    glNamedBufferData(buffer->buffer->id, dataSize, data, buffer->buffer->usage);
}
void openglBufferSubData(gnBufferHandle buffer, size_t offset, size_t dataSize, gnBufferMemory data) {
    glNamedBufferSubData(buffer->buffer->id, offset, dataSize, data);
}
void* openglMapBuffer(gnBufferHandle buffer) {
    return glMapNamedBuffer(buffer->buffer->id, GL_READ_WRITE);
}
void openglUnmapBuffer(gnBufferHandle buffer) {
    glUnmapNamedBuffer(buffer->buffer->id);
}
void openglDestroyBuffer(gnBufferHandle buffer) {
    glDeleteBuffers(1, &buffer->buffer->id);
}
