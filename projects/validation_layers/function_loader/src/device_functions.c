#include "device_functions.h"
#include "loader_utils.h"
#include <core/src/instance/gryphn_debugger.h>
#include "core/src/presentation_queue/gryphn_presentation_queue.h"
#include "core/src/shader_module/gryphn_shader_module.h"
#include "core/src/renderpass/gryphn_render_pass_descriptor.h"
#include "core/src/pipelines/graphics_pipeline/gryphn_graphics_pipeline.h"
#include "core/src/framebuffer/gryphn_framebuffer.h"
#include "core/src/command/command_pool/gryphn_command_pool.h"
#include "core/src/buffers/gryphn_buffer.h"
#include "core/src/uniforms/gryphn_uniform_pool.h"
#include "core/src/textures/gryphn_texture.h"
#include "core/src/submit/gryphn_submit.h"
#include "core/src/present/gryphn_present.h"

gnReturnCode checkCreatePresentationQueue(gnPresentationQueueHandle presentationQueue, const gnOutputDeviceHandle device, gnPresentationQueueInfo presentationInfo){
    CHECK_FUNCTION_WITH_RETURN_CODE(presentationQueue->outputDevice->instance, _gnCreatePresentationQueue, deviceFunctions, presentationQueue, device, presentationInfo);
}
gnReturnCode checkPresentationQueueGetImage(gnPresentationQueueHandle presentationQueue, uint32_t *imageIndex) {
    CHECK_FUNCTION_WITH_RETURN_CODE(presentationQueue->outputDevice->instance, _gnPresentationQueueGetImage, deviceFunctions, presentationQueue, imageIndex);
}
void checkDestroyPresentationQueue(gnPresentationQueueHandle presentationQueue) {
    CHECK_VOID_FUNCTION(presentationQueue->outputDevice->instance, _gnDestroyPresentationQueue, deviceFunctions, presentationQueue);
}

gnReturnCode checkCreateShaderModule(gnShaderModuleHandle module, gnOutputDeviceHandle device, gnShaderModuleInfo shaderModuleInfo) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnCreateShaderModule, deviceFunctions, module, device, shaderModuleInfo);
}
void checkDestroyShaderModule(gnShaderModuleHandle module) {
    CHECK_VOID_FUNCTION(module->device->instance, _gnDestroyShaderModule, deviceFunctions, module);
}

gnReturnCode checkCreateRenderPassDescriptor(gnRenderPassDescriptorHandle renderPass, gnOutputDeviceHandle device, gnRenderPassDescriptorInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnCreateRenderPassDescriptor, deviceFunctions, renderPass, device, info);
}
void checkDestroyRenderPassDescriptor(gnRenderPassDescriptorHandle renderPass) {
    CHECK_VOID_FUNCTION(renderPass->device->instance, _gnDestroyRenderPassDescriptor, deviceFunctions, renderPass);
}

gnReturnCode checkCreateGraphicsPipeline(gnGraphicsPipelineHandle pipeline, gnOutputDeviceHandle device, gnGraphicsPipelineInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnCreateGraphicsPipeline, deviceFunctions, pipeline, device, info);
}
void checkDestroyGraphicsPipeline(gnGraphicsPipelineHandle pipeline) {
    CHECK_VOID_FUNCTION(pipeline->device->instance, _gnDestroyGraphicsPipeline, deviceFunctions, pipeline);
}

gnReturnCode checkCreateFramebuffer(gnFramebuffer framebuffer, gnOutputDeviceHandle device, gnFramebufferInfo framebufferInfo) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnCreateFramebuffer, deviceFunctions, framebuffer, device, framebufferInfo);
}
void checkDestroyFramebuffer(gnFramebuffer framebuffer) {
    CHECK_VOID_FUNCTION(framebuffer->device->instance, _gnDestroyFramebuffer, deviceFunctions, framebuffer);
}

