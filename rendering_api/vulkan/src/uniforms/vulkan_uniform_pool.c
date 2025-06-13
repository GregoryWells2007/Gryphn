#include "vulkan_uniform_pool.h"
#include "vulkan_uniform_layout.h"
#include "stdlib.h"
#include "output_device/vulkan_output_devices.h"
#include "core/uniforms/gryphn_uniform.h"
#include "vulkan_uniform.h"
#include "shader_module/vulkan_shader_module.h"
#include "stdio.h"

gnReturnCode gnCreateUniformPoolFn(gnUniformPool pool, gnDeviceHandle device) {
    pool->uniformPool = malloc(sizeof(struct gnPlatformUniformPool_t));
    pool->uniformPool->poolCount = 0;
    pool->uniformPool->maxPoolCount = 1;
    pool->uniformPool->pools = malloc(sizeof(vkGryphnUniformPool) * pool->uniformPool->maxPoolCount);
    return GN_SUCCESS;
}

VkDescriptorSetLayout* fsdfsdfsdfsdfsdfdsf(
    const gnUniformLayout* layout, uint32_t* setCount,
    VkDevice device
) {
    gnUniformLayout uniformLayout = *layout;

    *setCount = uniformLayout.uniformBindingCount;
    VkDescriptorSetLayout* sets = malloc(sizeof(VkDescriptorSetLayoutBinding) * uniformLayout.uniformBindingCount);
    for (int i = 0; i < uniformLayout.uniformBindingCount; i++) {
        VkDescriptorSetLayoutBinding setLayout = {
            .binding = uniformLayout.uniformBindings[i].binding,
            .descriptorCount = 1,
            .descriptorType = vkGryphnUniformType(uniformLayout.uniformBindings[i].type),
            .stageFlags = vkGryphnShaderModuleStage(uniformLayout.uniformBindings[i].stage)
        };

        VkDescriptorSetLayoutCreateInfo info = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
            .bindingCount = 1,
            .pBindings = &setLayout
        };

        if (vkCreateDescriptorSetLayout(device, &info, NULL, sets) != VK_SUCCESS) {
            return NULL;
        }
    }
    return sets;
}

gnUniform* gnUniformPoolAllocateUniformsFn(gnUniformPool pool, gnUniformAllocationInfo allocInfo) {
    if (pool->uniformPool->poolCount >= pool->uniformPool->maxPoolCount) {
        pool->uniformPool->maxPoolCount *= 2;
        pool->uniformPool->pools = realloc(pool->uniformPool->pools, sizeof(vkGryphnUniformPool) * pool->uniformPool->maxPoolCount);
    }

    pool->uniformPool->pools[pool->uniformPool->poolCount].layouts = malloc(sizeof(VkDescriptorSetLayout) * allocInfo.layoutCount);
    pool->uniformPool->pools[pool->uniformPool->poolCount].layoutCount = allocInfo.layoutCount;
    VkDescriptorPoolSize uniformBufferSize = {
        .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = 0
    };
    for (int i = 0; i < allocInfo.layoutCount; i++) {
        for (int c = 0; c < allocInfo.layouts[i].uniformBindingCount; c++)
            if (allocInfo.layouts[i].uniformBindings[c].type == GN_UNIFORM_BUFFER_DESCRIPTOR) uniformBufferSize.descriptorCount++;
        pool->uniformPool->pools[pool->uniformPool->poolCount].layouts[i] = vkGryphnCreateSetLayouts(&allocInfo.layouts[i], pool->device->outputDevice->device);
    }

    uint32_t maxSets = uniformBufferSize.descriptorCount;

    VkDescriptorPoolCreateInfo poolInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .poolSizeCount = 1,
        .pPoolSizes = &uniformBufferSize,
        .maxSets = maxSets
    };

    if (vkCreateDescriptorPool(
        pool->device->outputDevice->device, &poolInfo, NULL,
        &pool->uniformPool->pools[pool->uniformPool->poolCount].pool
    ) != VK_SUCCESS)
        return NULL;

    VkDescriptorSetAllocateInfo vkAllocInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = pool->uniformPool->pools[pool->uniformPool->poolCount].pool,
        .descriptorSetCount = allocInfo.layoutCount,
        .pSetLayouts = pool->uniformPool->pools[pool->uniformPool->poolCount].layouts
    };

    VkDescriptorSet* sets = malloc(sizeof(VkDescriptorSet) * allocInfo.layoutCount);
    if (vkAllocateDescriptorSets(pool->device->outputDevice->device, &vkAllocInfo, sets) != VK_SUCCESS)
        return NULL;

    gnUniform* uniforms = malloc(sizeof(gnUniform) * allocInfo.layoutCount);
    for (int i = 0; i < allocInfo.layoutCount; i++) {
        uniforms[i] = malloc(sizeof(struct gnUniform_t));
        uniforms[i]->uniform = malloc(sizeof(struct gnPlatformUniform_t));
        uniforms[i]->uniform->set = sets[i];
    }

    pool->uniformPool->poolCount++;
    return uniforms;
}

void gnDestroyUniformPoolFn(gnUniformPool pool) {
    for (int i = 0; i < pool->uniformPool->poolCount; i++) {
        vkDestroyDescriptorPool(pool->device->outputDevice->device, pool->uniformPool->pools[i].pool, NULL);
        for (int k = 0; k < pool->uniformPool->pools[i].layoutCount; k++) {
            vkDestroyDescriptorSetLayout(pool->device->outputDevice->device, pool->uniformPool->pools[i].layouts[k], NULL);
        }
    }
    free(pool->uniformPool);
}
