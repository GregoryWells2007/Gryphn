#pragma once
#include <gryphn/gryphn_utils.h>
#include "core/shaders/gryphn_shader_module.h"

struct gnPlatformPushConstant;

struct gnPushConstant {
ACCESS_LEVEL:
    gnPlatformPushConstant* pushConstant = nullptr;
    gnShaderModuleStage stage = 0;
    gnSize offset = 0;
    gnSize size = 0;
public:
    gnPushConstant() {}
};

void gnPushConstantSetShaderStage(gnPushConstant& pushConstant, gnShaderModuleStage stage);
void gnPushConstantSetOffset(gnPushConstant& pushConstant, gnSize offset);
void gnPushConstantSetSize(gnPushConstant& pushConstant, gnSize size);
