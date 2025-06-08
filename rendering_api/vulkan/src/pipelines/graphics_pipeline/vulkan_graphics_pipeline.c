#include "vulkan_graphics_pipeline.h"
#include "output_device/vulkan_output_devices.h"
#include "shader_module/vulkan_shader_module.h"
#include "renderpass/vulkan_render_pass_descriptor.h"

VkDynamicState vkGryphnDynamicStateToVulkanDynamicState(enum gnDynamicState_e state) {
    switch (state) {
    case GN_DYNAMIC_VIEWPORT: return VK_DYNAMIC_STATE_VIEWPORT;
    case GN_DYNAMIC_SCISSOR: return VK_DYNAMIC_STATE_SCISSOR;

    case GN_DYNAMIC_STATE_MAX: return VK_DYNAMIC_STATE_MAX_ENUM;
    }
}

VkPrimitiveTopology vkGryphnPrimitiveType(enum gnPrimitiveType_e primitiveType) {
    switch (primitiveType) {
    case GN_PRIMITIVE_POINTS: return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
    case GN_PRIMITIVE_LINES: return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
    case GN_PRIMITIVE_LINE_STRIP: return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
    case GN_PRIMITIVE_TRIANGLES: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    case GN_PRIMITIVE_TRIANGLE_STRIP: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
    }
}

VkPolygonMode vkGryphnPolygonMode(enum gnFillMode_e fillMode) {
    switch (fillMode) {
    case GN_FILL_MODE_FILL: return VK_POLYGON_MODE_FILL;
    case GN_FILL_MODE_LINE: return VK_POLYGON_MODE_LINE;
    case GN_FILL_MODE_POINT: return VK_POLYGON_MODE_POINT;
    }
}

VkCullModeFlags vkGryphnCullMode(enum gnCullFace_e face) {
    switch (face) {
        case GN_CULL_FACE_NONE: return VK_CULL_MODE_NONE;
        case GN_CULL_FACE_BACK: return VK_CULL_MODE_BACK_BIT;
        case GN_CULL_FACE_FRONT: return VK_CULL_MODE_FRONT_BIT;
    }
}

VkBlendFactor vkGryphnBlendFactor(enum gnBlendFactor_e factor) {
    switch (factor) {
    case GN_BLEND_FACTOR_ZERO: return VK_BLEND_FACTOR_ZERO;
    case GN_BLEND_FACTOR_ONE: return VK_BLEND_FACTOR_ONE;
    case GN_BLEND_FACTOR_SRC_ALPHA: return VK_BLEND_FACTOR_SRC_ALPHA;
    case GN_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA: return VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    }
}

