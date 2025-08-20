#include "opengl_shader_module.h"
#include "opengl_shader_compiler.h"
#include "stdlib.h"

GLenum gnShaderTypeToGLEnum(gnShaderModuleStage stage) {
    switch (stage) {
    case GN_VERTEX_SHADER_MODULE: return GL_VERTEX_SHADER;
    case GN_FRAGMENT_SHADER_MODULE: return GL_FRAGMENT_SHADER;
    case GN_ALL_SHADER_MODULE: return GL_VERTEX_SHADER | GL_FRAGMENT_SHADER;
    }
}

gnReturnCode openglCreateShaderModule(gnShaderModule module, gnDevice device, gnShaderModuleInfo shaderModuleInfo) {
    module->shaderModule = malloc(sizeof(gnPlatformShaderModule));
    glCompilerInfo info = {
        .code = shaderModuleInfo.code,
        .wordCount = shaderModuleInfo.size / 4,
        .entryPoint = gnToCString(shaderModuleInfo.entryPoint),
    };
    module->shaderModule->compiler  = glCreateCompiler(&info);
    return GN_SUCCESS;
}
void openglDestroyShaderModule(gnShaderModule module) {
    glDestroyCompiler(module->shaderModule->compiler);
    free(module->shaderModule);
}
