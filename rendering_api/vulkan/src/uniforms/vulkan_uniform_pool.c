#include "vulkan_uniform_pool.h"
#include "vulkan_uniform_layout.h"
#include "stdlib.h"
#include "output_device/vulkan_output_devices.h"
#include "core/uniforms/gryphn_uniform.h"
#include "vulkan_uniform.h"
#include "stdio.h"

gnReturnCode gnCreateUniformPoolFn(gnUniformPool pool, gnDeviceHandle device) {
    pool->uniformPool = malloc(sizeof(struct gnPlatformUniformPool_t));
    pool->uniformPool->poolCount = 0;
    // pool->uniformPool->maxPoolCount = 2;
    pool->uniformPool->pools = malloc(sizeof(vkGryphnUniformPool) * pool->uniformPool->maxPoolCount);

    VkDescriptorPoolCreateInfo poolInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .flags = VK_DESCRIPTOR_POOL_CREATE_ALLOW_OVERALLOCATION_SETS_BIT_NV,
        .poolSizeCount = 0,
        .pPoolSizes = NULL,
        .maxSets = 0
    };

    if (vkCreateDescriptorPool(
        pool->device->outputDevice->device, &poolInfo, NULL,
        &pool->uniformPool->pools[0].pool
    ) != VK_SUCCESS)
        return GN_FAILED_TO_ALLOCATE_MEMORY;

    pool->uniformPool->pools[0].layouts = VkDescriptorSetLayoutArrayListCreate();

    // if (device->outputDevice->enabledOversizedDescriptorPools == gnTrue) {
    //     VkDescriptorPoolCreateInfo poolInfo = {
    //         .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
    //         .flags = VK_DESCRIPTOR_POOL_CREATE_ALLOW_OVERALLOCATION_SETS_BIT_NV,
    //         .poolSizeCount = 0,
    //         .pPoolSizes = NULL,
    //         .maxSets = 0
    //     };

    //     if (vkCreateDescriptorPool(
    //         pool->device->outputDevice->device, &poolInfo, NULL,
    //         &pool->uniformPool->pools[pool->uniformPool->poolCount].pool
    //     ) != VK_SUCCESS)
    //         return GN_FAILED_TO_ALLOCATE_MEMORY;

    //     pool->uniformPool->pools[0].layoutCount = 0;
    //     pool->uniformPool->pools[0].layouts = NULL;
    //     pool->uniformPool->poolCount = 1;
    // }

    // pool->uniformPool->currentPool = 0;



    return GN_SUCCESS;
}

