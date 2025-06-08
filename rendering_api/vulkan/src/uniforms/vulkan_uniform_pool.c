#include "vulkan_uniform_pool.h"
#include "vulkan_uniform_layout.h"
#include "stdlib.h"
#include "output_device/vulkan_output_devices.h"

gnReturnCode gnCreateUniformPoolFn(gnUniformPool pool, gnDeviceHandle device) {
    pool->uniformPool = malloc(sizeof(struct gnPlatformUniformPool_t));
    pool->uniformPool->poolCount = 0;
    pool->uniformPool->maxPoolCount = 1;
    pool->uniformPool->pools = malloc(sizeof(vkGryphnUniformPool) * pool->uniformPool->maxPoolCount);
    return GN_SUCCESS;
}

gnUniform* gnUniformPoolAllocateUniformsFn(gnUniformPool pool, const gnUniformLayout layout) {
    if (pool->uniformPool->poolCount >= pool->uniformPool->maxPoolCount) {
        pool->uniformPool->maxPoolCount *= 2;
        pool->uniformPool->pools = realloc(pool->uniformPool->pools, sizeof(vkGryphnUniformPool) * pool->uniformPool->maxPoolCount);
    }

    pool->uniformPool->pools[pool->uniformPool->poolCount].layouts = vkGryphnCreateSetLayouts(&layout, &pool->uniformPool->pools[pool->uniformPool->poolCount].layoutCount, pool->device->outputDevice->device);
    VkDescriptorPoolSize* sizes = malloc(sizeof(VkDescriptorPoolSize) * layout.uniformBindingCount);

    gnUniform* uniforms = malloc(sizeof(gnUniform) * pool->uniformPool->pools[pool->uniformPool->poolCount].layoutCount);
    for (int i = 0; i < layout.uniformBindingCount; i++) {
        sizes[i].type = vkGryphnUniformType(layout.uniformBindings[i].type);
        sizes[i].descriptorCount = 1;
    }

    VkDescriptorPoolCreateInfo poolInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .poolSizeCount = layout.uniformBindingCount,
        .pPoolSizes = sizes,
        .maxSets = layout.uniformBindingCount,
    };

    if (vkCreateDescriptorPool(
        pool->device->outputDevice->device, &poolInfo, NULL,
        &pool->uniformPool->pools[pool->uniformPool->poolCount].pool
    ) != VK_SUCCESS)
        return NULL;
    pool->uniformPool->poolCount++;

    free(sizes);
    return uniforms;
}

void gnDestroyUniformPoolFn(gnUniformPool pool) {
    for (int i = 0; i < pool->uniformPool->poolCount; i++) {
        for (int k = 0; k < pool->uniformPool->pools[i].layoutCount; k++)
            vkDestroyDescriptorSetLayout(pool->device->outputDevice->device, pool->uniformPool->pools[i].layouts[k], NULL);
        vkDestroyDescriptorPool(pool->device->outputDevice->device, pool->uniformPool->pools[i].pool, NULL);
    }
    free(pool->uniformPool);
}
