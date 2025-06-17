#pragma once
#include <core/pipelines/graphics_pipeline/gryphn_graphics_pipeline.h>
#include <vulkan/vulkan.h>

typedef struct gnPlatformGraphicsPipeline_t {
    VkPipelineDynamicStateCreateInfo dynamicState;
    gnBool isDynamic[GN_DYNAMIC_STATE_MAX];

    VkPipelineVertexInputStateCreateInfo vertexInfo;
    VkPipelineInputAssemblyStateCreateInfo inputAssembly;
    VkViewport viewport;
    VkRect2D scissor;
    VkPipelineViewportStateCreateInfo viewportState;
    VkPipelineRasterizationStateCreateInfo rasterizer;
    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    VkPipelineColorBlendStateCreateInfo colorBlending;
    VkPipelineDepthStencilStateCreateInfo depthStencil;

    // gnBool createdPipelineLayout;
    uint32_t setCount;
    VkDescriptorSetLayout* sets;
    VkPipelineLayout pipelineLayout;


    VkPipeline graphicsPipeline;



    // memory that needs to be freeed
    VkDynamicState* dynamicStates;
    VkVertexInputBindingDescription* bindingDescriptions;
    VkVertexInputAttributeDescription* attributeDescriptions;
    VkPipelineShaderStageCreateInfo* modules;
} gnPlatformGraphicsPipeline;
