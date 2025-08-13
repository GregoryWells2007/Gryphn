#include "opengl_loader.h"
#include "commands/buffers/opengl_command_buffer.h"

gnCommandFunctions loadOpenGLCommandFunctions() {
    return (gnCommandFunctions) {
        ._gnCommandPoolAllocateCommandBuffers = openglCommandPoolAllocateCommandBuffers,

        ._gnBeginCommandBuffer = openglBeginCommandBuffer,
        ._gnResetCommandBuffer = openglResetCommandBuffer,
        ._gnEndCommandBuffer = openglEndCommandBuffer,
        ._gnDestroyCommandBuffer = openglDestroyCommandBuffer,

        ._gnCommandBeginRenderPass = NULL,
        ._gnCommandEndRenderPass = NULL,

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
