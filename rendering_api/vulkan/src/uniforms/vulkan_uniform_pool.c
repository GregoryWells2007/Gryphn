#include "vulkan_uniform_pool.h"
#include "vulkan_uniform_layout.h"
#include "stdlib.h"
#include "output_device/vulkan_output_devices.h"

gnReturnCode gnCreateUniformPoolFn(gnUniformPool pool, gnDeviceHandle device) {
    pool->uniformPool = malloc(sizeof(struct gnPlatformUniformPool_t));
    pool->uniformPool->poolCount = pool->uniformPool->maxPoolCount = 1;
    pool->uniformPool->pools = malloc(sizeof(VkDescriptorPool) * pool->uniformPool->maxPoolCount);
    return GN_SUCCESS;
}

gnUniform* gnUniformPoolAllocateUniformsFn(gnUniformPool pool, const gnUniformLayout layout) {
    uint32_t setCount;
    VkDescriptorSetLayout* layouts = vkGryphnCreateSetLayouts(&layout, &setCount, pool->device->outputDevice->device);
    VkDescriptorPoolSize* sizes = malloc(sizeof(VkDescriptorPoolSize) * layout.uniformBindingCount);

    gnUniform* uniforms = malloc(sizeof(gnUniform) * setCount);
    for (int i = 0; i < layout.uniformBindingCount; i++) {

    }

    VkDescriptorPoolCreateInfo poolInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .poolSizeCount = layout.uniformBindingCount,
        .maxSets = layout.uniformBindingCount,
        .pPoolSizes = sizes,
    };

    if (pool->uniformPool->poolCount >= pool->uniformPool->maxPoolCount) {
        pool->uniformPool->maxPoolCount *= 2;
        pool->uniformPool->pools = realloc(pool->uniformPool->pools, sizeof(VkDescriptorPool) * pool->uniformPool->maxPoolCount);
    }

    if (vkCreateDescriptorPool(
        pool->device->outputDevice->device, &poolInfo, NULL,
        &pool->uniformPool->pools[pool->uniformPool->poolCount]
    ) != VK_SUCCESS)
        return NULL;
    pool->uniformPool->poolCount++;


    free(layouts);
    free(sizes);
    return uniforms;
}
