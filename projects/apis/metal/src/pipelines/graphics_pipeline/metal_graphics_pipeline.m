#include "metal_graphics_pipeline.h"
#include "devices/metal_output_devices.h"
#include "debugger/gryphn_debugger.h"
#include "shader_module/metal_shader_module.h"
#include "surface/metal_surface.h"
#include "texture/metal_texture.h"

#include "utils/math/gryphn_vec3.h"

MTLBlendFactor mtlGryphnBlendFactor(gnBlendFactor factor) {
    switch (factor) {
    case GN_BLEND_FACTOR_ZERO: return MTLBlendFactorZero;
    case GN_BLEND_FACTOR_ONE: return MTLBlendFactorOne;
    case GN_BLEND_FACTOR_SRC_ALPHA: return MTLBlendFactorSourceAlpha;
    case GN_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA: return MTLBlendFactorOneMinusSourceAlpha;
    }
}

MTLBlendOperation mtlGryphnBlendOperation(gnBlendOperation operation) {
    switch(operation) {
    case GN_OPERATION_ADD: return MTLBlendOperationAdd;
    }
}

MTLVertexFormat mtlGryphnVertexFormat(gnVertexFormat format) {
    switch (format) {
    case GN_FLOAT2: return MTLVertexFormatFloat2;
    case GN_FLOAT3: return MTLVertexFormatFloat3;
    }
}

MTLCompareFunction mtlGrypnCompareOperation(gnCompareOperation operation) {
    switch(operation) {
    case GN_COMPARE_NEVER: return MTLCompareFunctionNever;
    case GN_COMPARE_LESS: return MTLCompareFunctionLess;
    case GN_COMPARE_EQUAL: return MTLCompareFunctionEqual;
    case GN_COMPARE_LESS_OR_EQUAL: return MTLCompareFunctionLessEqual;
    case GN_COMPARE_GREATER: return MTLCompareFunctionGreater;
    case GN_COMPARE_NOT_EQUAL: return MTLCompareFunctionNotEqual;
    case GN_COMPARE_GREATER_OR_EQUAL: return MTLCompareFunctionGreaterEqual;
    case GN_COMPARE_ALWAYS: return MTLCompareFunctionAlways;
    }
}

