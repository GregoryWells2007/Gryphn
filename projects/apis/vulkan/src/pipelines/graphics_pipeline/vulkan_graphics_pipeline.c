#include "vulkan_graphics_pipeline.h"
#include "output_device/vulkan_output_devices.h"
#include "output_device/vulkan_physical_device.h"
#include "shader_module/vulkan_shader_module.h"
#include "renderpass/vulkan_render_pass_descriptor.h"
#include "uniforms/vulkan_uniform_layout.h"
#include "vulkan_result_converter.h"

VkDynamicState vkGryphnDynamicStateToVulkanDynamicState(gnDynamicState state) {
    switch (state) {
    case GN_DYNAMIC_VIEWPORT: return VK_DYNAMIC_STATE_VIEWPORT;
    case GN_DYNAMIC_SCISSOR: return VK_DYNAMIC_STATE_SCISSOR;

    case GN_DYNAMIC_STATE_MAX: return VK_DYNAMIC_STATE_MAX_ENUM;
    }
}

VkPrimitiveTopology vkGryphnPrimitiveType(gnPrimitiveType primitiveType) {
    switch (primitiveType) {
    case GN_PRIMITIVE_POINTS: return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
    case GN_PRIMITIVE_LINES: return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
    case GN_PRIMITIVE_LINE_STRIP: return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
    case GN_PRIMITIVE_TRIANGLES: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    case GN_PRIMITIVE_TRIANGLE_STRIP: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
    }
}

VkPolygonMode vkGryphnPolygonMode(gnFillMode fillMode) {
    switch (fillMode) {
    case GN_FILL_MODE_FILL: return VK_POLYGON_MODE_FILL;
    case GN_FILL_MODE_LINE: return VK_POLYGON_MODE_LINE;
    case GN_FILL_MODE_POINT: return VK_POLYGON_MODE_POINT;
    }
}

VkCullModeFlags vkGryphnCullMode(gnCullFace face) {
    switch (face) {
        case GN_CULL_FACE_NONE: return VK_CULL_MODE_NONE;
        case GN_CULL_FACE_BACK: return VK_CULL_MODE_BACK_BIT;
        case GN_CULL_FACE_FRONT: return VK_CULL_MODE_FRONT_BIT;
    }
}

VkBlendFactor vkGryphnBlendFactor(gnBlendFactor factor) {
    switch (factor) {
    case GN_BLEND_FACTOR_ZERO: return VK_BLEND_FACTOR_ZERO;
    case GN_BLEND_FACTOR_ONE: return VK_BLEND_FACTOR_ONE;
    case GN_BLEND_FACTOR_SRC_ALPHA: return VK_BLEND_FACTOR_SRC_ALPHA;
    case GN_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA: return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    }
}

VkBlendOp vkGryphnBlendOperation(gnBlendOperation operation) {
    switch(operation) {
    case GN_OPERATION_ADD: return VK_BLEND_OP_ADD;
    }
}

VkFormat vkGryphnVertexFormat(gnVertexFormat format) {
    switch (format) {
    case GN_FLOAT2: return VK_FORMAT_R32G32_SFLOAT;
    case GN_FLOAT3: return VK_FORMAT_R32G32B32_SFLOAT;
    }
}

VkCompareOp vkGrypnCompareOperation(gnCompareOperation operation) {
    switch(operation) {
    case GN_COMPARE_NEVER: return VK_COMPARE_OP_NEVER;
    case GN_COMPARE_LESS: return VK_COMPARE_OP_LESS;
    case GN_COMPARE_EQUAL: return VK_COMPARE_OP_EQUAL;
    case GN_COMPARE_LESS_OR_EQUAL: return VK_COMPARE_OP_LESS_OR_EQUAL;
    case GN_COMPARE_GREATER: return VK_COMPARE_OP_GREATER;
    case GN_COMPARE_NOT_EQUAL: return VK_COMPARE_OP_NOT_EQUAL;
    case GN_COMPARE_GREATER_OR_EQUAL: return VK_COMPARE_OP_GREATER_OR_EQUAL;
    case GN_COMPARE_ALWAYS: return VK_COMPARE_OP_ALWAYS;
    }
}

VkStencilOp vkGryphnStencilOperation(gnStencilOperation operation) {
    switch(operation) {
    case GN_STENCIL_KEEP: return VK_STENCIL_OP_KEEP;
    case GN_STENCIL_ZERO: return VK_STENCIL_OP_ZERO;
    case GN_STENCIL_REPLACE: return VK_STENCIL_OP_REPLACE;
    case GN_STENCIL_INCREMENT_AND_CLAMP: return VK_STENCIL_OP_INCREMENT_AND_CLAMP;
    case GN_STENCIL_DECREMENT_AND_CLAMP: return VK_STENCIL_OP_DECREMENT_AND_CLAMP;
    case GN_STENCIL_INVERT: return VK_STENCIL_OP_INVERT;
    case GN_STENCIL_INCREMENT_AND_WRAP: return VK_STENCIL_OP_INCREMENT_AND_WRAP;
    case GN_STENCIL_DECREMENT_AND_WRAP: return VK_STENCIL_OP_DECREMENT_AND_WRAP;
    }
}

