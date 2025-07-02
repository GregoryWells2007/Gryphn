#include "device_functions.h"
#include "loader_utils.h"
#include "core/src/debugger/gryphn_debugger.h"
#include "core/src/presentation_queue/gryphn_presentation_queue.h"
#include "core/src/shader_module/gryphn_shader_module.h"
#include "core/src/renderpass/gryphn_render_pass_descriptor.h"
#include "core/src/pipelines/graphics_pipeline/gryphn_graphics_pipeline.h"
#include "core/src/framebuffer/gryphn_framebuffer.h"
#include "core/src/command/command_pool/gryphn_command_pool.h"
#include "core/src/buffers/gryphn_buffer.h"
#include "core/src/uniforms/gryphn_uniform_pool.h"
#include "core/src/textures/gryphn_texture.h"
#include "core/src/sync/fence/gryphn_fence.h"
#include "core/src/submit/gryphn_submit.h"
#include "core/src/present/gryphn_present.h"

gnReturnCode checkCreatePresentationQueue(gnPresentationQueueHandle presentationQueue, const gnOutputDeviceHandle device, gnPresentationQueueInfo presentationInfo){
    loaderLayer* nextLayer = loaderGetNextLayer(presentationQueue->outputDevice->instance);
    if (nextLayer->deviceFunctions._gnCreatePresentationQueue == NULL) {
        gnDebuggerSetErrorMessage(presentationQueue->outputDevice->instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load create presentation queue function")
        });
        resetLayer(presentationQueue->outputDevice->instance);
        return GN_FAILED_TO_LOAD_FUNCTION;
    }
    return nextLayer->deviceFunctions._gnCreatePresentationQueue(presentationQueue, device, presentationInfo);
}
gnReturnCode checkPresentationQueueGetImage(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphoreHandle semaphore, uint32_t* imageIndex) {
    loaderLayer* nextLayer = loaderGetNextLayer(presentationQueue->outputDevice->instance);
    if (nextLayer->deviceFunctions._gnPresentationQueueGetImage == NULL) {
        gnDebuggerSetErrorMessage(presentationQueue->outputDevice->instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load presentation queue get image function")
        });
        resetLayer(presentationQueue->outputDevice->instance);
        return GN_FAILED_TO_LOAD_FUNCTION;
    }
    return nextLayer->deviceFunctions._gnPresentationQueueGetImage(presentationQueue, timeout, semaphore, imageIndex);
}
void checkDestroyPresentationQueue(gnPresentationQueueHandle presentationQueue) {
    loaderLayer* nextLayer = loaderGetNextLayer(presentationQueue->outputDevice->instance);
    if (nextLayer->deviceFunctions._gnDestroyPresentationQueue == NULL) {
        gnDebuggerSetErrorMessage(presentationQueue->outputDevice->instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load destroy presentation queue function")
        });
        resetLayer(presentationQueue->outputDevice->instance);
    }
    nextLayer->deviceFunctions._gnDestroyPresentationQueue(presentationQueue);
}

gnReturnCode checkCreateShaderModule(gnShaderModuleHandle module, gnOutputDeviceHandle device, gnShaderModuleInfo shaderModuleInfo) {
    loaderLayer* nextLayer = loaderGetNextLayer(device->instance);
    if (nextLayer->deviceFunctions._gnCreateShaderModule == NULL) {
        gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load create shader module function")
        });
        resetLayer(device->instance);
        return GN_FAILED_TO_LOAD_FUNCTION;
    }
    return nextLayer->deviceFunctions._gnCreateShaderModule(module, device, shaderModuleInfo);
}
void checkDestroyShaderModule(gnShaderModuleHandle module){
    loaderLayer* nextLayer = loaderGetNextLayer(module->device->instance);
    if (nextLayer->deviceFunctions._gnDestroyShaderModule == NULL) {
        gnDebuggerSetErrorMessage(module->device->instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load destroy shader module function")
        });
        resetLayer(module->device->instance);
    }
    nextLayer->deviceFunctions._gnDestroyShaderModule(module);
}

gnReturnCode checkCreateRenderPassDescriptor(gnRenderPassDescriptorHandle renderPass, gnOutputDeviceHandle device, gnRenderPassDescriptorInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnCreateRenderPassDescriptor, renderPass, device, info);
}
void checkDestroyRenderPassDescriptor(gnRenderPassDescriptorHandle renderPass) {
    CHECK_VOID_FUNCTION(renderPass->device->instance, _gnDestroyRenderPassDescriptor, renderPass);
}

gnReturnCode checkCreateGraphicsPipeline(gnGraphicsPipelineHandle pipeline, gnOutputDeviceHandle device, gnGraphicsPipelineInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnCreateGraphicsPipeline, pipeline, device, info);
}
void checkDestroyGraphicsPipeline(gnGraphicsPipelineHandle pipeline) {
    CHECK_VOID_FUNCTION(pipeline->device->instance, _gnDestroyGraphicsPipeline, pipeline);
}

