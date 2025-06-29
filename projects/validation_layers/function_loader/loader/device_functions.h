#include "loader/src/gryphn_device_functions.h"

gnReturnCode checkCreatePresentationQueue(gnPresentationQueueHandle presentationQueue, const gnOutputDeviceHandle device, gnPresentationQueueInfo presentationInfo);
gnReturnCode checkPresentationQueueGetImage(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphoreHandle semaphore, uint32_t* imageIndex);
void checkDestroyPresentationQueue(gnPresentationQueueHandle presentationQueue);

gnReturnCode checkCreateShaderModule(gnShaderModuleHandle module, gnOutputDeviceHandle device, gnShaderModuleInfo shaderModuleInfo);
void checkDestroyShaderModule(gnShaderModuleHandle module);

gnReturnCode checkCreateRenderPassDescriptor(gnRenderPassDescriptorHandle renderPass, gnOutputDeviceHandle device, gnRenderPassDescriptorInfo info);
void checkDestroyRenderPassDescriptor(gnRenderPassDescriptorHandle renderPass);

gnReturnCode checkCreateGraphicsPipeline(gnGraphicsPipelineHandle pipeline, gnOutputDeviceHandle device, gnGraphicsPipelineInfo pipelineInfo);
void checkDestroyGraphicsPipeline(gnGraphicsPipelineHandle pipeline);

gnReturnCode checkCreateFramebuffer(gnFramebuffer framebuffer, gnOutputDeviceHandle device, gnFramebufferInfo framebufferInfo);
void checkDestroyFramebuffer(gnFramebuffer framebuffer);

gnReturnCode checkCreateCommandPool(gnCommandPoolHandle commandPool, gnOutputDeviceHandle device, gnCommandPoolInfo info);
void checkDestroyCommandPool(gnCommandPoolHandle commandPool);

gnReturnCode checkCreateSemaphore(gnSemaphoreHandle semaphore, gnOutputDeviceHandle device);
void checkDestroySemaphore(gnSemaphoreHandle semaphore);

gnReturnCode checkCreateBuffer(gnBufferHandle buffer, gnDeviceHandle device, gnBufferInfo info);
void checkBufferData(gnBufferHandle buffer, size_t size, void* data);
void* checkMapBuffer(gnBufferHandle buffer);
void checkDestroyBuffer(gnBufferHandle buffer);

gnReturnCode checkCreateUniformPool(gnUniformPool pool, gnDeviceHandle device);
gnUniform* checkUniformPoolAllocateUniforms(gnUniformPool pool, gnUniformAllocationInfo allocInfo);
void checkDestroyUniformPool(gnUniformPool pool);

void checkUpdateBufferUniform(gnUniform uniform, gnBufferUniformInfo* bufferInfo);
void checkUpdateImageUniform(gnUniform uniform, gnImageUniformInfo* imageInfo);

gnReturnCode checkCreateTexture(gnTexture texture, gnDevice device, const gnTextureInfo info);
void checkTextureData(gnTextureHandle texture, void* pixelData);
void checkDestroyTexture(gnTexture texture);

gnReturnCode checkCreateFence(gnFenceHandle fence, gnOutputDeviceHandle device);
void checkWaitForFence(gnFenceHandle fence, uint64_t timeout);
void checkResetFence(gnFenceHandle fence);
void checkDestroyFence(gnFenceHandle fence);

gnReturnCode checkSubmit(gnOutputDeviceHandle device, gnSubmitInfo submit);
gnReturnCode checkPresent(gnOutputDeviceHandle device, gnPresentInfo info);

void checkWaitForDevice(gnOutputDeviceHandle device);
