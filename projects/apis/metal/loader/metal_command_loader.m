#include "metal_loader.h"

gnCommandFunctions loadMetalCommandFunctions() {
    return (gnCommandFunctions){
        ._gnCommandPoolAllocateCommandBuffers = NULL,
        ._gnBeginCommandBuffer = NULL,
        ._gnResetCommandBuffer = NULL,
        ._gnEndCommandBuffer = NULL,

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
