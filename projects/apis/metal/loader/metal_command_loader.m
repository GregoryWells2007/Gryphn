#include "metal_loader.h"
#include "commands/command_buffer/metal_command_buffer.h"
#include "commands/commands/metal_commands.h"

gnCommandFunctions loadMetalCommandFunctions(void) {
    return (gnCommandFunctions){
        ._gnCommandPoolAllocateCommandBuffers = allocateMetalCommandBuffers,
        ._gnBeginCommandBuffer = beginMetalCommandBuffer,
        ._gnResetCommandBuffer = resetMetalCommandBuffer,
        ._gnEndCommandBuffer = endMetalCommandBuffer,
        ._gnDestroyCommandBuffer = destroyMetalCommandBuffer,

        ._gnCommandBeginRenderPass = metelBeginRenderPass,
        ._gnCommandEndRenderPass = endMetalRenderPass,
        ._gnCommandBindGraphicsPipeline = bindMetalGraphicsPipeline,
        ._gnCommandSetViewport = setMetalViewport,
        ._gnCommandSetScissor = setMetalScissor,
        ._gnCommandBindUniform = metalBindUniform,
        ._gnCommandPushConstant = metalBindVertexBytes,

        ._gnCommandBindBuffer = bindMetalBuffer,
        ._gnCommandDraw = metalDraw,
        ._gnCommandDrawIndexed = metalDrawIndexed,
    };
}
