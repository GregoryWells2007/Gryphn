#pragma once
#include <vulkan/vulkan.h>
#include <uniforms/gryphn_uniform_pool.h>


GN_ARRAY_LIST_HEADER(VkDescriptorSetLayout);
typedef struct VkGryphnUniformPool {
    VkDescriptorPool pool;
    VkDescriptorSetLayoutArrayList layouts;
} VkGryphnUniformPool;
GN_ARRAY_LIST_HEADER(VkGryphnUniformPool);

struct gnPlatformUniformPool_t {
    VkGryphnUniformPoolArrayList pools;
};

gnReturnCode createUniformPool(gnUniformPool pool, gnDeviceHandle device);
gnUniform* allocateUniforms(gnUniformPool pool, gnUniformAllocationInfo allocInfo);
void destroyUniformPool(gnUniformPool pool);
