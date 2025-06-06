#include "metal_graphics_pipeline.h"
#include "core/devices/metal_output_devices.h"
#include "core/debugger/gryphn_debugger.h"
#include "core/shader_module/metal_shader_module.h"
#include "core/surface/metal_surface.h"

MTLBlendFactor vkGryphnBlendFactor(enum gnBlendFactor_e factor) {
    switch (factor) {
    case GN_BLEND_FACTOR_ZERO: return MTLBlendFactorZero;
    case GN_BLEND_FACTOR_ONE: return MTLBlendFactorOne;
    case GN_BLEND_FACTOR_SRC_ALPHA: return MTLBlendFactorSourceAlpha;
    case GN_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA: return MTLBlendFactorOneMinusSourceAlpha;
    }
}

MTLBlendOperation vkGryphnBlendOperation(enum gnBlendOperation_e operation) {
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

gnReturnCode gnCreateGraphicsPipelineFn(struct gnGraphicsPipeline_t* graphicsPipeline, struct gnOutputDevice_t* device, struct gnGraphicsPipelineInfo_t info) {
    graphicsPipeline->graphicsPipeline = malloc(sizeof(struct gnPlatformGraphicsPipeline_t));
    MTLRenderPipelineDescriptor* descriptor = [[MTLRenderPipelineDescriptor alloc] init];

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
        descriptor.colorAttachments[i].pixelFormat = mtlGryphnFormatToVulkanFormat(attInfo.format);
        if (info.colorBlending.enable == gnTrue) {
            [descriptor.colorAttachments objectAtIndexedSubscript:i].blendingEnabled = YES;
            [descriptor.colorAttachments objectAtIndexedSubscript:i].rgbBlendOperation = vkGryphnBlendOperation(info.colorBlending.colorBlendOperation);
            [descriptor.colorAttachments objectAtIndexedSubscript:i].alphaBlendOperation = vkGryphnBlendOperation(info.colorBlending.alphaBlendOperation);
            [descriptor.colorAttachments objectAtIndexedSubscript:i].sourceRGBBlendFactor = vkGryphnBlendFactor(info.colorBlending.sourceColorBlendFactor);
            [descriptor.colorAttachments objectAtIndexedSubscript:i].sourceAlphaBlendFactor = vkGryphnBlendFactor(info.colorBlending.sourceAlphaBlendFactor);
            [descriptor.colorAttachments objectAtIndexedSubscript:i].destinationRGBBlendFactor = vkGryphnBlendFactor(info.colorBlending.destinationColorBlendFactor);
            [descriptor.colorAttachments objectAtIndexedSubscript:i].destinationAlphaBlendFactor = vkGryphnBlendFactor(info.colorBlending.destinationAlphaBlendFactor);
        } else {
            [descriptor.colorAttachments objectAtIndexedSubscript:i].blendingEnabled = FALSE;
        }
    }

    for (int i = 0; i < info.shaderModuleCount; i++) {
        if (info.shaderModules[i]->info.stage == GN_VERTEX_SHADER_MODULE) {
            [descriptor setVertexFunction:info.shaderModules[i]->shaderModule->function];
        } else if (info.shaderModules[i]->info.stage == GN_FRAGMENT_SHADER_MODULE) {
            [descriptor setFragmentFunction:info.shaderModules[i]->shaderModule->function];
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

void gnDestroyGraphicsPipelineFn(struct gnGraphicsPipeline_t *graphicsPipeline) {
    [graphicsPipeline->graphicsPipeline->graphicsPipeline release];
    free(graphicsPipeline->graphicsPipeline);
}
