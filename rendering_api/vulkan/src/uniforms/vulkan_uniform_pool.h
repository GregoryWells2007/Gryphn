#pragma once
#include <vulkan/vulkan.h>
#include <core/uniforms/gryphn_uniform_pool.h>

typedef struct vkGryphnUniformPool {
    VkDescriptorPool pool;
    uint32_t layoutCount;
    VkDescriptorSetLayout* layouts;
} vkGryphnUniformPool;

struct gnPlatformUniformPool_t {
    uint32_t poolCount, maxPoolCount, currentPool;
    vkGryphnUniformPool* pools;
};
