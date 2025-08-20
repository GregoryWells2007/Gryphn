#include "opengl_uniform.h"

void openglUpdateBufferUniform(gnUniform uniform, gnBufferUniformInfo* info) {
    uniform->uniform->bindings[info->binding].isUpdated = GN_TRUE;
    uniform->uniform->bindings[info->binding].type = gl_buffer;
    uniform->uniform->bindings[info->binding].buffer_info = *info;
}
void openglUpdateStorageUniform(gnUniform uniform, gnStorageUniformInfo* info) {
    uniform->uniform->bindings[info->binding].isUpdated = GN_TRUE;
    uniform->uniform->bindings[info->binding].type = gl_storage;
    uniform->uniform->bindings[info->binding].storage_info = *info;
}
void openglUpdateImageUniform(gnUniform uniform, gnImageUniformInfo* info) {
    uniform->uniform->bindings[info->binding].isUpdated = GN_TRUE;
    uniform->uniform->bindings[info->binding].type = gl_image;
    uniform->uniform->bindings[info->binding].image_info = *info;
}
