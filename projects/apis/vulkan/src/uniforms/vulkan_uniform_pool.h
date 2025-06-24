#pragma once
#include <vulkan/vulkan.h>
#include <uniforms/gryphn_uniform_pool.h>

GN_ARRAY_LIST(VkDescriptorSetLayout);

typedef struct VkGryphnUniformPool {
    VkDescriptorPool pool;
    VkDescriptorSetLayoutArrayList layouts;
} VkGryphnUniformPool;
GN_ARRAY_LIST(VkGryphnUniformPool);

struct gnPlatformUniformPool_t {
    VkGryphnUniformPoolArrayList pools;
};
