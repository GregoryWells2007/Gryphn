// #include <core/output_device/gryphn_physical_output_device.h>
// #include <Metal/Metal.hpp>
// #include <core/metal_instance.h>
// #include "metal_output_devices.h"

// struct mtlFramebufferVertex {
//     float x, y;
//     float u, v;
// };

// GN_EXPORT gnReturnCode gnRegisterOutputDeviceFn(gnOutputDevice* outputDevice, const gnInstance& instance, const gnPhysicalOutputDevice& physicalDevice) {
//     if (outputDevice->outputDevice == nullptr) outputDevice->outputDevice = new gnPlatformOutputDevice();
//     outputDevice->physicalOutputDevice = const_cast<gnPhysicalOutputDevice*>(&physicalDevice);

//     // instance.instance->metalLayer->setDevice(physicalDevice.physicalOutputDevice->device);

//     // outputDevice->outputDevice->contentView = instance.instance->metalContentView->retain();
//     outputDevice->outputDevice->device = physicalDevice.physicalOutputDevice->device->retain();
//     outputDevice->outputDevice->commandQueue = outputDevice->outputDevice->device->newCommandQueue();
//     outputDevice->outputDevice->instance = const_cast<gnInstance*>(&instance);

//     {

//         NS::Error* error = nullptr;
//         MTL::CompileOptions* options = nullptr;
//         MTL::Library* library = physicalDevice.physicalOutputDevice->device->newLibrary(NS::String::string(shaderSrc, NS::UTF8StringEncoding), options, &error);
//         if (!library) {
//             return gnReturnError(GN_FAILED_CREATE_DEVICE, error->localizedDescription()->utf8String());
//         }
//         MTL::Function* vs = library->newFunction(NS::String::string("vs_main", NS::UTF8StringEncoding));
//         MTL::Function* fs = library->newFunction(NS::String::string("fs_main", NS::UTF8StringEncoding));

//         MTL::RenderPipelineDescriptor* pipelineDesc = MTL::RenderPipelineDescriptor::alloc()->init();
//         pipelineDesc->setVertexFunction(vs);
//         pipelineDesc->setFragmentFunction(fs);
//         pipelineDesc->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormatBGRA8Unorm);

//         instance.instance->framebufferRenderer = outputDevice->outputDevice->device->newRenderPipelineState(pipelineDesc, &error);
//         if (!instance.instance->framebufferRenderer) {
//             return gnReturnError(GN_FAILED_CREATE_DEVICE, error->localizedDescription()->utf8String());
//         }
//     }

//     return GN_SUCCESS;
// }

// GN_EXPORT void gnWaitForDeviceFn(const gnOutputDevice& device) {
//     NS::AutoreleasePool* pool = NS::AutoreleasePool::alloc()->init();

//     auto mtlDevice = device.physicalOutputDevice->physicalOutputDevice->device;

//     auto commandBuffer = device.outputDevice->commandQueue->commandBuffer();

//     commandBuffer->commit();
//     commandBuffer->waitUntilCompleted();

//     pool->release();
// }

// GN_EXPORT void gnDestroyOutputDeviceFn(gnOutputDevice& device) {
//     device.outputDevice->commandQueue->release();
//     device.physicalOutputDevice->physicalOutputDevice->device->release();
// }