gnReturnCode checkCreateFramebuffer(gnFramebuffer framebuffer, gnOutputDeviceHandle device, gnFramebufferInfo framebufferInfo) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnCreateFramebuffer, framebuffer, device, framebufferInfo);
}
void checkDestroyFramebuffer(gnFramebuffer framebuffer) {
    CHECK_VOID_FUNCTION(framebuffer->device->instance, _gnDestroyFramebuffer, framebuffer);
}

gnReturnCode checkCreateCommandPool(gnCommandPoolHandle commandPool, gnOutputDeviceHandle device, gnCommandPoolInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnCreateCommandPool, commandPool, device, info);
}
void checkDestroyCommandPool(gnCommandPoolHandle commandPool) {
    CHECK_VOID_FUNCTION(commandPool->device->instance, _gnDestroyCommandPool, commandPool);
}

gnReturnCode checkCreateSemaphore(gnSemaphoreHandle semaphore, gnOutputDeviceHandle device) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnCreateSemaphore, semaphore, device);
}
void checkDestroySemaphore(gnSemaphoreHandle semaphore) {
    CHECK_VOID_FUNCTION(semaphore->device->instance, _gnDestroySemaphore, semaphore);
}

gnReturnCode checkCreateBuffer(gnBufferHandle buffer, gnDeviceHandle device, gnBufferInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnCreateBuffer, buffer, device, info);
}
void checkBufferData(gnBufferHandle buffer, size_t size, void* data) {
    CHECK_VOID_FUNCTION(buffer->device->instance, _gnBufferData, buffer, size, data);
}
void* checkMapBuffer(gnBufferHandle buffer) {
    loaderLayer* nextLayer = loaderGetNextLayer(buffer->device->instance);
    if (nextLayer->deviceFunctions._gnMapBuffer == NULL) {
        gnDebuggerSetErrorMessage(buffer->device->instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load create map buffer function")
        });
        resetLayer(buffer->device->instance);
        return NULL;
    }
    return nextLayer->deviceFunctions._gnMapBuffer(buffer);
}
void checkDestroyBuffer(gnBufferHandle buffer) {
    CHECK_VOID_FUNCTION(buffer->device->instance, _gnDestroyBuffer, buffer);
}

gnReturnCode checkCreateUniformPool(gnUniformPool pool, gnDeviceHandle device) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnCreateUniformPool, pool, device);
}
gnUniform* checkUniformPoolAllocateUniforms(gnUniformPool pool, gnUniformAllocationInfo allocInfo) {
    loaderLayer* nextLayer = loaderGetNextLayer(pool->device->instance);
    if (nextLayer->deviceFunctions._gnUniformPoolAllocateUniforms == NULL) {
        gnDebuggerSetErrorMessage(pool->device->instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load allocate uniform functions")
        });
        resetLayer(pool->device->instance);
        return NULL;
    }
    return nextLayer->deviceFunctions._gnUniformPoolAllocateUniforms(pool, allocInfo);
}
void checkDestroyUniformPool(gnUniformPool pool) {
    CHECK_VOID_FUNCTION(pool->device->instance, _gnDestroyUniformPool, pool);
}

void checkUpdateBufferUniform(gnUniform uniform, gnBufferUniformInfo* bufferInfo) {
    CHECK_VOID_FUNCTION(uniform->pool->device->instance, _gnUpdateBufferUniform, uniform, bufferInfo);
}
void checkUpdateImageUniform(gnUniform uniform, gnImageUniformInfo* imageInfo) {
    CHECK_VOID_FUNCTION(uniform->pool->device->instance, _gnUpdateImageUniform, uniform, imageInfo);
}

gnReturnCode checkCreateTexture(gnTexture texture, gnDevice device, const gnTextureInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnCreateTexture, texture, device, info);
}
void checkTextureData(gnTextureHandle texture, void* pixelData) {
    CHECK_VOID_FUNCTION(texture->device->instance, _gnTextureData, texture, pixelData);
}
void checkDestroyTexture(gnTexture texture) {
    CHECK_VOID_FUNCTION(texture->device->instance, _gnDestroyTexture, texture);
}

gnReturnCode checkCreateFence(gnFenceHandle fence, gnOutputDeviceHandle device) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnCreateFence, fence, device);
}
void checkWaitForFence(gnFenceHandle fence, uint64_t timeout) {
    CHECK_VOID_FUNCTION(fence->device->instance, _gnWaitForFence, fence, timeout);
}
void checkResetFence(gnFenceHandle fence) {
    CHECK_VOID_FUNCTION(fence->device->instance, _gnResetFence, fence);
}
void checkDestroyFence(gnFenceHandle fence) {
    CHECK_VOID_FUNCTION(fence->device->instance, _gnDestroyFence, fence);
}

gnReturnCode checkSubmit(gnOutputDeviceHandle device, gnSubmitInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnSubmit, device, info);
}
gnReturnCode checkPresent(gnOutputDeviceHandle device, gnPresentInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnPresent, device, info);
}

void checkWaitForDevice(gnOutputDeviceHandle device) {
    CHECK_VOID_FUNCTION(device->instance, _gnWaitForDevice, device);
}
