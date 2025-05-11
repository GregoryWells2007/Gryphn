#include "vulkan_graphics_pipeline.h"
#include "../shaders/vulkan_shader_module.h"
#include "vulkan_renderpass.h"
#include "../vertex_buffers/vertex_descriptions/vulkan_vertex_description.h"
#include "../uniform_descriptor/vulkan_uniform_layout.h"
#include "../push_constant/vulkan_push_constant.h"

void vulkanCreateGraphicsPipeline(gnGraphicsPipeline* pipeline) {
    if (pipeline->graphicsPipeline == nullptr) pipeline->graphicsPipeline = new gnPlatformGraphicsPipeline();

    pipeline->graphicsPipeline->inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    pipeline->graphicsPipeline->rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    pipeline->graphicsPipeline->rasterizer.rasterizerDiscardEnable = VK_FALSE;
    pipeline->graphicsPipeline->dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    pipeline->graphicsPipeline->viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    pipeline->graphicsPipeline->multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    pipeline->graphicsPipeline->colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    pipeline->graphicsPipeline->colorBlending.logicOpEnable = VK_FALSE;
    pipeline->graphicsPipeline->colorBlending.attachmentCount = 1;
    pipeline->graphicsPipeline->colorBlending.blendConstants[0] = 0.0f;
    pipeline->graphicsPipeline->colorBlending.blendConstants[1] = 0.0f;
    pipeline->graphicsPipeline->colorBlending.blendConstants[2] = 0.0f;
    pipeline->graphicsPipeline->colorBlending.blendConstants[3] = 0.0f;
    pipeline->graphicsPipeline->depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    pipeline->graphicsPipeline->pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
}

GN_EXPORT void gnGraphicsPipelineSetPrimativeFn(gnGraphicsPipeline& pipeline, gnPrimative primative) {
    vulkanCreateGraphicsPipeline(&pipeline);
    pipeline.primative = primative;

    if (primative == GN_POINTS) pipeline.graphicsPipeline->inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
    else if (primative == GN_LINES) pipeline.graphicsPipeline->inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
    else if (primative == GN_LINE_STRIP) pipeline.graphicsPipeline->inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
    else if (primative == GN_TRIANGLES) pipeline.graphicsPipeline->inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    else { /* TODO: throw debugger runtime errors */ }

    pipeline.graphicsPipeline->inputAssembly.primitiveRestartEnable = VK_FALSE;
}

GN_EXPORT void gnGraphicsPipelineEnableDynamicStatesFn(gnGraphicsPipeline& pipeline, const gnBool enable) {
    vulkanCreateGraphicsPipeline(&pipeline);
    pipeline.graphicsPipeline->dynamicStatesEnabled = true;

    pipeline.graphicsPipeline->dynamicState.dynamicStateCount = static_cast<uint32_t>(pipeline.graphicsPipeline->dynamicStates.size());
    pipeline.graphicsPipeline->dynamicState.pDynamicStates = pipeline.graphicsPipeline->dynamicStates.data();
}

GN_EXPORT void gnGraphicsPipelineEnableDynamicStateFn(gnGraphicsPipeline& pipeline, const gnDynamicState state) {
    vulkanCreateGraphicsPipeline(&pipeline);
    VkDynamicState dynamicState;
    if (state == GN_DYNAMIC_STATE_VIEWPORT) dynamicState = VK_DYNAMIC_STATE_VIEWPORT;
    if (state == GN_DYNAMIC_STATE_SCISSOR) dynamicState = VK_DYNAMIC_STATE_SCISSOR;
    pipeline.graphicsPipeline->dynamicStates.push_back(dynamicState);
}