gnReturnCode createGraphicsPipeline(gnGraphicsPipeline graphicsPipeline, gnDevice device, gnGraphicsPipelineInfo info) {
    graphicsPipeline->graphicsPipeline = malloc(sizeof(gnPlatformGraphicsPipeline));
    for (int i = 0; i < GN_DYNAMIC_STATE_MAX; i++) graphicsPipeline->graphicsPipeline->isDynamic[i] = GN_FALSE;

    graphicsPipeline->graphicsPipeline->dynamicStates = malloc(sizeof(VkDynamicState) * info.dynamicState.dynamicStateCount);
    for (int i = 0; i < info.dynamicState.dynamicStateCount; i++) {
        graphicsPipeline->graphicsPipeline->isDynamic[info.dynamicState.dynamicStates[i]] = GN_TRUE;
        graphicsPipeline->graphicsPipeline->dynamicStates[i] = vkGryphnDynamicStateToVulkanDynamicState(info.dynamicState.dynamicStates[i]);
    }

    graphicsPipeline->graphicsPipeline->dynamicState = (VkPipelineDynamicStateCreateInfo){
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        .dynamicStateCount = info.dynamicState.dynamicStateCount,
        .pDynamicStates = graphicsPipeline->graphicsPipeline->dynamicStates
    };

    int vertexAttributeCount = 0;
    graphicsPipeline->graphicsPipeline->bindingDescriptions = malloc(sizeof(VkVertexInputBindingDescription) * info.shaderInputLayout.bufferCount);
    for (int i = 0; i < info.shaderInputLayout.bufferCount; i++) {
        graphicsPipeline->graphicsPipeline->bindingDescriptions[i].binding = info.shaderInputLayout.bufferAttributes[i].binding;
        graphicsPipeline->graphicsPipeline->bindingDescriptions[i].stride = info.shaderInputLayout.bufferAttributes[i].size;
        graphicsPipeline->graphicsPipeline->bindingDescriptions[i].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        vertexAttributeCount += info.shaderInputLayout.bufferAttributes[i].attributeCount;
    }
    graphicsPipeline->graphicsPipeline->attributeDescriptions = malloc(sizeof(VkVertexInputAttributeDescription) * vertexAttributeCount);
    for (int i = 0, j = 0; j < info.shaderInputLayout.bufferCount; j++) {
        for (int k = 0; k < info.shaderInputLayout.bufferAttributes[j].attributeCount; k++) {
            graphicsPipeline->graphicsPipeline->attributeDescriptions[i].binding = j;
            graphicsPipeline->graphicsPipeline->attributeDescriptions[i].location = info.shaderInputLayout.bufferAttributes[j].attributes[k].location;
            graphicsPipeline->graphicsPipeline->attributeDescriptions[i].offset = info.shaderInputLayout.bufferAttributes[j].attributes[k].offset;
            graphicsPipeline->graphicsPipeline->attributeDescriptions[i].format = vkGryphnVertexFormat(info.shaderInputLayout.bufferAttributes[j].attributes[k].format);
            i++;
        }
    }

    graphicsPipeline->graphicsPipeline->vertexInfo = (VkPipelineVertexInputStateCreateInfo){
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .vertexBindingDescriptionCount = info.shaderInputLayout.bufferCount,
        .pVertexBindingDescriptions = graphicsPipeline->graphicsPipeline->bindingDescriptions,
        .vertexAttributeDescriptionCount = vertexAttributeCount,
        .pVertexAttributeDescriptions = graphicsPipeline->graphicsPipeline->attributeDescriptions
    };

    graphicsPipeline->graphicsPipeline->inputAssembly = (VkPipelineInputAssemblyStateCreateInfo){
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .topology = vkGryphnPrimitiveType(info.primitiveType),
        .primitiveRestartEnable = VK_FALSE
    };

    graphicsPipeline->graphicsPipeline->viewportState = (VkPipelineViewportStateCreateInfo){
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount = 1,
        .scissorCount = 1
    };

    if (!graphicsPipeline->graphicsPipeline->isDynamic[GN_DYNAMIC_VIEWPORT]) {
        graphicsPipeline->graphicsPipeline->viewport = (VkViewport) {
            .x = info.viewport.position.x,
            .y = info.viewport.position.y,
            .width  = info.viewport.size.x,
            .height = info.viewport.size.y,
            .minDepth = info.viewport.minDepth,
            .maxDepth = info.viewport.maxDepth
        };
        graphicsPipeline->graphicsPipeline->viewportState.pViewports = &graphicsPipeline->graphicsPipeline->viewport;
    }

    if (!graphicsPipeline->graphicsPipeline->isDynamic[GN_DYNAMIC_SCISSOR]) {
        graphicsPipeline->graphicsPipeline->scissor = (VkRect2D){
            .offset = { info.scissor.position.x, info.scissor.position.y },
            .extent = { info.scissor.size.x, info.scissor.size.y }
        };
        graphicsPipeline->graphicsPipeline->viewportState.pScissors = &graphicsPipeline->graphicsPipeline->scissor;
    }

    graphicsPipeline->graphicsPipeline->rasterizer = (VkPipelineRasterizationStateCreateInfo){
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .polygonMode = vkGryphnPolygonMode(info.fillMode),
        .lineWidth = 1.0f,
        .frontFace = ( info.cullMode.direction == GN_DIRECTION_CLOCK_WISE ) ? VK_FRONT_FACE_COUNTER_CLOCKWISE : VK_FRONT_FACE_CLOCKWISE,
        .cullMode = vkGryphnCullMode(info.cullMode.face),
        .depthBiasEnable = VK_FALSE,
        .depthBiasConstantFactor = 0.0f,
        .depthBiasClamp = 0.0f,
        .depthBiasSlopeFactor = 0.0f
    };

    VkPipelineMultisampleStateCreateInfo multisampling = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .sampleShadingEnable = VK_FALSE,
        .rasterizationSamples = gnSampleCountToVulkan(info.multisample.samples)
    };

    graphicsPipeline->graphicsPipeline->colorBlendAttachment = (VkPipelineColorBlendAttachmentState){
        .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
        .blendEnable = ( info.colorBlending.enable == GN_TRUE ) ? VK_TRUE : VK_FALSE,
        .srcColorBlendFactor = vkGryphnBlendFactor(info.colorBlending.sourceColorBlendFactor),
        .dstColorBlendFactor = vkGryphnBlendFactor(info.colorBlending.destinationColorBlendFactor),
        .colorBlendOp = vkGryphnBlendOperation(info.colorBlending.colorBlendOperation),
        .srcAlphaBlendFactor = vkGryphnBlendFactor(info.colorBlending.sourceAlphaBlendFactor),
        .dstAlphaBlendFactor = vkGryphnBlendFactor(info.colorBlending.destinationAlphaBlendFactor),
        .alphaBlendOp = vkGryphnBlendOperation(info.colorBlending.alphaBlendOperation),
    };

    graphicsPipeline->graphicsPipeline->colorBlending = (VkPipelineColorBlendStateCreateInfo){
        .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .logicOpEnable = VK_FALSE,
        .logicOp = VK_LOGIC_OP_COPY,
        .attachmentCount = 1,
        .pAttachments = &graphicsPipeline->graphicsPipeline->colorBlendAttachment,
        .blendConstants[0] = 0.0f,
        .blendConstants[1] = 0.0f,
        .blendConstants[2] = 0.0f,
        .blendConstants[3] = 0.0f
    };

    graphicsPipeline->graphicsPipeline->depthStencil = (VkPipelineDepthStencilStateCreateInfo){
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
        .depthWriteEnable = info.depthStencil.depthWriteEnable,
        .depthTestEnable = info.depthStencil.depthWriteEnable,
        .depthCompareOp = vkGrypnCompareOperation(info.depthStencil.operation),
        .depthBoundsTestEnable = VK_FALSE,
        .stencilTestEnable = info.depthStencil.stencilTestEnable,
    };

    if (info.depthStencil.stencilTestEnable) {
        graphicsPipeline->graphicsPipeline->depthStencil.front = (VkStencilOpState){
            .failOp = vkGryphnStencilOperation(info.depthStencil.front.failOperation),
            .passOp = vkGryphnStencilOperation(info.depthStencil.front.passOperation),
            .depthFailOp = vkGryphnStencilOperation(info.depthStencil.front.depthFailOperation),
            .compareOp = vkGrypnCompareOperation(info.depthStencil.front.compareOperation),
            .compareMask = info.depthStencil.front.compareMask,
            .writeMask = info.depthStencil.front.writeMask,
            .reference = info.depthStencil.front.reference,
        };

        graphicsPipeline->graphicsPipeline->depthStencil.back = (VkStencilOpState){
            .failOp = vkGryphnStencilOperation(info.depthStencil.back.failOperation),
            .passOp = vkGryphnStencilOperation(info.depthStencil.back.passOperation),
            .depthFailOp = vkGryphnStencilOperation(info.depthStencil.back.depthFailOperation),
            .compareOp = vkGrypnCompareOperation(info.depthStencil.back.compareOperation),
            .compareMask = info.depthStencil.back.compareMask,
            .writeMask = info.depthStencil.back.writeMask,
            .reference = info.depthStencil.back.reference,
        };
    }

    graphicsPipeline->graphicsPipeline->setCount = info.uniformLayout.setCount;
    graphicsPipeline->graphicsPipeline->sets = malloc(sizeof(VkDescriptorSetLayout) * info.uniformLayout.setCount);
    for (int i = 0; i < info.uniformLayout.setCount; i++) graphicsPipeline->graphicsPipeline->sets[i] = vkGryphnCreateSetLayouts(&info.uniformLayout.sets[i], device->outputDevice->device);

    graphicsPipeline->graphicsPipeline->ranges = malloc(sizeof(VkPushConstantRange) * info.uniformLayout.pushConstantCount);
    for (int i = 0; i < info.uniformLayout.pushConstantCount; i++) {
        graphicsPipeline->graphicsPipeline->ranges[i] = (VkPushConstantRange) {
            .offset = info.uniformLayout.pushConstants[i].offset,
            .size = info.uniformLayout.pushConstants[i].size,
            .stageFlags = vkGryphnShaderModuleStage(info.uniformLayout.pushConstants[i].stage)
        };
    }

    VkPipelineLayoutCreateInfo pipelineLayoutInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .setLayoutCount = graphicsPipeline->graphicsPipeline->setCount,
        pipelineLayoutInfo.pSetLayouts = graphicsPipeline->graphicsPipeline->sets,
        pipelineLayoutInfo.pushConstantRangeCount = info.uniformLayout.pushConstantCount,
        pipelineLayoutInfo.pPushConstantRanges = graphicsPipeline->graphicsPipeline->ranges
    };

    VkResult pipelineCode = vkCreatePipelineLayout(device->outputDevice->device, &pipelineLayoutInfo, NULL, &graphicsPipeline->graphicsPipeline->pipelineLayout);
    if (pipelineCode!= VK_SUCCESS)
        return VkResultToGnReturnCode(pipelineCode);

    graphicsPipeline->graphicsPipeline->modules = malloc(sizeof(VkPipelineShaderStageCreateInfo) * info.shaderModuleCount);
    for (int i = 0; i < info.shaderModuleCount; i++) {
        graphicsPipeline->graphicsPipeline->modules[i] = info.shaderModules[i]->shaderModule->shaderStageInfo;
    }

    VkGraphicsPipelineCreateInfo pipelineInfo = {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .stageCount = info.shaderModuleCount,
        .pStages = graphicsPipeline->graphicsPipeline->modules,
        .pVertexInputState = &graphicsPipeline->graphicsPipeline->vertexInfo,
        .pInputAssemblyState = &graphicsPipeline->graphicsPipeline->inputAssembly,
        .pViewportState = &graphicsPipeline->graphicsPipeline->viewportState,
        .pRasterizationState = &graphicsPipeline->graphicsPipeline->rasterizer,
        .pMultisampleState = &multisampling,
        .pDepthStencilState = &graphicsPipeline->graphicsPipeline->depthStencil,
        .pColorBlendState = &graphicsPipeline->graphicsPipeline->colorBlending,
        .pDynamicState = &graphicsPipeline->graphicsPipeline->dynamicState,
        .layout = graphicsPipeline->graphicsPipeline->pipelineLayout,
        .renderPass = info.renderPassDescriptor->renderPassDescriptor->renderPass,
        .subpass = info.subpassIndex,
        .basePipelineHandle = VK_NULL_HANDLE,
        .basePipelineIndex = -1,
    };

    return VkResultToGnReturnCode(vkCreateGraphicsPipelines(device->outputDevice->device, VK_NULL_HANDLE, 1, &pipelineInfo, NULL, &graphicsPipeline->graphicsPipeline->graphicsPipeline));
}

void destroyGraphicsPipeline(gnGraphicsPipeline graphicsPipeline) {
    free(graphicsPipeline->graphicsPipeline->dynamicStates);
    free(graphicsPipeline->graphicsPipeline->bindingDescriptions);
    free(graphicsPipeline->graphicsPipeline->attributeDescriptions);
    free(graphicsPipeline->graphicsPipeline->ranges);
    for (int i = 0; i < graphicsPipeline->graphicsPipeline->setCount; i++)
        vkDestroyDescriptorSetLayout(graphicsPipeline->device->outputDevice->device, graphicsPipeline->graphicsPipeline->sets[i], NULL);
    free(graphicsPipeline->graphicsPipeline->modules);
    vkDestroyPipeline(graphicsPipeline->device->outputDevice->device, graphicsPipeline->graphicsPipeline->graphicsPipeline, NULL);
    vkDestroyPipelineLayout(graphicsPipeline->device->outputDevice->device, graphicsPipeline->graphicsPipeline->pipelineLayout, NULL);
    free(graphicsPipeline->graphicsPipeline);
}
