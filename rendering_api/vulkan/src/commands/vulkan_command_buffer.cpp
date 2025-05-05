#include "gryphn/gryphn_utils.h"
#include "core/commands/gryphn_command_buffer.h"
#include "../graphics_pipeline/vulkan_renderpass.h"
#include "../presentation_queue/vulkan_queue_families.h"
#include "../instance/vulkan_instance.h"
#include "vulkan_command_buffer.h"
#include "../graphics_pipeline/vulkan_graphics_pipeline.h"

VkCommandBuffer beginSingleTimeCommands(const gnOutputDevice& outputDevice) {
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = outputDevice.outputDevice->commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(outputDevice.outputDevice->device, &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    return commandBuffer;
}


void endSingleTimeCommands(VkCommandBuffer commandBuffer, const gnOutputDevice& outputDevice) {
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(outputDevice.outputDevice->graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(outputDevice.outputDevice->graphicsQueue);

    vkFreeCommandBuffers(outputDevice.outputDevice->device, outputDevice.outputDevice->commandPool, 1, &commandBuffer);
}

// GN_EXPORT gnReturnCode _gnCreateCommandBuffersFn(gnList<gnCommandBuffer> *commandBuffers, const gnGraphicsPipeline& pipeline) {
//     std::vector<VkCommandBuffer> commandBufferList;
//     for (int i = 0; i < gnListLength(*commandBuffers); i++) {
//         if ((*commandBuffers)[i].commandBuffer == nullptr) (*commandBuffers)[i].commandBuffer = new gnPlatformCommandBuffer();

//         (*commandBuffers)[i].commandBuffer->outputDevice = pipeline.renderPass->renderpass->outputDevice;
//         commandBufferList.push_back((*commandBuffers)[i].commandBuffer->commandBuffer);
//     }

//     VkCommandBufferAllocateInfo allocInfo{};
//     allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
//     allocInfo.commandPool = *pipeline.graphicsPipeline->commandPool;
//     allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
//     allocInfo.commandBufferCount = (uint32_t) gnListLength(*commandBuffers);

//     if (vkAllocateCommandBuffers(pipeline.renderPass->renderpass->outputDevice->outputDevice->device, &allocInfo, commandBufferList.data()) != VK_SUCCESS) {
//         return GN_FAILED;
//     }

//     for (int i = 0; i < gnListLength(*commandBuffers); i++) {
//         (*commandBuffers)[i].commandBuffer->commandBuffer = commandBufferList[i];
//     }

//     return GN_SUCCESS;
// }

// GN_EXPORT gnReturnCode _gnCreateCommandBuffersFn(std::vector<gnCommandBuffer>* commandBuffers, const gnGraphicsPipeline &pipeline) {
//     std::vector<VkCommandBuffer> commandBufferList;
//     for (int i = 0; i < commandBuffers->size(); i++) {
//         (*commandBuffers)[i].commandBuffer->outputDevice = pipeline.renderPass->renderpass->outputDevice;
//         commandBufferList.push_back((*commandBuffers)[i].commandBuffer->commandBuffer);
//     }

//     VkCommandBufferAllocateInfo allocInfo{};
//     allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
//     allocInfo.commandPool = *pipeline.graphicsPipeline->commandPool;
//     allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
//     allocInfo.commandBufferCount = (uint32_t) commandBuffers->size();

//     if (vkAllocateCommandBuffers(pipeline.renderPass->renderpass->outputDevice->outputDevice->device, &allocInfo, commandBufferList.data()) != VK_SUCCESS) {
//         return GN_FAILED;
//     }

//     for (int i = 0; i < commandBuffers->size(); i++) {
//         (*commandBuffers)[i].commandBuffer->commandBuffer = commandBufferList[i];
//     }

//     return GN_SUCCESS;
// }

GN_EXPORT gnReturnCode _gnCreateCommandBuffersFn(gnCommandBuffer* commandBuffers, gnUInt commandBufferCount, const gnOutputDevice& outputDevice) {
    std::vector<VkCommandBuffer> commandBufferList;
    for (int i = 0; i < commandBufferCount; i++) {
        commandBuffers[i].commandBuffer = new gnPlatformCommandBuffer();
        commandBuffers[i].commandBuffer->outputDevice = const_cast<gnOutputDevice*>(&outputDevice);
        commandBufferList.push_back(commandBuffers[i].commandBuffer->commandBuffer);
    }

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = outputDevice.outputDevice->commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t) commandBufferCount;

    if (vkAllocateCommandBuffers(outputDevice.outputDevice->device, &allocInfo, commandBufferList.data()) != VK_SUCCESS) {
        return GN_FAILED;
    }

    for (int i = 0; i < commandBufferCount; i++) {
        commandBuffers[i].commandBuffer->commandBuffer = commandBufferList[i];
    }

    return GN_SUCCESS;
}


GN_EXPORT gnReturnCode gnCreateCommandBufferFn(gnCommandBuffer* commandBuffer, const gnOutputDevice& device) {
    commandBuffer->commandBuffer->outputDevice = const_cast<gnOutputDevice*>(&device);

    { // create the command buffer
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = device.outputDevice->commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = 1;

        if (vkAllocateCommandBuffers(device.outputDevice->device, &allocInfo, &commandBuffer->commandBuffer->commandBuffer) != VK_SUCCESS) {
            return GN_FAILED;
        }
    }

    return GN_SUCCESS;
}

GN_EXPORT void gnCommandBufferResetFn(const gnCommandBuffer& commandBuffer) {
    vkResetCommandBuffer(commandBuffer.commandBuffer->commandBuffer, 0);
}

GN_EXPORT void gnDestroyCommandBufferFn(const gnCommandBuffer& commandBuffer) {
    // do nothing this function is archaic
}
