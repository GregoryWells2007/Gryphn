#include "vulkan_loader.h"
#include <commands/command_buffer/vulkan_command_buffer.h>
#include <commands/commands/vulkan_commands.h>

gnCommandFunctions loadVulkanCommandFunctions() {
    return (gnCommandFunctions){
        ._gnCommandPoolAllocateCommandBuffers = allocateCommandBuffers,
        ._gnBeginCommandBuffer = beginCommandBuffer,
        ._gnResetCommandBuffer = resetCommandBuffer,
        ._gnEndCommandBuffer = endCommandBuffer,

        ._gnCommandBeginRenderPass = beginRenderPass,
        ._gnCommandEndRenderPass = endRenderPass,
        ._gnCommandBindGraphicsPipeline = bindGraphicsPipeline,
        ._gnCommandSetViewport = setViewport,
        ._gnCommandSetScissor = setScissor,
        ._gnCommandBindUniform = bindUniform,
        ._gnCommandPushConstant = pushConstant,

        ._gnCommandBindBuffer = bindBuffer,
        ._gnCommandDraw = draw,
        ._gnCommandDrawIndexed = drawIndexed,
    };
}
