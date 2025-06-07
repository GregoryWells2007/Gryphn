#pragma once
#include "stdint.h"
#include "utils/gryphn_string.h"
#include "utils/gryphn_error_code.h"
#include "core/gryphn_handles.h"

typedef enum gnShaderModuleStage_e {
    GN_VERTEX_SHADER_MODULE   = 0x00000001,
    GN_FRAGMENT_SHADER_MODULE = 0x00000002,
    GN_ALL_SHADER_MODULE      = 0xffffffff
} gnShaderModuleStage;

typedef struct gnShaderModuleInfo_t {
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

gnReturnCode gnCreateShaderModule(gnShaderModuleHandle* module, gnOutputDeviceHandle device, struct gnShaderModuleInfo_t shaderModuleInfo);
void gnDestroyShaderModule(gnShaderModuleHandle module);