gnUniform* gnUniformPoolAllocateUniformsFn(gnUniformPool pool, gnUniformAllocationInfo allocInfo) {
    uint32_t startingCount = pool->uniformPool->pools[0].layouts.count;
    VkDescriptorSetLayoutArrayListExpand(&pool->uniformPool->pools[0].layouts, allocInfo.setCount);

    for (int i = 0; i < allocInfo.setCount; i++) {
        VkDescriptorSetLayoutArrayListAdd(
            &pool->uniformPool->pools[0].layouts,
            vkGryphnCreateSetLayouts(&allocInfo.sets[i], pool->device->outputDevice->device)
        );
    }

    VkDescriptorSetAllocateInfo vkAllocInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = pool->uniformPool->pools[0].pool,
        .descriptorSetCount = allocInfo.setCount,
        .pSetLayouts = &pool->uniformPool->pools[0].layouts.data[startingCount]
    };

    VkDescriptorSet* sets = malloc(sizeof(VkDescriptorSet) * allocInfo.setCount);
    if (vkAllocateDescriptorSets(pool->device->outputDevice->device, &vkAllocInfo, sets) != VK_SUCCESS)
        return NULL;

    gnUniform* uniforms = malloc(sizeof(gnUniform) * allocInfo.setCount);
    for (int i = 0; i < allocInfo.setCount; i++) {
        uniforms[i] = malloc(sizeof(struct gnUniform_t));
        uniforms[i]->uniform = malloc(sizeof(struct gnPlatformUniform_t));
        uniforms[i]->uniform->set = sets[i];
    }
    return uniforms;

    // gnBool fixedAllocCount = pool->device->outputDevice->enabledOversizedDescriptorPools;

    // if (fixedAllocCount) {
    //     if (pool->uniformPool->poolCount >= pool->uniformPool->maxPoolCount) {
    //         pool->uniformPool->maxPoolCount *= 2;
    //         pool->uniformPool->pools = realloc(pool->uniformPool->pools, sizeof(vkGryphnUniformPool) * pool->uniformPool->maxPoolCount);
    //     }

    //     VkDescriptorPoolSize uniformBufferSize = {
    //         .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
    //         .descriptorCount = 0
    //     };

    //     VkDescriptorPoolSize imageSize = {
    //         .type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
    //         .descriptorCount = 0
    //     };

    //     for (int i = 0; i < allocInfo.setCount; i++) {
    //         for (int c = 0; c < allocInfo.sets[i].uniformBindingCount; c++) {
    //             if (allocInfo.sets[i].uniformBindings[i].type == GN_UNIFORM_BUFFER_DESCRIPTOR) uniformBufferSize.descriptorCount++;
    //             if (allocInfo.sets[i].uniformBindings[i].type == GN_IMAGE_DESCRIPTOR) imageSize.descriptorCount++;
    //         }
    //     }



    //     VkDescriptorPoolCreateInfo poolInfo = {
    //         .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
    //         .poolSizeCount = 1,
    //         .pPoolSizes = (VkDescriptorPoolSize[]){ uniformBufferSize, imageSize },
    //         .maxSets = allocInfo.setCount
    //     };

    //     if (vkCreateDescriptorPool(
    //         pool->device->outputDevice->device, &poolInfo, NULL,
    //         &pool->uniformPool->pools[pool->uniformPool->poolCount].pool
    //     ) != VK_SUCCESS)
    //         return NULL;
    //     pool->uniformPool->poolCount++;

    //     uint32_t maxSets = uniformBufferSize.descriptorCount + uniformBufferSize.descriptorCount;
    // }

    // if (fixedAllocCount)
    //     pool->uniformPool->pools[pool->uniformPool->currentPool].layouts = malloc(sizeof(VkDescriptorSetLayout) * allocInfo.setCount);
    // else {
    //     if (pool->uniformPool->pools[pool->uniformPool->currentPool].layouts == NULL) {
    //         pool->uniformPool->pools[pool->uniformPool->currentPool].layouts = malloc(sizeof(VkDescriptorSetLayout) * allocInfo.setCount);
    //     }
    //     else {
    //         pool->uniformPool->pools[pool->uniformPool->currentPool].layouts = realloc(
    //             pool->uniformPool->pools[pool->uniformPool->currentPool].layouts,
    //             sizeof(VkDescriptorSetLayout) * (allocInfo.setCount + pool->uniformPool->pools[pool->uniformPool->currentPool].layoutCount));
    //     }
    // }
    // for (int i = 0; i < allocInfo.setCount; i++) {
    //     pool->uniformPool->pools[pool->uniformPool->currentPool].layouts[pool->uniformPool->pools[pool->uniformPool->currentPool].layoutCount + i] = vkGryphnCreateSetLayouts(&allocInfo.sets[i], pool->device->outputDevice->device);
    // }

    // VkDescriptorSetAllocateInfo vkAllocInfo = {
    //     .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
    //     .descriptorPool = pool->uniformPool->pools[pool->uniformPool->currentPool].pool,
    //     .descriptorSetCount = allocInfo.setCount,
    //     .pSetLayouts = &pool->uniformPool->pools[pool->uniformPool->currentPool].layouts[pool->uniformPool->pools[pool->uniformPool->currentPool].layoutCount]
    // };
    // pool->uniformPool->pools[pool->uniformPool->currentPool].layoutCount += allocInfo.setCount;

    // VkDescriptorSet* sets = malloc(sizeof(VkDescriptorSet) * allocInfo.setCount);
    // if (vkAllocateDescriptorSets(pool->device->outputDevice->device, &vkAllocInfo, sets) != VK_SUCCESS)
    //     return NULL;

    // gnUniform* uniforms = malloc(sizeof(gnUniform) * allocInfo.setCount);
    // for (int i = 0; i < allocInfo.setCount; i++) {
    //     uniforms[i] = malloc(sizeof(struct gnUniform_t));
    //     uniforms[i]->uniform = malloc(sizeof(struct gnPlatformUniform_t));
    //     uniforms[i]->uniform->set = sets[i];
    // }
    // return uniforms;
}

void gnDestroyUniformPoolFn(gnUniformPool pool) {
    vkDestroyDescriptorPool(pool->device->outputDevice->device, pool->uniformPool->pools[0].pool, NULL);
    for (int i = 0; i < pool->uniformPool->pools[0].layouts.count; i++) {
        vkDestroyDescriptorSetLayout(pool->device->outputDevice->device, pool->uniformPool->pools[0].layouts.data[i], NULL);
    }
}
