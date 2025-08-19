#include "opengl_loader.h"
#include "commands/buffers/opengl_command_buffer.h"
#include "commands/commands/opengl_commands.h"

gnCommandFunctions loadOpenGLCommandFunctions() {
    return (gnCommandFunctions) {
        ._gnCommandPoolAllocateCommandBuffers = openglCommandPoolAllocateCommandBuffers,

        ._gnBeginCommandBuffer = openglBeginCommandBuffer,
        ._gnResetCommandBuffer = openglResetCommandBuffer,
        ._gnEndCommandBuffer = openglEndCommandBuffer,
        ._gnDestroyCommandBuffer = openglDestroyCommandBuffer,

        ._gnCommandBeginRenderPass = openglBeginRenderPass,
        ._gnCommandEndRenderPass = openglEndRenderPass,

        ._gnCommandBindGraphicsPipeline = openglBindGraphicsPipeline,
        ._gnCommandSetViewport = openglSetViewport,
        ._gnCommandSetScissor = openglSetScissor,
        ._gnCommandBindUniform = openglBindUniform,
        ._gnCommandPushConstant = openglPushConstant,

        ._gnCommandBindBuffer = openglBindBuffer,
        ._gnCommandDraw = openglDraw,
        ._gnCommandDrawIndexed = openglDrawIndexed,
    };
}
