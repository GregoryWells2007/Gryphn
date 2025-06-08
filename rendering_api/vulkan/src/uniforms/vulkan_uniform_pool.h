#pragma once
#include <vulkan/vulkan.h>
#include <core/uniforms/gryphn_uniform_pool.h>
#include "core/uniforms/gryphn_uniform_layout.h"

typedef struct VkGryphnUniformPool {
    VkDescriptorPool pool;
    gnUniformType type;
} VkGryphnUniformPool;

struct gnPlatformUniformPool_t {
    int maxUniformPools;
    int uniformPoolCount;
    VkGryphnUniformPool* pools;
};