GN_EXPORT void _gnGraphicsPipelineSetViewportFn(gnGraphicsPipeline& pipeline, gnUInt2 position, gnUInt2 size, gnFloat minDepth, gnFloat maxDepth) {
    vulkanCreateGraphicsPipeline(&pipeline);
    pipeline.graphicsPipeline->viewport.x = position.x;
    pipeline.graphicsPipeline->viewport.y = position.y;
    pipeline.graphicsPipeline->viewport.width = (float)size.x;
    pipeline.graphicsPipeline->viewport.height = (float)size.y;
    pipeline.graphicsPipeline->viewport.minDepth = minDepth;
    pipeline.graphicsPipeline->viewport.maxDepth = maxDepth;
    pipeline.graphicsPipeline->viewportState.viewportCount = 1;

    if (!pipeline.graphicsPipeline->dynamicStateEnabled(VK_DYNAMIC_STATE_VIEWPORT)) {
        pipeline.graphicsPipeline->viewportState.pViewports = &pipeline.graphicsPipeline->viewport;
    }
}
GN_EXPORT void gnGraphicsPipelineSetCropFn(gnGraphicsPipeline& pipeline, gnInt2 position, gnUInt2 size) {
    vulkanCreateGraphicsPipeline(&pipeline);
    pipeline.graphicsPipeline->scissor.offset = { position.x, position.y };
    pipeline.graphicsPipeline->scissor.extent = {size.x, size.y};
    pipeline.graphicsPipeline->viewportState.scissorCount = 1;

    if (!pipeline.graphicsPipeline->dynamicStateEnabled(VK_DYNAMIC_STATE_VIEWPORT)) {
        pipeline.graphicsPipeline->viewportState.pScissors = &pipeline.graphicsPipeline->scissor;
    }
}
GN_EXPORT void gnGraphicsPipelineSetDepthClampFn(gnGraphicsPipeline& pipeline, gnBool enableDepthClamp) {
    vulkanCreateGraphicsPipeline(&pipeline);
    pipeline.graphicsPipeline->rasterizer.depthClampEnable = (enableDepthClamp == true) ? VK_TRUE : VK_FALSE;
}
GN_EXPORT void gnGraphicsPipelineSetFillModeFn(gnGraphicsPipeline& pipeline, gnFillMode fillMode) {
    vulkanCreateGraphicsPipeline(&pipeline);
    VkPolygonMode polygoneMode = VK_POLYGON_MODE_FILL;
    if (fillMode == GN_POLYGON_FILLMODE_FILL) polygoneMode = VK_POLYGON_MODE_FILL;
    if (fillMode == GN_POLYGON_FILLMODE_LINES) polygoneMode = VK_POLYGON_MODE_LINE;
    if (fillMode == GN_POLYGON_FILLMODE_POINTS) polygoneMode = VK_POLYGON_MODE_POINT;

    pipeline.graphicsPipeline->rasterizer.polygonMode = polygoneMode;
}
GN_EXPORT void gnGraphicsPipelineSetLineWidthFn(gnGraphicsPipeline& pipeline, gnFloat lineWidth) {
    vulkanCreateGraphicsPipeline(&pipeline);
    pipeline.graphicsPipeline->rasterizer.lineWidth = lineWidth;
}
GN_EXPORT void gnGraphicsPipelineSetCullModeFn(gnGraphicsPipeline& pipeline, gnCullMode cullMode, gnFrontFaceDirection direction) {
    vulkanCreateGraphicsPipeline(&pipeline);
    VkCullModeFlags cullmode;
    if(cullMode == GN_CULL_NONE) pipeline.graphicsPipeline->rasterizer.cullMode = VK_CULL_MODE_NONE;
    else if(cullMode == GN_CULL_BACKFACE) pipeline.graphicsPipeline->rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    else if(cullMode == GN_CULL_FRONTFACE) pipeline.graphicsPipeline->rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    // else if(cullMode == GN_CULL_ALL) pipeline.graphicsPipeline->rasterizer.cullMode = VK_CULL_MODE_FRONT_AND_BACK;

    pipeline.graphicsPipeline->rasterizer.frontFace = (direction == GN_CLOCKWISE) ? VK_FRONT_FACE_CLOCKWISE : VK_FRONT_FACE_COUNTER_CLOCKWISE;
}
GN_EXPORT void gnGraphicsPipelineSetMultisamplingFn(gnGraphicsPipeline& pipeline, gnBool enableMultisampling) {
    vulkanCreateGraphicsPipeline(&pipeline);
    if (enableMultisampling) { /* TODO: Debugger needs to throw some errors */ return; }

    pipeline.graphicsPipeline->multisampling.sampleShadingEnable = VK_FALSE;
    pipeline.graphicsPipeline->multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
}


GN_EXPORT void gnGraphicsPipelineSetColorBlendFn(gnGraphicsPipeline& pipeline, gnBool colorBlend) {
    vulkanCreateGraphicsPipeline(&pipeline);
    // if (colorBlend) { /* TODO: Debugger needs to throw some errors */ return; }

    pipeline.graphicsPipeline->colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    pipeline.graphicsPipeline->colorBlendAttachment.blendEnable = VK_TRUE;

    pipeline.graphicsPipeline->colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
    pipeline.graphicsPipeline->colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
    pipeline.graphicsPipeline->colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    pipeline.graphicsPipeline->colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    pipeline.graphicsPipeline->colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    pipeline.graphicsPipeline->colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;

    pipeline.graphicsPipeline->colorBlending.pAttachments = &pipeline.graphicsPipeline->colorBlendAttachment;

}
GN_EXPORT void gnGraphicsPipelineSetRenderPassFn(gnGraphicsPipeline& pipeline, gnRenderPass& renderpass) {
    vulkanCreateGraphicsPipeline(&pipeline);
    pipeline.renderPass = &renderpass;

    pipeline.graphicsPipeline->pipelineInfo.renderPass = renderpass.renderpass->renderPass;
    pipeline.graphicsPipeline->pipelineInfo.subpass = 0;
}

