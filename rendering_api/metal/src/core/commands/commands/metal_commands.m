#include "core/command/commands/gryphn_command.h"
#include "core/framebuffers/metal_framebuffer.h"
#include "core/commands/command_buffer/metal_command_buffer.h"
#include "core/pipelines/graphics_pipeline/metal_graphics_pipeline.h"
#include "core/buffer/metal_buffer.h"
#include "core/uniforms/metal_uniform.h"
#import <Metal/MTLRenderCommandEncoder.h>

void gnCommandBeginRenderPassFn(struct gnCommandBuffer_t* buffer, struct gnRenderPassInfo_t passInfo) {
    int currentColorAttachment = 0;
    for (int i = 0; i < passInfo.clearValueCount; i++) {
        gnBool wasDepthStencil = gnFalse;
        if (isDepthFormat(passInfo.renderPassDescriptor->info.attachmentInfos[i].format)) {
            wasDepthStencil = gnTrue;
        }
        if (isStencilFormat(passInfo.renderPassDescriptor->info.attachmentInfos[i].format)) {
            wasDepthStencil = gnTrue;
        }

        if(!wasDepthStencil) {
            MTLRenderPassColorAttachmentDescriptor* color = passInfo.framebuffer->framebuffer->framebuffer.colorAttachments[i];
            color.clearColor = MTLClearColorMake(
                passInfo.clearValues[i].red,
                passInfo.clearValues[i].green,
                passInfo.clearValues[i].blue,
                passInfo.clearValues[i].alpha
            );
        }
    }
    buffer->commandBuffer->encoder = [buffer->commandBuffer->commandBuffer renderCommandEncoderWithDescriptor:passInfo.framebuffer->framebuffer->framebuffer];
    MTLViewport vp = {(double)passInfo.offset.x, (double)passInfo.offset.y, (double)passInfo.size.x, (double)passInfo.size.y, 0.0f, 1.0f};
    id<MTLRenderCommandEncoder> encoder = (id<MTLRenderCommandEncoder>)buffer->commandBuffer->encoder;
    [encoder setViewport:vp];
}
void gnCommandEndRenderPassFn(struct gnCommandBuffer_t* buffer) {
    [buffer->commandBuffer->encoder endEncoding];
}
void gnCommandBindGraphicsPipelineFn(struct gnCommandBuffer_t* buffer, struct gnGraphicsPipeline_t* graphicsPipeline) {
    id<MTLRenderCommandEncoder> encoder = (id<MTLRenderCommandEncoder>)buffer->commandBuffer->encoder;
    [encoder setRenderPipelineState:graphicsPipeline->graphicsPipeline->graphicsPipeline];

    if (graphicsPipeline->info.cullMode.face == GN_CULL_FACE_BACK)
        [encoder setCullMode:MTLCullModeBack];
    else if (graphicsPipeline->info.cullMode.face == GN_CULL_FACE_FRONT)
        [encoder setCullMode:MTLCullModeFront];
    else if (graphicsPipeline->info.cullMode.face == GN_CULL_FACE_NONE)
        [encoder setCullMode:MTLCullModeNone];

    if (graphicsPipeline->info.cullMode.direction == GN_DIRECTION_CLOCK_WISE)
        [encoder setFrontFacingWinding:MTLWindingCounterClockwise];
    if (graphicsPipeline->info.cullMode.direction == GN_DIRECTION_COUNTER_CLOCK_WISE)
        [encoder setFrontFacingWinding:MTLWindingClockwise];

    if (graphicsPipeline->info.fillMode == GN_FILL_MODE_POINT)
        [encoder setTriangleFillMode:MTLTriangleFillModeFill];
    if (graphicsPipeline->info.fillMode == GN_FILL_MODE_LINE)
        [encoder setTriangleFillMode:MTLTriangleFillModeLines];
    if (graphicsPipeline->info.fillMode == GN_FILL_MODE_FILL)
        [encoder setTriangleFillMode:MTLTriangleFillModeFill];

    buffer->commandBuffer->boundGraphcisPipeline = graphicsPipeline;
}
void gnCommandSetViewportFn(struct gnCommandBuffer_t* buffer, struct gnViewport_t viewport) {
    MTLViewport vp = {(double)viewport.position.x, (double)viewport.position.y, (double)viewport.size.x, (double)viewport.size.y, viewport.minDepth, viewport.maxDepth};
    id<MTLRenderCommandEncoder> encoder = (id<MTLRenderCommandEncoder>)buffer->commandBuffer->encoder;
    [encoder setViewport:vp];
}
void gnCommandSetScissorFn(struct gnCommandBuffer_t* buffer, struct gnScissor_t scissor) {
    MTLScissorRect scissorRect = { scissor.position.x, scissor.position.y, scissor.size.x, scissor.size.y };
    id<MTLRenderCommandEncoder> encoder = (id<MTLRenderCommandEncoder>)buffer->commandBuffer->encoder;
    [encoder setScissorRect:scissorRect];
}
void gnCommandBindBufferFn(gnCommandBufferHandle buffer, gnBufferHandle bufferToBind, gnBufferType type) {
    id<MTLRenderCommandEncoder> encoder = (id<MTLRenderCommandEncoder>)buffer->commandBuffer->encoder;
    if (type == GN_VERTEX_BUFFER)
        [encoder setVertexBuffer:bufferToBind->buffer->buffer offset:0 atIndex:0];
    else if (type == GN_INDEX_BUFFER)
        buffer->commandBuffer->indexBuffer = bufferToBind;
}
void gnCommandDrawFn(struct gnCommandBuffer_t* buffer, int vertexCount, int firstVertex, int instanceCount, int firstInstance) {
    if (buffer->commandBuffer->boundGraphcisPipeline != NULL) {
        id<MTLRenderCommandEncoder> encoder = (id<MTLRenderCommandEncoder>)buffer->commandBuffer->encoder;
        if (buffer->commandBuffer->boundGraphcisPipeline->info.primitiveType == GN_PRIMITIVE_POINTS)
            [encoder drawPrimitives:MTLPrimitiveTypePoint vertexStart:firstVertex vertexCount:vertexCount instanceCount:instanceCount baseInstance:firstInstance];
        else if (buffer->commandBuffer->boundGraphcisPipeline->info.primitiveType == GN_PRIMITIVE_LINES)
            [encoder drawPrimitives:MTLPrimitiveTypeLine vertexStart:firstVertex vertexCount:vertexCount instanceCount:instanceCount baseInstance:firstInstance];
        else if (buffer->commandBuffer->boundGraphcisPipeline->info.primitiveType == GN_PRIMITIVE_LINE_STRIP)
            [encoder drawPrimitives:MTLPrimitiveTypeLineStrip vertexStart:firstVertex vertexCount:vertexCount instanceCount:instanceCount baseInstance:firstInstance];
        else if (buffer->commandBuffer->boundGraphcisPipeline->info.primitiveType == GN_PRIMITIVE_TRIANGLES)
            [encoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:firstVertex vertexCount:vertexCount instanceCount:instanceCount baseInstance:firstInstance];
        else if (buffer->commandBuffer->boundGraphcisPipeline->info.primitiveType == GN_PRIMITIVE_TRIANGLE_STRIP)
            [encoder drawPrimitives:MTLPrimitiveTypeTriangleStrip vertexStart:firstVertex vertexCount:vertexCount instanceCount:instanceCount baseInstance:firstInstance];
    }
}
void gnCommandDrawIndexedFn(gnCommandBufferHandle buffer, gnIndexType type, int indexCount, int firstIndex, int vertexOffset, int instanceCount, int firstInstance)  {
    id<MTLRenderCommandEncoder> encoder = (id<MTLRenderCommandEncoder>)buffer->commandBuffer->encoder;
    MTLPrimitiveType primative;
    switch (buffer->commandBuffer->boundGraphcisPipeline->info.primitiveType) {
    case GN_PRIMITIVE_POINTS: primative = MTLPrimitiveTypePoint; break;
    case GN_PRIMITIVE_LINE_STRIP: primative = MTLPrimitiveTypeLineStrip; break;
    case GN_PRIMITIVE_LINES: primative = MTLPrimitiveTypeLine; break;
    case GN_PRIMITIVE_TRIANGLE_STRIP: primative = MTLPrimitiveTypeTriangleStrip; break;
    case GN_PRIMITIVE_TRIANGLES: primative = MTLPrimitiveTypeTriangle; break;
    }
    [encoder
        drawIndexedPrimitives:primative
        indexCount:indexCount
        indexType:((type == GN_UINT32) ? MTLIndexTypeUInt32 : MTLIndexTypeUInt16)
        indexBuffer:buffer->commandBuffer->indexBuffer->buffer->buffer
        indexBufferOffset:0
        instanceCount:instanceCount
        baseVertex:vertexOffset
        baseInstance:firstInstance
    ];
}

void gnCommandBindUniformFn(gnCommandBufferHandle buffer, gnUniform uniform, uint32_t set) {
    id<MTLRenderCommandEncoder> encoder = (id<MTLRenderCommandEncoder>)buffer->commandBuffer->encoder;
    if (uniform->uniform->type == GN_UNIFORM_BUFFER_DESCRIPTOR) {
        gnBufferUniformInfo info = *(gnBufferUniformInfo*)uniform->uniform->data;

        [encoder setVertexBuffer:info.buffer->buffer->buffer
            offset:info.offset
            atIndex:(info.binding + 1)
        ];
    }
}
