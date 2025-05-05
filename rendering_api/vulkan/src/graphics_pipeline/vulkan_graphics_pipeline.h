#pragma once
#include "vulkan/vulkan.h"
#include "core/graphics_pipeline/gryphn_graphics_pipeline.h"
#include "core/output_device/gryphn_output_device.h"
#include "../output_device/vulkan_output_devices.h"
#include "vector"

struct gnPlatformGraphicsPipeline {
    VkPipelineDynamicStateCreateInfo dynamicState{};
    gnBool dynamicStatesEnabled = false;
    std::vector<VkDynamicState> dynamicStates = {};

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    VkViewport viewport{};
    VkRect2D scissor{};
    VkPipelineRasterizationStateCreateInfo rasterizer{};

    bool createdDynamicViewportState = false;
    VkPipelineViewportStateCreateInfo viewportState{};

    VkPipelineMultisampleStateCreateInfo multisampling{};
    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    VkPipelineColorBlendStateCreateInfo colorBlending{};
    VkPipelineDepthStencilStateCreateInfo depthStencil{};

    VkGraphicsPipelineCreateInfo pipelineInfo{};

    std::vector<VkDynamicState> vulkanDynamicStates = {};
    std::vector<VkPipelineShaderStageCreateInfo> shaderStages = {};

    bool dynamicStateEnabled(VkDynamicState dynamicState) {
        for (int i = 0; i < dynamicStates.size(); i++) {
            if (dynamicStates[i] == dynamicState) {
                return true;
            }
        }
        return false;
    }

    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    gnOutputDevice* outputDevice;

    VkCommandPool* commandPool;
};