GN_EXPORT void gnGraphicsPipelineBindShaderFn(gnGraphicsPipeline& pipeline, const gnShader& shader) {
    vulkanCreateGraphicsPipeline(&pipeline);
    pipeline.graphicsPipeline->pipelineInfo.stageCount = gnListLength(shader.shaderModules);

    for (int i = 0; i < gnListLength(shader.shaderModules); i++) {
        pipeline.graphicsPipeline->shaderStages.push_back(shader.shaderModules[i].shaderModule->stageCreateInfo);
    }


    pipeline.graphicsPipeline->pipelineInfo.pStages = pipeline.graphicsPipeline->shaderStages.data();
}

GN_EXPORT void gnGraphicsPipelineSetVertexDescriptionFn(gnGraphicsPipeline& pipeline, const gnVertexDescription& vertexDescription) {
    vulkanCreateGraphicsPipeline(&pipeline);
    pipeline.graphicsPipeline->vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    pipeline.graphicsPipeline->vertexInputInfo.vertexBindingDescriptionCount = 1;
    pipeline.graphicsPipeline->vertexInputInfo.vertexAttributeDescriptionCount = vertexDescription.vertexDescription->attributeDescriptionCount;
    pipeline.graphicsPipeline->vertexInputInfo.pVertexBindingDescriptions = &vertexDescription.vertexDescription->bindingDescription;
    pipeline.graphicsPipeline->vertexInputInfo.pVertexAttributeDescriptions = vertexDescription.vertexDescription->attributeDescriptions;
}

GN_EXPORT void gnGraphicsPipelineEnableDepthTestFn(gnGraphicsPipeline& pipeline, gnBool depthTest) {
    vulkanCreateGraphicsPipeline(&pipeline);
    if (depthTest == true) {
        pipeline.graphicsPipeline->depthStencil.depthTestEnable = (depthTest == true) ? VK_TRUE : VK_FALSE;
    } else {
        pipeline.graphicsPipeline->depthStencil.depthTestEnable = VK_FALSE;
    }
    pipeline.graphicsPipeline->depthStencil.depthWriteEnable = (depthTest == true) ? VK_TRUE : VK_FALSE;
    pipeline.graphicsPipeline->depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
    pipeline.graphicsPipeline->depthStencil.depthBoundsTestEnable = VK_FALSE;
    pipeline.graphicsPipeline->depthStencil.minDepthBounds = 0.0f; // Optional
    pipeline.graphicsPipeline->depthStencil.maxDepthBounds = 1.0f; // Optional
    pipeline.graphicsPipeline->depthStencil.stencilTestEnable = VK_FALSE;
    pipeline.graphicsPipeline->depthStencil.front = {}; // Optional
    pipeline.graphicsPipeline->depthStencil.back = {}; // Optional
}

