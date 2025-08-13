#include "core/src/shader_module/gryphn_shader_module.h"

typedef struct gnPlatformShaderModule_t {
    const char* shaderSource;
} gnPlatformShaderModule;

gnReturnCode openglCreateShaderModule(gnShaderModule module, gnDevice device, gnShaderModuleInfo shaderModuleInfo);
void openglDestroyShaderModule(gnShaderModule module);
