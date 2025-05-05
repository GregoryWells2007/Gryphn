#include <core/graphics_pipeline/gryphn_graphics_pipeline.h>
#include "metal_graphics_pipeline.h"
#include <core/devices/metal_output_devices.h>
#include <Metal/Metal.hpp>
#include <core/buffers/vertex_description/metal_vertex_description.h>
#include "core/shaders/metal_shader_module.h"

void mtlInitGraphicsPipeline(gnGraphicsPipeline& pipeline) {
    if (pipeline.graphicsPipeline == nullptr) { pipeline.graphicsPipeline = new gnPlatformGraphicsPipeline();
        pipeline.graphicsPipeline->renderPipelineDescriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    }
}

GN_EXPORT void gnGraphicsPipelineSetPrimativeFn(gnGraphicsPipeline& pipeline, gnPrimative primative) {
    mtlInitGraphicsPipeline(pipeline);
    pipeline.primative = primative;
    // this is done at draw time in metal, all this shit it
}
GN_EXPORT void gnGraphicsPipelineEnableDynamicStatesFn(gnGraphicsPipeline& pipeline, const gnBool enable) {
    mtlInitGraphicsPipeline(pipeline);
    pipeline.graphicsPipeline->dynamicStatesEnabled = enable;
}
GN_EXPORT void gnGraphicsPipelineEnableDynamicStateFn(gnGraphicsPipeline& pipeline, const gnDynamicState state) {
    mtlInitGraphicsPipeline(pipeline);
    pipeline.graphicsPipeline->dynamicStates.push_back(state);
}
GN_EXPORT void _gnGraphicsPipelineSetViewportFn(gnGraphicsPipeline& pipeline, gnUInt2 position, gnUInt2 size, gnFloat minDepth, gnFloat maxDepth) {
    mtlInitGraphicsPipeline(pipeline);
    pipeline.graphicsPipeline->position = position;
    pipeline.graphicsPipeline->size = size;
    pipeline.graphicsPipeline->minDepth = minDepth;
    pipeline.graphicsPipeline->maxDepth = maxDepth; // these functions are usless because metal already makes all this shit dynamic
} // minDepth = 0.0f, maxDepth = 1.0f
GN_EXPORT void gnGraphicsPipelineSetCropFn(gnGraphicsPipeline& graphicsPipeline, gnInt2 position, gnUInt2 size) {
    mtlInitGraphicsPipeline(graphicsPipeline);
    graphicsPipeline.graphicsPipeline->stencil_position = position;
    graphicsPipeline.graphicsPipeline->stencil_size = size;
}
GN_EXPORT void gnGraphicsPipelineSetDepthClampFn(gnGraphicsPipeline& graphicsPipeline, gnBool enableDepthClamp) {
    mtlInitGraphicsPipeline(graphicsPipeline);
    graphicsPipeline.graphicsPipeline->enableDepthClamp = true;
}
GN_EXPORT void gnGraphicsPipelineSetFillModeFn(gnGraphicsPipeline& graphicsPipeline, gnFillMode fillMode) {
    mtlInitGraphicsPipeline(graphicsPipeline);
    graphicsPipeline.graphicsPipeline->fillMode = fillMode;
    // if fill mode is points than fuck you, I have to write a renderer that is going to just draw the points
}
GN_EXPORT void gnGraphicsPipelineSetLineWidthFn(gnGraphicsPipeline& graphicsPipeline, gnFloat lineWidth) {
    mtlInitGraphicsPipeline(graphicsPipeline);
    graphicsPipeline.graphicsPipeline->lineWidth = lineWidth;
}
GN_EXPORT void gnGraphicsPipelineSetCullModeFn(gnGraphicsPipeline& graphicsPipeline, gnCullMode cullMode, gnFrontFaceDirection direction) {
    mtlInitGraphicsPipeline(graphicsPipeline);
    graphicsPipeline.graphicsPipeline->cullMode = cullMode;
    graphicsPipeline.graphicsPipeline->direction = direction;
}
GN_EXPORT void gnGraphicsPipelineSetMultisamplingFn(gnGraphicsPipeline& graphicsPipeline, gnBool enableMultisampling) {
    mtlInitGraphicsPipeline(graphicsPipeline);
    if (enableMultisampling) {
        std::cout << "Fuck you im not doing multisampling";
    }
}
GN_EXPORT void gnGraphicsPipelineEnableDepthTestFn(gnGraphicsPipeline& graphicsPipeline, gnBool depthTest) {
    mtlInitGraphicsPipeline(graphicsPipeline);
    graphicsPipeline.graphicsPipeline->depthStateDescriptor = MTL::DepthStencilDescriptor::alloc()->init();
    if (depthTest) {
        graphicsPipeline.graphicsPipeline->depthStateDescriptor->setDepthCompareFunction(MTL::CompareFunctionLess);
        graphicsPipeline.graphicsPipeline->depthStateDescriptor->setDepthWriteEnabled(true);
    } else {
        graphicsPipeline.graphicsPipeline->depthStateDescriptor->setDepthCompareFunction(MTL::CompareFunctionAlways);
        graphicsPipeline.graphicsPipeline->depthStateDescriptor->setDepthWriteEnabled(false);
    }
}
GN_EXPORT void gnGraphicsPipelineSetColorBlendFn(gnGraphicsPipeline& graphicsPipeline, gnBool colorBlend) {
    mtlInitGraphicsPipeline(graphicsPipeline);
    graphicsPipeline.graphicsPipeline->colorBlending = colorBlend;

    if (colorBlend) {
        graphicsPipeline.graphicsPipeline->renderPipelineDescriptor->colorAttachments()->object(0)->setBlendingEnabled(true);
        graphicsPipeline.graphicsPipeline->renderPipelineDescriptor->colorAttachments()->object(0)->setRgbBlendOperation(MTL::BlendOperation::BlendOperationAdd);
        graphicsPipeline.graphicsPipeline->renderPipelineDescriptor->colorAttachments()->object(0)->setAlphaBlendOperation(MTL::BlendOperation::BlendOperationAdd);
        graphicsPipeline.graphicsPipeline->renderPipelineDescriptor->colorAttachments()->object(0)->setSourceRGBBlendFactor(MTL::BlendFactor::BlendFactorSourceAlpha);
        graphicsPipeline.graphicsPipeline->renderPipelineDescriptor->colorAttachments()->object(0)->setSourceAlphaBlendFactor(MTL::BlendFactor::BlendFactorSourceAlpha);
        graphicsPipeline.graphicsPipeline->renderPipelineDescriptor->colorAttachments()->object(0)->setDestinationRGBBlendFactor(MTL::BlendFactor::BlendFactorOneMinusSourceAlpha);
        graphicsPipeline.graphicsPipeline->renderPipelineDescriptor->colorAttachments()->object(0)->setDestinationAlphaBlendFactor(MTL::BlendFactor::BlendFactorOneMinusSourceAlpha);
    }

}
GN_EXPORT void gnGraphicsPipelineSetVertexDescriptionFn(gnGraphicsPipeline& graphicsPipeline, const gnVertexDescription& vertexDescription) {
    mtlInitGraphicsPipeline(graphicsPipeline);
    // this is one of the only things that is not done at runtime in metal, i dont fucking know why
    graphicsPipeline.graphicsPipeline->renderPipelineDescriptor->setVertexDescriptor(vertexDescription.vertexDescription->vertexDescriptor);
}
GN_EXPORT void gnGraphicsPipelineBindShaderFn(gnGraphicsPipeline& graphicsPipeline, const gnShader& shader) {
    mtlInitGraphicsPipeline(graphicsPipeline);
    for (int i = 0; i < gnListLength(shader.shaderModules); i++) {
        if (shader.shaderModules[i].shaderType == GN_VERTEX_SHADER_MODULE)
            graphicsPipeline.graphicsPipeline->renderPipelineDescriptor->setVertexFunction(shader.shaderModules[i].shaderModule->shaderFunction);
        else if (shader.shaderModules[i].shaderType == GN_FRAGMENT_SHADER_MODULE)
            graphicsPipeline.graphicsPipeline->renderPipelineDescriptor->setFragmentFunction(shader.shaderModules[i].shaderModule->shaderFunction);

        graphicsPipeline.graphicsPipeline->shaders.push_back({
            shader.shaderModules[i].shaderType,
            shader.shaderModules[i].shaderModule->uniformBufferOffset,
            shader.shaderModules[i].shaderModule->pushConstantOffset,
            shader.shaderModules[i].shaderModule->texturesSetBindings
        });
    }
}
GN_EXPORT void gnGraphicsPipelineSetRenderPassFn(gnGraphicsPipeline& graphicsPipeline, gnRenderPass& renderpass) {

}
GN_EXPORT void gnGraphicsPipelineAddUniformLayoutFn(gnGraphicsPipeline& graphicsPipeline, const gnUniformLayout& uniformLayout) {

}
GN_EXPORT void gnGraphicsPipelineAddPushConstantFn(gnGraphicsPipeline& graphicsPipeline, const gnPushConstant& pushConstant) {

}
GN_EXPORT gnReturnCode gnCreateGraphicsPipelineFn(gnGraphicsPipeline* graphicsPipeline, gnOutputDevice& outputDevice) {
    if (graphicsPipeline->graphicsPipeline == nullptr) GN_RETURN_ERROR("Need to call one gnGraphicsPipeline function to create a graphics pipeline");
    NS::Error* error = nullptr;
    graphicsPipeline->graphicsPipeline->renderPipelineDescriptor->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
    graphicsPipeline->graphicsPipeline->renderPipelineState = outputDevice.outputDevice->device->newRenderPipelineState(graphicsPipeline->graphicsPipeline->renderPipelineDescriptor, &error);
    if (!graphicsPipeline->graphicsPipeline->renderPipelineState)
        GN_RETURN_ERROR(error->localizedDescription()->utf8String());

    graphicsPipeline->graphicsPipeline->depthStencilState = outputDevice.outputDevice->device->newDepthStencilState(graphicsPipeline->graphicsPipeline->depthStateDescriptor);
    graphicsPipeline->graphicsPipeline->outputDevice = &outputDevice;

    return GN_SUCCESS;
}
GN_EXPORT void gnDestroyGraphicsPipelineFn(gnGraphicsPipeline& graphicsPipeline) {

}
