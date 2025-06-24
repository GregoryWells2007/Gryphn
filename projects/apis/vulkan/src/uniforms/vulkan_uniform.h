#pragma once
#include <vulkan/vulkan.h>
#include "uniforms/gryphn_uniform.h"

typedef struct gnPlatformUniform_t {
    VkDescriptorSet set;
} gnPlatformUniform;

void updateBufferUniform(gnUniform uniform, gnBufferUniformInfo* info);
void updateImageUniform(gnUniform uniform, gnImageUniformInfo* info);
