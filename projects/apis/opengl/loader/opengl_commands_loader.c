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

        ._gnCommandBindGraphicsPipeline = NULL,
        ._gnCommandSetViewport = NULL,
        ._gnCommandSetScissor = NULL,
        ._gnCommandBindUniform = NULL,
        ._gnCommandPushConstant = NULL,

        ._gnCommandBindBuffer = NULL,
        ._gnCommandDraw = NULL,
        ._gnCommandDrawIndexed = NULL,
    };
}