gnReturnCode checkCreateCommandPool(gnCommandPoolHandle commandPool, gnOutputDeviceHandle device, gnCommandPoolInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnCreateCommandPool, deviceFunctions, commandPool, device, info);
}
void checkDestroyCommandPool(gnCommandPoolHandle commandPool) {
    CHECK_VOID_FUNCTION(commandPool->device->instance, _gnDestroyCommandPool, deviceFunctions, commandPool);
}

gnReturnCode checkCreateBuffer(gnBufferHandle buffer, gnDeviceHandle device, gnBufferInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnCreateBuffer, deviceFunctions, buffer, device, info);
}
void checkBufferData(gnBufferHandle buffer, size_t size, void* data) {
    CHECK_VOID_FUNCTION(buffer->device->instance, _gnBufferData, deviceFunctions, buffer, size, data);
}
void checkBufferSubData(gnBufferHandle buffer, size_t offset, size_t size, void* data) {
    CHECK_VOID_FUNCTION(buffer->device->instance, _gnBufferSubData, deviceFunctions, buffer, offset, size, data);
}
void* checkMapBuffer(gnBufferHandle buffer) {
    CHECK_RETURNED_FUNCTION(buffer->device->instance, _gnMapBuffer, deviceFunctions, NULL, buffer);
}
void checkDestroyBuffer(gnBufferHandle buffer) {
    CHECK_VOID_FUNCTION(buffer->device->instance, _gnDestroyBuffer, deviceFunctions, buffer);
}

gnReturnCode checkCreateUniformPool(gnUniformPool pool, gnDeviceHandle device) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnCreateUniformPool, deviceFunctions, pool, device);
}
gnUniform* checkUniformPoolAllocateUniforms(gnUniformPool pool, gnUniformAllocationInfo allocInfo) {
    CHECK_RETURNED_FUNCTION(pool->device->instance, _gnUniformPoolAllocateUniforms, deviceFunctions, NULL, pool, allocInfo);
}
void checkDestroyUniformPool(gnUniformPool pool) {
    CHECK_VOID_FUNCTION(pool->device->instance, _gnDestroyUniformPool, deviceFunctions, pool);
}

void checkUpdateBufferUniform(gnUniform uniform, gnBufferUniformInfo* bufferInfo) {
    CHECK_VOID_FUNCTION(uniform->pool->device->instance, _gnUpdateBufferUniform, deviceFunctions, uniform, bufferInfo);
}
void checkUpdateStorageUniform(gnUniform uniform, gnStorageUniformInfo* storageInfo) {
    CHECK_VOID_FUNCTION(uniform->pool->device->instance, _gnUpdateStorageUniform, deviceFunctions, uniform, storageInfo);
}
void checkUpdateImageUniform(gnUniform uniform, gnImageUniformInfo* imageInfo) {
    CHECK_VOID_FUNCTION(uniform->pool->device->instance, _gnUpdateImageUniform, deviceFunctions, uniform, imageInfo);
}

gnReturnCode checkCreateTexture(gnTexture texture, gnDevice device, const gnTextureInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnCreateTexture, deviceFunctions, texture, device, info);
}
void checkTextureData(gnTextureHandle texture, void* pixelData) {
    CHECK_VOID_FUNCTION(texture->device->instance, _gnTextureData, deviceFunctions, texture, pixelData);
}
void checkDestroyTexture(gnTexture texture) {
    CHECK_VOID_FUNCTION(texture->device->instance, _gnDestroyTexture, deviceFunctions, texture);
}

gnReturnCode checkSubmit(gnOutputDeviceHandle device, gnSubmitInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnSubmit, deviceFunctions, device, info);
}
gnReturnCode checkPresent(gnOutputDeviceHandle device, gnPresentInfo info) {
    CHECK_FUNCTION_WITH_RETURN_CODE(device->instance, _gnPresent, deviceFunctions, device, info);
}

void checkWaitForDevice(gnOutputDeviceHandle device) {
    CHECK_VOID_FUNCTION(device->instance, _gnWaitForDevice, deviceFunctions, device);
}
