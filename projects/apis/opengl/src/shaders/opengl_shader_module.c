#include "opengl_shader_module.h"
#include "opengl_shader_compiler.h"
#include "stdlib.h"

gnReturnCode openglCreateShaderModule(gnShaderModule module, gnDevice device, gnShaderModuleInfo shaderModuleInfo) {
    module->shaderModule = malloc(sizeof(gnPlatformShaderModule));
    glCompilerInfo info = {
        .code = shaderModuleInfo.code,
        .wordCount = shaderModuleInfo.size / 4,
        .entryPoint = gnToCString(shaderModuleInfo.entryPoint),
    };
    glCompiler compiler = glCreateCompiler(&info);
    module->shaderModule->shader = glCompilerCompilerShader(compiler);
    glDestroyCompiler(compiler);
    return GN_SUCCESS;
}
void openglDestroyShaderModule(gnShaderModule module) {
    free(module->shaderModule);
}
