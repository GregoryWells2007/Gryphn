#include "metal_graphics_pipeline.h"
#include "devices/metal_output_devices.h"
#include "shader_module/metal_shader_module.h"
#include "surface/metal_surface.h"
#include "texture/metal_texture.h"
#include "renderpass/metal_render_pass.h"

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

        if (subpass.depthAttachment != NULL) {
            descriptor.depthAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
            descriptor.depthAttachmentPixelFormat = info.renderPassDescriptor->renderPassDescriptor->subpasses[info.subpassIndex].depthAttachment.texture.pixelFormat;
            descriptor.stencilAttachmentPixelFormat = info.renderPassDescriptor->renderPassDescriptor->subpasses[info.subpassIndex].stencilAttachment.texture.pixelFormat;
        }
    }

    for (int i = 0; i < info.shaderModuleCount; i++) {
        const char* shaderCode = mtlCompilerShader(info.shaderModules[i]->shaderModule->compiler, &info.uniformLayout);
        // printf("shader code: %s\n", shaderCode);

        NSError* error = nil;
        MTLCompileOptions* mtloptions = nil;
        NSString* sourceCode = [NSString stringWithCString:shaderCode encoding:NSUTF8StringEncoding];
        id<MTLLibrary> shaderLib = [device->outputDevice->device    newLibraryWithSource:sourceCode options:mtloptions error:&error];
        if (!shaderLib) {
            const char* errorString = error.localizedDescription.UTF8String;
            gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
                .message = gnCombineStrings(gnCreateString("Failed to compile metal library "), errorString)
            });
            [shaderLib release];
            free((void*)shaderCode);
            return GN_FAILED_TO_CREATE_SHADER_MODULE;
        }


        const char* name = gnToCString(info.shaderModules[i]->info.entryPoint);
        if (strcmp(name, "main") == 0)  name = "main0";

        gnBool foundFunction = false;
        for (int i = 0; i < shaderLib.functionNames.count; i++) {
            if (strcmp([shaderLib.functionNames objectAtIndex:0].UTF8String, name) == 0) {
                foundFunction = true;
                break;
            }
        }
        if (!foundFunction) return GN_FAILED_TO_FIND_ENTRY_POINT;

        NSString* functionName = [NSString stringWithCString:name encoding:NSUTF8StringEncoding];
        id<MTLFunction> function = [shaderLib newFunctionWithName:functionName];
        if (info.shaderModules[i]->info.stage == GN_VERTEX_SHADER_MODULE) [descriptor setVertexFunction:function];
        if (info.shaderModules[i]->info.stage == GN_FRAGMENT_SHADER_MODULE) [descriptor setFragmentFunction:function];
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
    [descriptor release];
    [vertexDescriptor release];
    [error release];
    if (graphicsPipeline->graphicsPipeline->graphicsPipeline == nil) return GN_FAILED_TO_CREATE_GRAPHICS_PIPELINE;
    return GN_SUCCESS;
}

void destroyMetalGraphicsPipeline(gnGraphicsPipeline graphicsPipeline) {
    [graphicsPipeline->graphicsPipeline->graphicsPipeline release];
    free(graphicsPipeline->graphicsPipeline);
}
