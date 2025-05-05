#include "metal_command_buffer.h"
#include <core/devices/metal_output_devices.h>
#include <core/output_device/gryphn_output_device.h>
#include <core/metal_instance.h>

GN_EXPORT gnReturnCode gnCreateCommandBufferFn(gnCommandBuffer* commandBuffer, const gnOutputDevice& outputDevice) {
    commandBuffer->commandBuffer = new gnPlatformCommandBuffer();
    commandBuffer->commandBuffer->outputDevice = &outputDevice;
    commandBuffer->commandBuffer->commandBuffer = outputDevice.outputDevice->commandQueue->commandBuffer();
    return GN_SUCCESS;
}
GN_EXPORT gnReturnCode _gnCreateCommandBuffersFn(gnCommandBuffer* commandBuffers, gnUInt commandBufferCount, const gnOutputDevice& outputDevice) {
    for (int i = 0; i < commandBufferCount; i++) {
        commandBuffers[i].commandBuffer = new gnPlatformCommandBuffer();
        commandBuffers[i].commandBuffer->outputDevice = &outputDevice;
        commandBuffers[i].commandBuffer->commandBuffer = outputDevice.outputDevice->commandQueue->commandBuffer();
    }
    return GN_SUCCESS;
}
// so imma just destroy and recreate the command buffer every frame, fuck you
GN_EXPORT void gnCommandBufferResetFn(const gnCommandBuffer& commandBuffer) {
    commandBuffer.commandBuffer->commandBuffer->release();
    commandBuffer.commandBuffer->commandBuffer = commandBuffer.commandBuffer->outputDevice->outputDevice->commandQueue->commandBuffer();
}
GN_EXPORT void gnDestroyCommandBufferFn(const gnCommandBuffer& commandBuffer) {
    commandBuffer.commandBuffer->commandBuffer->release();
}
