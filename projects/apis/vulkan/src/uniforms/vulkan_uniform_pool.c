#include "vulkan_uniform_pool.h"
#include "vulkan_uniform_layout.h"
#include "stdlib.h"
#include "output_device/vulkan_output_devices.h"
#include "uniforms/gryphn_uniform.h"
#include "vulkan_uniform.h"
#include "stdio.h"

VkGryphnUniformPool* GetLastUniformPool(VkGryphnUniformPoolArrayList* list) { return &list->data[list->count - 1]; }

gnReturnCode createUniformPool(gnUniformPool pool, gnDeviceHandle device) {
    pool->uniformPool = malloc(sizeof(struct gnPlatformUniformPool_t));
    pool->uniformPool->pools = VkGryphnUniformPoolArrayListCreate();

    if (device->outputDevice->enabledOversizedDescriptorPools == gnTrue) {
        {
            VkGryphnUniformPool firstPool = {
                .pool = VK_NULL_HANDLE,
                .layouts = VkDescriptorSetLayoutArrayListCreate()
            };
            VkGryphnUniformPoolArrayListAdd(&pool->uniformPool->pools, firstPool);
        } // scopped because the add function copies and I don't want it lying around

        VkGryphnUniformPool* currentPool = GetLastUniformPool(&pool->uniformPool->pools);
        VkDescriptorPoolCreateInfo poolInfo = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .flags = VK_DESCRIPTOR_POOL_CREATE_ALLOW_OVERALLOCATION_SETS_BIT_NV,
            .poolSizeCount = 0,
            .pPoolSizes = NULL,
            .maxSets = 0
        };

        if (vkCreateDescriptorPool(
            pool->device->outputDevice->device, &poolInfo, NULL,
            &currentPool->pool
        ) != VK_SUCCESS)
            return GN_FAILED_TO_ALLOCATE_MEMORY;
    }

    return GN_SUCCESS;
}

gnUniform* allocateUniforms(gnUniformPool pool, gnUniformAllocationInfo allocInfo) {
    gnBool fixedAllocation = !pool->device->outputDevice->enabledOversizedDescriptorPools;

    if (fixedAllocation) {
        VkGryphnUniformPool newPool = {
            .pool = VK_NULL_HANDLE,
            .layouts = VkDescriptorSetLayoutArrayListCreate()
        };

        // TODO: redo this, its not warning me IDK why cuz its totally wrong
        VkDescriptorPoolSize uniformBufferSize = {
            .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            .descriptorCount = 0
        };

        VkDescriptorPoolSize imageSize = {
            .type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            .descriptorCount = 0
        };

        for (int i = 0; i < allocInfo.setCount; i++) {
            for (int c = 0; c < allocInfo.sets[i].uniformBindingCount; c++) {
                if (allocInfo.sets[i].uniformBindings[c].type == GN_UNIFORM_BUFFER_DESCRIPTOR) uniformBufferSize.descriptorCount++;
                if (allocInfo.sets[i].uniformBindings[c].type == GN_IMAGE_DESCRIPTOR) imageSize.descriptorCount++;
            }
        }

        uint32_t count = 0;
        VkDescriptorPoolSize poolSizes[2] = {};

        if (uniformBufferSize.descriptorCount > 0) {
            poolSizes[count] = uniformBufferSize;
            count++;
        }

        if (imageSize.descriptorCount > 0) {
            poolSizes[count] = imageSize;
            count++;
        }

        VkDescriptorPoolCreateInfo poolInfo = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .poolSizeCount = count,
            .pPoolSizes = poolSizes,
            .maxSets = allocInfo.setCount
        };

        if (vkCreateDescriptorPool(
            pool->device->outputDevice->device, &poolInfo, NULL,
            &newPool.pool
        ) != VK_SUCCESS)
            return NULL;

        VkGryphnUniformPoolArrayListAdd(&pool->uniformPool->pools, newPool);
    } // scopped for same reasons as before

    VkGryphnUniformPool* currentPool = GetLastUniformPool(&pool->uniformPool->pools);

    uint32_t startingCount = currentPool->layouts.count;
    VkDescriptorSetLayoutArrayListExpand(&currentPool->layouts, allocInfo.setCount);

    for (int i = 0; i < allocInfo.setCount; i++) {
        VkDescriptorSetLayoutArrayListAdd(
            &currentPool->layouts,
            vkGryphnCreateSetLayouts(&allocInfo.sets[i], pool->device->outputDevice->device)
        );
    }

    VkDescriptorSetAllocateInfo vkAllocInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = currentPool->pool,
        .descriptorSetCount = allocInfo.setCount,
        .pSetLayouts = &currentPool->layouts.data[startingCount]
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
}

void destroyUniformPool(gnUniformPool pool) {
    for (int k = 0; k < pool->uniformPool->pools.count; k++) {
        vkDestroyDescriptorPool(pool->device->outputDevice->device, pool->uniformPool->pools.data[k].pool, NULL);
        for (int i = 0; i < pool->uniformPool->pools.data[k].layouts.count; i++)
            vkDestroyDescriptorSetLayout(pool->device->outputDevice->device, pool->uniformPool->pools.data[k].layouts.data[i], NULL);
    }
}
