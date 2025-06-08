#pragma once
#include <vulkan/vulkan.h>
#include <core/uniforms/gryphn_uniform_pool.h>
#include "core/uniforms/gryphn_uniform_layout.h"

struct gnPlatformUniformPool_t {
    uint32_t poolCount, maxPoolCount;
    VkDescriptorPool* pools;
};
