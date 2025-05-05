#include <core/commands/gryphn_command.h>
#include <core/commands/metal_command_buffer.h>
#include <core/graphics_pipeline/metal_render_pass_frame.h>
#include <core/graphics_pipeline/metal_graphics_pipeline.h>
#include <core/framebuffers/metal_framebuffer.h>
#include <core/textures/metal_texture.h>
#include <core/buffers/metal_buffer.h>
#include <core/metal_instance.h>
#include <core/shaders/metal_shader_module.h>

GN_EXPORT gnReturnCode gnCommandBufferStartFn(gnCommandBuffer& commandBuffer) {
    // do absoluetly nothing
    return GN_SUCCESS;
}
GN_EXPORT void gnCommandBeginRenderPassFn(gnCommandBuffer& commandBuffer, const gnRenderPassFrame& frame) {
    int currentColorAttachment = 0;
    for (int i = 0; i < gnListLength(frame.framebuffer->framebufferAttachments); i++) {
        if (frame.framebuffer->framebufferAttachments[i].bindPoint == GN_COLOR_ATTACHMENT) {
            frame.framebuffer->framebuffer->framebuffer->colorAttachments()->object(currentColorAttachment)->setClearColor(MTL::ClearColor::Make(frame.clearColor.r / 255.0f, frame.clearColor.g / 255.0f, frame.clearColor.b / 255.0f, frame.clearColor.a));
            currentColorAttachment++;
        }
    }
    commandBuffer.commandBuffer->renderCommandEncoder = commandBuffer.commandBuffer->commandBuffer->renderCommandEncoder(frame.framebuffer->framebuffer->framebuffer);
    MTL::Viewport vp = {(double)frame.offset.x, (double)frame.offset.y, (double)frame.area.x, (double)frame.area.y, 0.0, 1.0};
    commandBuffer.commandBuffer->renderCommandEncoder->setViewport(vp);
}
GN_EXPORT void gnCommandSetGraphicsPipelineFn(gnCommandBuffer& commandBuffer, const gnGraphicsPipeline& graphicsPipeline) {
    commandBuffer.commandBuffer->renderCommandEncoder->setRenderPipelineState(graphicsPipeline.graphicsPipeline->renderPipelineState);
    if (graphicsPipeline.graphicsPipeline->cullMode == GN_CULL_BACKFACE)
        commandBuffer.commandBuffer->renderCommandEncoder->setCullMode(MTL::CullMode::CullModeBack);
    else if (graphicsPipeline.graphicsPipeline->cullMode == GN_CULL_FRONTFACE)
        commandBuffer.commandBuffer->renderCommandEncoder->setCullMode(MTL::CullMode::CullModeFront);
    else if (graphicsPipeline.graphicsPipeline->cullMode == GN_CULL_NONE)
        commandBuffer.commandBuffer->renderCommandEncoder->setCullMode(MTL::CullMode::CullModeNone);

    if (graphicsPipeline.graphicsPipeline->direction == GN_CLOCKWISE)
        commandBuffer.commandBuffer->renderCommandEncoder->setFrontFacingWinding(MTL::WindingCounterClockwise);
    if (graphicsPipeline.graphicsPipeline->direction == GN_COUNTER_CLOCKWISE)
        commandBuffer.commandBuffer->renderCommandEncoder->setFrontFacingWinding(MTL::WindingClockwise);

    commandBuffer.commandBuffer->renderCommandEncoder->setDepthStencilState(graphicsPipeline.graphicsPipeline->depthStencilState);
}
GN_EXPORT void gnCommandSetViewportFn(const gnCommandBuffer& commandBuffer, gnViewportDescriptionData data) {
    MTL::Viewport viewport = {
        data.offset.x, data.offset.y,
        data.size.x, data.size.y,
        data.depth.x, data.depth.y
    };
    commandBuffer.commandBuffer->renderCommandEncoder->setViewport(viewport);
}
GN_EXPORT void gnCommandSetScissorFn(const gnCommandBuffer& commandBuffer, gnScissorDescriptionData data) {
    MTL::ScissorRect rect = {
        data.offset.x, data.offset.y,
        data.extent.x, data.extent.y
    };
    commandBuffer.commandBuffer->renderCommandEncoder->setScissorRect(rect);
}
GN_EXPORT void gnCommandDrawFn(gnCommandBuffer& commandBuffer, int vertexCount, int instanceCount, int firstVertex, int firstInstance) {
    commandBuffer.commandBuffer->renderCommandEncoder->drawPrimitives(MTL::PrimitiveTypeTriangle, firstVertex, vertexCount, instanceCount, firstInstance);
}
GN_EXPORT void gnCommandDrawIndexedFn(gnCommandBuffer& commandBuffer, gnUInt indexCount, gnUInt instanceCount, gnUInt firstIndex, gnInt vertexOffset, gnUInt firstInstance) {
    commandBuffer.commandBuffer->renderCommandEncoder->drawIndexedPrimitives(MTL::PrimitiveTypeTriangle, indexCount, MTL::IndexTypeUInt16, commandBuffer.commandBuffer->boundIndexBuffer, vertexOffset, instanceCount);
}
GN_EXPORT void gnCommandBindBufferFn(gnCommandBuffer& commandBuffer, const gnBuffer& buffer) {
    if (buffer.bufferType == GN_VERTEX_BUFFER)
        commandBuffer.commandBuffer->renderCommandEncoder->setVertexBuffer(buffer.buffer->buffer, 0, 0);
    else if (buffer.bufferType == GN_INDEX_BUFFER)
        commandBuffer.commandBuffer->boundIndexBuffer = buffer.buffer->buffer;
}
GN_EXPORT void gnCommandBindBufferUniformFn(gnCommandBuffer& commandBuffer, gnGraphicsPipeline& graphicsPipeline, gnBufferUniform& uniformBuffer, gnInt set) {
    for (int i = 0; i < graphicsPipeline.graphicsPipeline->shaders.size(); i++) {
        const mtlShaderRepresentation& repr = graphicsPipeline.graphicsPipeline->shaders[i];
        if (repr.module == GN_VERTEX_SHADER_MODULE) {
            commandBuffer.commandBuffer->renderCommandEncoder->setVertexBuffer(uniformBuffer.buffer->buffer->buffer, 0, uniformBuffer.binding + repr.uniformBufferBinding);
        } else if (repr.module == GN_FRAGMENT_SHADER_MODULE) {
            commandBuffer.commandBuffer->renderCommandEncoder->setFragmentBuffer(uniformBuffer.buffer->buffer->buffer, 0, uniformBuffer.binding + repr.pushConstantBinding);
        }
    }
}
GN_EXPORT void gnCommandBindSamplerUniformFn(gnCommandBuffer& commandBuffer, const gnGraphicsPipeline& graphicsPipeline, const gnSamplerUniform& sampler, gnInt set) {
    for (int i = 0; i < graphicsPipeline.graphicsPipeline->shaders.size(); i++) {
        if (graphicsPipeline.graphicsPipeline->shaders[i].module == GN_FRAGMENT_SHADER_MODULE) {
            int binding = graphicsPipeline.graphicsPipeline->shaders[i].textureBindings[{(gnUInt)set, sampler.binding}];
            // std::cout << "Binding: " << binding << "\n";
            commandBuffer.commandBuffer->renderCommandEncoder->setFragmentTexture(sampler.texture->texture->texture, binding);
            commandBuffer.commandBuffer->renderCommandEncoder->setFragmentSamplerState(sampler.texture->texture->sampler, binding);
        }
    }
}
GN_EXPORT void gnCommandPushConstantFn(gnCommandBuffer& commandBuffer, const gnGraphicsPipeline& graphicsPipeline, const gnPushConstant& pushConstant, void* data) {
    for (int i = 0; i < graphicsPipeline.graphicsPipeline->shaders.size(); i++) {
        const mtlShaderRepresentation& repr = graphicsPipeline.graphicsPipeline->shaders[i];
        if (repr.module == GN_VERTEX_SHADER_MODULE) {
            commandBuffer.commandBuffer->renderCommandEncoder->setVertexBytes(data, pushConstant.size, repr.pushConstantBinding);
        } else if (repr.module == GN_FRAGMENT_SHADER_MODULE) {
            commandBuffer.commandBuffer->renderCommandEncoder->setFragmentBytes(data, pushConstant.size, repr.pushConstantBinding);
        }
    }
}
GN_EXPORT void  gnCommandEndRenderPassFn(gnCommandBuffer& commandBuffer) {
    commandBuffer.commandBuffer->renderCommandEncoder->endEncoding();
}
GN_EXPORT gnReturnCode gnCommandBufferEndFn(gnCommandBuffer& commandBuffer) {
    // commandBuffer.commandBuffer->commandBuffer->commit();
    return GN_SUCCESS;
}
