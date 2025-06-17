#pragma once
#include <vulkan/vulkan.h>
#include <core/uniforms/gryphn_uniform_pool.h>

GN_ARRAY_LIST(VkDescriptorSetLayout);

typedef struct vkGryphnUniformPool {
    VkDescriptorPool pool;
    VkDescriptorSetLayoutArrayList layouts;
} vkGryphnUniformPool;

struct gnPlatformUniformPool_t {
    uint32_t poolCount, maxPoolCount, currentPool;
    vkGryphnUniformPool* pools;
};
