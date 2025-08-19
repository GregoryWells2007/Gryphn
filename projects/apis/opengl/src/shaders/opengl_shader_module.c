#include "opengl_shader_module.h"
#include "opengl_shader_compiler.h"
#include "output_device/gryphn_output_device.h"
#include "instance/gryphn_instance.h"
#include "stdlib.h"

#include "stdio.h"

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
    glCompiler compiler = glCreateCompiler(&info);
    module->shaderModule->shader = glCompilerCompilerShader(compiler);
    glDestroyCompiler(compiler);

    module->shaderModule->id = glCreateShader(gnShaderTypeToGLEnum(shaderModuleInfo.stage));
    const char* source = module->shaderModule->shader.source;
    printf("Shader Source %s\n", source);
    glShaderSource(module->shaderModule->id, 1, &source, NULL);
    glCompileShader(module->shaderModule->id);

    GLint returnCode;
    glGetShaderiv(module->shaderModule->id, GL_COMPILE_STATUS, &returnCode);
    if(!returnCode) {
        char infoLog[512];
        glGetShaderInfoLog(module->shaderModule->id, 512, NULL, infoLog);
        gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
            .message = gnCreateString(infoLog)
        });
    }

    return GN_SUCCESS;
}
void openglDestroyShaderModule(gnShaderModule module) {
    glDeleteShader(module->shaderModule->id);
    free(module->shaderModule);
}
