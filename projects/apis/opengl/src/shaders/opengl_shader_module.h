#pragma once
#include "core/src/shader_module/gryphn_shader_module.h"
#include "opengl_shader_compiler.h"

typedef struct gnPlatformShaderModule_t {
    glCompiler compiler;
} gnPlatformShaderModule;

GLenum gnShaderTypeToGLEnum(gnShaderModuleStage stage);

gnReturnCode openglCreateShaderModule(gnShaderModule module, gnDevice device, gnShaderModuleInfo shaderModuleInfo);
void openglDestroyShaderModule(gnShaderModule module);
