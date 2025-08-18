#include "opengl_uniform.h"

void openglUpdateBufferUniform(gnUniform uniform, gnBufferUniformInfo* info) {
    uniform->uniform->type = gl_buffer;
    uniform->uniform->buffer_info = *info;
}
void openglUpdateStorageUniform(gnUniform uniform, gnStorageUniformInfo* info) {
    uniform->uniform->type = gl_storage;
    uniform->uniform->storage_info = *info;
}
void openglUpdateImageUniform(gnUniform uniform, gnImageUniformInfo* info) {
    uniform->uniform->type = gl_image;
    uniform->uniform->image_info = *info;
}
