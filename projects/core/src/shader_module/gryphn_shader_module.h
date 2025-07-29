#pragma once
#include "stdint.h"
#include "utils/gryphn_string.h"
#include "core/gryphn_return_code.h"
#include "gryphn_handles.h"

typedef enum gnShaderModuleStage {
    GN_VERTEX_SHADER_MODULE   = 1 << 0,
    GN_FRAGMENT_SHADER_MODULE = 1 << 1,
    GN_ALL_SHADER_MODULE = GN_VERTEX_SHADER_MODULE | GN_FRAGMENT_SHADER_MODULE
} gnShaderModuleStage;

typedef struct gnShaderModuleInfo {
    gnShaderModuleStage stage;
    uint32_t* code;
    uint32_t size;
    gnString entryPoint;
} gnShaderModuleInfo;

#ifdef GN_REVEAL_IMPL
struct gnShaderModule_t {
    struct gnPlatformShaderModule_t* shaderModule;
    gnShaderModuleInfo info;
    gnOutputDeviceHandle device;
};
#endif

gnReturnCode gnCreateShaderModule(gnShaderModuleHandle* module, gnOutputDeviceHandle device, struct gnShaderModuleInfo shaderModuleInfo);
void gnDestroyShaderModule(gnShaderModuleHandle module);
