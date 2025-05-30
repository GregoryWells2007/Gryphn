#pragma once
#include <core/command/command_pool/gryphn_command_pool.h>
#include "core/renderpass/gryphn_render_pass.h"

typedef struct gnCommandBuffer_t {
    struct gnPlatformCommandBuffer_t* commandBuffer;
} gnCommandBuffer;

gnReturnCode gnBeginCommandBuffer(struct gnCommandBuffer_t* commandBuffer);
void gnCommandBufferBeginRenderPass(struct gnRenderPassInfo_t passInfo);
