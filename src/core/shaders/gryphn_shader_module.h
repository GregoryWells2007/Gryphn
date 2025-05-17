#pragma once
#include <gryphn/gryphn_utils.h>
#include "core/output_device/gryphn_output_device.h"
#include <vector>

typedef gnUByte gnShaderModuleStage;
#define GN_VERTEX_SHADER_MODULE 0x01
#define GN_FRAGMENT_SHADER_MODULE 0x10

typedef gnUInt gnShaderUse;
#define GN_GRAPHICS_PIPELINE 0

inline gnBool gnContainsShaderStage(gnShaderModuleStage stage, gnShaderModuleStage stageToContain) {
    if ((stage & stageToContain) == stageToContain) return true;
    return false;
}

struct gnPlatformShaderModule;

struct gnShaderModule {
ACCESS_LEVEL:
    gnPlatformShaderModule* shaderModule = nullptr;

    gnShaderModuleStage shaderType;
    gnShaderUse shaderUse = GN_GRAPHICS_PIPELINE;
    int codeSize = -1;
    gnByte* shaderData = nullptr;

    bool valid = false;
public:
    gnShaderModule() {}
};

void gnSetShaderModuleType(gnShaderModule& module, gnShaderModuleStage shaderModuleType);
void gnSetShaderModuleUse(gnShaderModule& module, gnShaderUse shaderUse);

void gnSetShaderModuleCode(gnShaderModule& module, gnByte* shaderModuleCode, gnSize codeSize);
void gnSetShaderModuleCode(gnShaderModule& module, gnList<gnByte>& shaderModuleCode);
void gnSetShaderModuleCode(gnShaderModule& module, gnList<gnByte> shaderModuleCode);
void gnSetShaderModuleCode(gnShaderModule& module, const std::vector<char>& shaderModuleCode);

inline gnReturnCode (*gnBuildShaderModule)(gnShaderModule* module, const gnOutputDevice& outputDevice);
inline void (*gnDestroyShaderModule)(gnShaderModule& module);