VkBlendOp vkGryphnBlendOperation(enum gnBlendOperation_e operation) {
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

VkDescriptorType vkGryphnUniformType(gnUniformType type) {
    switch(type) {
    case GN_UNIFORM_BUFFER_DESCRIPTOR: return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    }
}

gnReturnCode gnCreateGraphicsPipelineFn(struct gnGraphicsPipeline_t* graphicsPipeline, struct gnOutputDevice_t* device, struct gnGraphicsPipelineInfo_t info) {
    graphicsPipeline->graphicsPipeline = malloc(sizeof(gnPlatformGraphicsPipeline));

    for (int i = 0; i < GN_DYNAMIC_STATE_MAX; i++) graphicsPipeline->graphicsPipeline->isDynamic[i] = gnFalse;

    VkDynamicState* dynamicStates = malloc(sizeof(VkDynamicState) * info.dynamicState.dynamicStateCount);
    for (int i = 0; i < info.dynamicState.dynamicStateCount; i++) {
        graphicsPipeline->graphicsPipeline->isDynamic[info.dynamicState.dynamicStates[i]] = gnTrue;
        dynamicStates[i] = vkGryphnDynamicStateToVulkanDynamicState(info.dynamicState.dynamicStates[i]);
    }

    graphicsPipeline->graphicsPipeline->dynamicState = (VkPipelineDynamicStateCreateInfo){
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        .dynamicStateCount = info.dynamicState.dynamicStateCount,
        .pDynamicStates = dynamicStates
    };

    int vertexAttributeCount = 0;
    VkVertexInputAttributeDescription* attributeDescriptions = NULL;
    VkVertexInputBindingDescription* bindingDescriptions = malloc(sizeof(VkVertexInputBindingDescription) * info.shaderInputLayout.bufferCount);
    for (int i = 0; i < info.shaderInputLayout.bufferCount; i++) {
        bindingDescriptions[i].binding = info.shaderInputLayout.bufferAttributes[i].binding;
        bindingDescriptions[i].stride = info.shaderInputLayout.bufferAttributes[i].size;
        bindingDescriptions[i].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        vertexAttributeCount += info.shaderInputLayout.bufferAttributes[i].attributeCount;
    }
    attributeDescriptions = malloc(sizeof(VkVertexInputBindingDescription) * vertexAttributeCount);
    for (int i = 0, j = 0; j < info.shaderInputLayout.bufferCount; j++) {
        for (int k = 0; k < info.shaderInputLayout.bufferAttributes[j].attributeCount; k++) {
            attributeDescriptions[i].binding = j;
            attributeDescriptions[i].location = info.shaderInputLayout.bufferAttributes[j].attributes[k].location;
            attributeDescriptions[i].offset = info.shaderInputLayout.bufferAttributes[j].attributes[k].offset;
            attributeDescriptions[i].format = vkGryphnVertexFormat(info.shaderInputLayout.bufferAttributes[j].attributes[k].format);
            i++;
        }
    }

    graphicsPipeline->graphicsPipeline->vertexInfo = (VkPipelineVertexInputStateCreateInfo){
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .vertexBindingDescriptionCount = info.shaderInputLayout.bufferCount,
        .pVertexBindingDescriptions = bindingDescriptions,
        .vertexAttributeDescriptionCount = vertexAttributeCount,
        .pVertexAttributeDescriptions = attributeDescriptions
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
        .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT
    };

    graphicsPipeline->graphicsPipeline->colorBlendAttachment = (VkPipelineColorBlendAttachmentState){
        .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
        .blendEnable = ( info.colorBlending.enable == gnTrue ) ? VK_TRUE : VK_FALSE,
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

    graphicsPipeline->graphicsPipeline->setCount = info.uniformLayout.uniformBindingCount;
    graphicsPipeline->graphicsPipeline->sets = malloc(sizeof(VkDescriptorSetLayoutBinding) * info.uniformLayout.uniformBindingCount);
    for (int i = 0; i < info.uniformLayout.uniformBindingCount; i++) {
        VkDescriptorSetLayoutBinding setLayout = {
            .binding = info.uniformLayout.uniformBindings[i].binding,
            .descriptorCount = 1,
            .descriptorType = vkGryphnUniformType(info.uniformLayout.uniformBindings[i].type),
            .stageFlags = vkGryphnShaderModuleStage(info.uniformLayout.uniformBindings[i].stage)
        };

        VkDescriptorSetLayoutCreateInfo info = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
            .bindingCount = 1,
            .pBindings = &setLayout
        };

        if (vkCreateDescriptorSetLayout(device->outputDevice->device, &info, NULL, &graphicsPipeline->graphicsPipeline->sets[i]) != VK_SUCCESS) {
            return GN_FAILED_TO_CREATE_UNIFORM_LAYOUT;
        }
    }


    VkPipelineLayoutCreateInfo pipelineLayoutInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .setLayoutCount = graphicsPipeline->graphicsPipeline->setCount,
        pipelineLayoutInfo.pSetLayouts = graphicsPipeline->graphicsPipeline->sets,
        pipelineLayoutInfo.pushConstantRangeCount = 0,
        pipelineLayoutInfo.pPushConstantRanges = NULL
    };

    if (vkCreatePipelineLayout(device->outputDevice->device, &pipelineLayoutInfo, NULL, &graphicsPipeline->graphicsPipeline->pipelineLayout) != VK_SUCCESS) {
        return GN_FAILED_TO_CREATE_UNIFORM_LAYOUT;
    }

    VkPipelineShaderStageCreateInfo* modules = malloc(sizeof(VkPipelineShaderStageCreateInfo) * info.shaderModuleCount);
    for (int i = 0; i < info.shaderModuleCount; i++) {
        modules[i] = info.shaderModules[i]->shaderModule->shaderStageInfo;
    }

    VkGraphicsPipelineCreateInfo pipelineInfo = {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .stageCount = info.shaderModuleCount,
        .pStages = modules,
        .pVertexInputState = &graphicsPipeline->graphicsPipeline->vertexInfo,
        .pInputAssemblyState = &graphicsPipeline->graphicsPipeline->inputAssembly,
        .pViewportState = &graphicsPipeline->graphicsPipeline->viewportState,
        .pRasterizationState = &graphicsPipeline->graphicsPipeline->rasterizer,
        .pMultisampleState = &multisampling,
        .pDepthStencilState = NULL,
        .pColorBlendState = &graphicsPipeline->graphicsPipeline->colorBlending,
        .pDynamicState = &graphicsPipeline->graphicsPipeline->dynamicState,
        .layout = graphicsPipeline->graphicsPipeline->pipelineLayout,
        .renderPass = info.renderPassDescriptor->renderPassDescriptor->renderPass,
        .subpass = info.subpassIndex,
        .basePipelineHandle = VK_NULL_HANDLE,
        .basePipelineIndex = -1,
    };

    if (vkCreateGraphicsPipelines(device->outputDevice->device, VK_NULL_HANDLE, 1, &pipelineInfo, NULL, &graphicsPipeline->graphicsPipeline->graphicsPipeline) != VK_SUCCESS) {
        return GN_FAILED_TO_CREATE_GRAPHICS_PIPELINE;
    }

    free(dynamicStates);
    free(bindingDescriptions);
    free(attributeDescriptions);
    return GN_SUCCESS;
}

void gnDestroyGraphicsPipelineFn(struct gnGraphicsPipeline_t *graphicsPipeline) {
    for (int i = 0; i < graphicsPipeline->graphicsPipeline->setCount; i++)
        vkDestroyDescriptorSetLayout(graphicsPipeline->device->outputDevice->device, graphicsPipeline->graphicsPipeline->sets[i], NULL);
    vkDestroyPipelineLayout(graphicsPipeline->device->outputDevice->device, graphicsPipeline->graphicsPipeline->pipelineLayout, NULL);
    vkDestroyPipeline(graphicsPipeline->device->outputDevice->device, graphicsPipeline->graphicsPipeline->graphicsPipeline, NULL);

    free(graphicsPipeline->graphicsPipeline);
}