GN_EXPORT gnReturnCode gnCreateGraphicsPipelineFn(gnGraphicsPipeline* pipeline, gnOutputDevice& outputDevice) {
    vulkanCreateGraphicsPipeline(pipeline);
    pipeline->graphicsPipeline->commandPool = &outputDevice.outputDevice->commandPool;

    std::vector<VkDescriptorSetLayout> descriptorLayouts;
    for (int i = 0; i < pipeline->uniformLayouts.size(); i++) {
        descriptorLayouts.push_back(pipeline->uniformLayouts[i]->uniformLayout->setLayout);
    }

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(pipeline->uniformLayouts.size());
    pipelineLayoutInfo.pSetLayouts = descriptorLayouts.data();

    std::vector<VkPushConstantRange> pushConstantRanges = {};
    for (int i = 0; i < pipeline->pushConstants.size(); i++ ) {
        VkPushConstantRange range;

        range.offset = pipeline->pushConstants[i]->offset;
        range.size = pipeline->pushConstants[i]->size;

        int stageBit = 0;

        if (gnContainsShaderStage(pipeline->pushConstants[i]->stage, GN_VERTEX_SHADER_MODULE)) stageBit |= VK_SHADER_STAGE_VERTEX_BIT;
        if (gnContainsShaderStage(pipeline->pushConstants[i]->stage, GN_FRAGMENT_SHADER_MODULE)) stageBit |= VK_SHADER_STAGE_FRAGMENT_BIT;

        range.stageFlags = stageBit;

        pushConstantRanges.push_back(range);
    }

    pipelineLayoutInfo.pPushConstantRanges = pushConstantRanges.data();
    pipelineLayoutInfo.pushConstantRangeCount = pipeline->pushConstants.size();

    if (vkCreatePipelineLayout(outputDevice.outputDevice->device, &pipelineLayoutInfo, nullptr, &pipeline->graphicsPipeline->pipelineLayout) != VK_SUCCESS) {
        return GN_FAILED;
    }

    for (int i = 0; i < pipeline->pushConstants.size(); i++ ) {
        if (pipeline->pushConstants[i]->pushConstant == nullptr) { pipeline->pushConstants[i]->pushConstant = new gnPlatformPushConstant(); }
        pipeline->pushConstants[i]->pushConstant->pushConstantRange = pushConstantRanges[i];
        pipeline->pushConstants[i]->pushConstant->graphicsPipeline = pipeline;
    }

    pipeline->graphicsPipeline->outputDevice = &outputDevice;

    {
        pipeline->graphicsPipeline->pipelineInfo.pVertexInputState = &pipeline->graphicsPipeline->vertexInputInfo;
        pipeline->graphicsPipeline->pipelineInfo.pInputAssemblyState = &pipeline->graphicsPipeline->inputAssembly;
        pipeline->graphicsPipeline->pipelineInfo.pViewportState = &pipeline->graphicsPipeline->viewportState;
        pipeline->graphicsPipeline->pipelineInfo.pRasterizationState = &pipeline->graphicsPipeline->rasterizer;
        pipeline->graphicsPipeline->pipelineInfo.pMultisampleState = &pipeline->graphicsPipeline->multisampling;
        pipeline->graphicsPipeline->pipelineInfo.pDepthStencilState = nullptr; // Optional
        pipeline->graphicsPipeline->pipelineInfo.pColorBlendState = &pipeline->graphicsPipeline->colorBlending;
        pipeline->graphicsPipeline->pipelineInfo.pDynamicState = &pipeline->graphicsPipeline->dynamicState;
        pipeline->graphicsPipeline->pipelineInfo.pDepthStencilState = &pipeline->graphicsPipeline->depthStencil;

        pipeline->graphicsPipeline->pipelineInfo.layout = pipeline->graphicsPipeline->pipelineLayout;

        // for (int i = 0; i < pipeline->descriptorSet->descriptorSet->descriptorSets.size(); i++) {
        //     (*pipeline->uniformBufferDescriptors)[i].bufferDescription->descriptorSet = pipeline->descriptorSet->descriptorSet->descriptorSets[i];
        // }

        if (vkCreateGraphicsPipelines(outputDevice.outputDevice->device, VK_NULL_HANDLE, 1, &pipeline->graphicsPipeline->pipelineInfo, nullptr, &pipeline->graphicsPipeline->graphicsPipeline) != VK_SUCCESS) {
            return GN_FAILED;
        }

    }

    return GN_SUCCESS;
}
GN_EXPORT void gnGraphicsPipelineAddPushConstantFn(gnGraphicsPipeline& pipeline, const gnPushConstant& pushConstant) {
    vulkanCreateGraphicsPipeline(&pipeline);
    pipeline.pushConstants.push_back(const_cast<gnPushConstant*>(&pushConstant));
}
GN_EXPORT void gnGraphicsPipelineSetUniformBufferDescriptorsFn(gnGraphicsPipeline& pipeline, const std::vector<gnBufferDescription>& bufferDescriptions) {
    vulkanCreateGraphicsPipeline(&pipeline);
    //graphicsPipeline.uniformBufferDescriptors = const_cast<std::vector<gnBufferDescription>*>(&bufferDescriptions);
}
GN_EXPORT void gnGraphicsPipelineAddUniformLayoutFn(gnGraphicsPipeline& pipeline, const gnUniformLayout& uniformLayout) {
    vulkanCreateGraphicsPipeline(&pipeline);
    pipeline.uniformLayouts.push_back(const_cast<gnUniformLayout*>(&uniformLayout));
}
GN_EXPORT void gnDestroyGraphicsPipelineFn(gnGraphicsPipeline& pipeline) {
    vulkanCreateGraphicsPipeline(&pipeline);
    vkDestroyPipeline(pipeline.graphicsPipeline->outputDevice->outputDevice->device, pipeline.graphicsPipeline->graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(pipeline.graphicsPipeline->outputDevice->outputDevice->device, pipeline.graphicsPipeline->pipelineLayout, nullptr);
}