gnReturnCode createMetalGraphicsPipeline(gnGraphicsPipeline graphicsPipeline, gnOutputDevice device, gnGraphicsPipelineInfo info) {
    graphicsPipeline->graphicsPipeline = malloc(sizeof(struct gnPlatformGraphicsPipeline_t));
    MTLRenderPipelineDescriptor* descriptor = [[MTLRenderPipelineDescriptor alloc] init];
    descriptor.rasterSampleCount = mtlSampleCount(info.multisample.samples);

    if (info.subpassIndex >= info.renderPassDescriptor->info.subpassCount) {
        gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
            .message = gnCreateString("Subpass index is larger then the subpass count in render pass descriptor")
        });
        return GN_UNKNOWN_SUBPASS;
    }

    struct gnSubpassInfo_t subpass = info.renderPassDescriptor->info.subpassInfos[info.subpassIndex];

    for (uint32_t i = 0; i < subpass.colorAttachmentCount; i++) {
        gnSubpassAttachmentInfo subpassAtt = subpass.colorAttachments[i];

        gnRenderPassAttachmentInfo attInfo = info.renderPassDescriptor->info.attachmentInfos[subpassAtt.index];
        descriptor.colorAttachments[i].pixelFormat = mtlGryphnFormatToMetalFormat(attInfo.format);
        if (info.colorBlending.enable == gnTrue) {
            [descriptor.colorAttachments objectAtIndexedSubscript:i].blendingEnabled = YES;
            [descriptor.colorAttachments objectAtIndexedSubscript:i].rgbBlendOperation = mtlGryphnBlendOperation(info.colorBlending.colorBlendOperation);
            [descriptor.colorAttachments objectAtIndexedSubscript:i].alphaBlendOperation = mtlGryphnBlendOperation(info.colorBlending.alphaBlendOperation);
            [descriptor.colorAttachments objectAtIndexedSubscript:i].sourceRGBBlendFactor = mtlGryphnBlendFactor(info.colorBlending.sourceColorBlendFactor);
            [descriptor.colorAttachments objectAtIndexedSubscript:i].sourceAlphaBlendFactor = mtlGryphnBlendFactor(info.colorBlending.sourceAlphaBlendFactor);
            [descriptor.colorAttachments objectAtIndexedSubscript:i].destinationRGBBlendFactor = mtlGryphnBlendFactor(info.colorBlending.destinationColorBlendFactor);
            [descriptor.colorAttachments objectAtIndexedSubscript:i].destinationAlphaBlendFactor = mtlGryphnBlendFactor(info.colorBlending.destinationAlphaBlendFactor);
        } else {
            [descriptor.colorAttachments objectAtIndexedSubscript:i].blendingEnabled = FALSE;
        }
    }

    for (int i = 0; i < info.shaderModuleCount; i++) {
        if (info.shaderModules[i]->info.stage == GN_VERTEX_SHADER_MODULE) {
            [descriptor setVertexFunction:info.shaderModules[i]->shaderModule->function];
            graphicsPipeline->graphicsPipeline->vertexShaderMaps = info.shaderModules[i]->shaderModule->map;
        } else if (info.shaderModules[i]->info.stage == GN_FRAGMENT_SHADER_MODULE) {
            [descriptor setFragmentFunction:info.shaderModules[i]->shaderModule->function];
            graphicsPipeline->graphicsPipeline->fragmentShaderMaps = info.shaderModules[i]->shaderModule->map;
        } else {
            return GN_UNSUPPORTED_SHADER_MODULE;
        }
    }

    MTLVertexDescriptor* vertexDescriptor = [[MTLVertexDescriptor alloc] init];
    MTLVertexAttributeDescriptorArray* attributes = vertexDescriptor.attributes;
    MTLVertexBufferLayoutDescriptorArray* buffers = vertexDescriptor.layouts;

    int k = 0;
    for (int i = 0; i < info.shaderInputLayout.bufferCount; i++) {
        [[buffers objectAtIndexedSubscript:info.shaderInputLayout.bufferAttributes[i].binding] setStride:info.shaderInputLayout.bufferAttributes[i].size];
        for (int j = 0; j < info.shaderInputLayout.bufferAttributes[i].attributeCount; j++) {
            attributes[k].bufferIndex = i;
            attributes[k].offset = info.shaderInputLayout.bufferAttributes[i].attributes[j].offset;
            attributes[k].format = mtlGryphnVertexFormat(info.shaderInputLayout.bufferAttributes[i].attributes[j].format);
            k++;
        }
    }

    MTLDepthStencilDescriptor* depthStencilDesc = [[MTLDepthStencilDescriptor alloc] init];
    depthStencilDesc.depthWriteEnabled = info.depthStencil.depthWriteEnable;
    depthStencilDesc.depthCompareFunction = mtlGrypnCompareOperation(info.depthStencil.operation);
    graphicsPipeline->graphicsPipeline->depthState = [device->outputDevice->device newDepthStencilStateWithDescriptor:depthStencilDesc];

    [descriptor setVertexDescriptor:vertexDescriptor];
    NSError* error = nil;
    graphicsPipeline->graphicsPipeline->graphicsPipeline = [device->outputDevice->device newRenderPipelineStateWithDescriptor:descriptor error:&error];
    if (graphicsPipeline->graphicsPipeline->graphicsPipeline == nil) {
        gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
            .message = gnCombineStrings(gnCreateString("Failed to create metal render pipeline descriptor "), error.localizedDescription.UTF8String)
        });
        return GN_FAILED_TO_CREATE_GRAPHICS_PIPELINE;
    }
    [descriptor release];
    [vertexDescriptor release];
    [error release];
    return GN_SUCCESS;
}

void destroyMetalGraphicsPipeline(gnGraphicsPipeline graphicsPipeline) {
    [graphicsPipeline->graphicsPipeline->graphicsPipeline release];
    free(graphicsPipeline->graphicsPipeline);
}
