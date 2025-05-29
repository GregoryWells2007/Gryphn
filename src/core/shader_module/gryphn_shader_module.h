#pragma once
#include "stdint.h"
#include "utils/strings/gryphn_string.h"
#include "core/output_device/gryphn_output_device.h"

typedef enum gnShaderModuleStage_e {
    GN_VERTEX_SHADER_MODULE, GN_FRAGMENT_SHADER_MODULE
} gnShaderModuleStage;

typedef struct gnShaderModuleInfo_t {
    enum gnShaderModuleStage_e stage;
    uint32_t* code;
    uint32_t size;
    gnString entryPoint;
} gnShaderModuleInfo;

struct gnPlatformShaderModule_t;

typedef struct gnShaderModule_t {
    struct gnPlatformShaderModule_t* shaderModule;
    struct gnShaderModuleInfo_t info;
    struct gnOutputDevice_t* device;
} gnShaderModule;

gnReturnCode gnCreateShaderModule(struct gnShaderModule_t* module, struct gnOutputDevice_t* device, struct gnShaderModuleInfo_t shaderModuleInfo);
void gnDestroyShaderModule(struct gnShaderModule_t* module);
