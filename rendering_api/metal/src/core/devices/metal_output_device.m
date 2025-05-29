#include <core/output_device/gryphn_physical_output_device.h>
#include <Metal/Metal.h>
#include "metal_output_devices.h"
#include "core/instance/metal_instance.h"
#include "core/instance/gryphn_instance.h"
#include <core/debugger/gryphn_debugger.h>

gnReturnCode gnCreateOutputDeviceFn(gnOutputDevice* outputDevice, gnInstance* instance, struct gnOutputDeviceInfo_t deviceInfo) {
    outputDevice->outputDevice = malloc(sizeof(gnPlatformOutputDevice));
    outputDevice->outputDevice->device = deviceInfo.physicalDevice.physicalDevice->device.retain;
    outputDevice->outputDevice->queueCount = deviceInfo.queueInfoCount;
    outputDevice->outputDevice->queues = malloc(sizeof(id<MTLCommandQueue>) * deviceInfo.queueInfoCount);
    for (int i = 0; i < deviceInfo.queueInfoCount; i++) {
        outputDevice->outputDevice->queues[i] = outputDevice->outputDevice->device.newCommandQueue;
    }

    // {
    //     NSError* error = nil;
    //     MTLCompileOptions* options = nil;
    //     NSString *shaderSource = @"#include <metal_stdlib>\
    //     using namespace metal;\
    //     struct VertexOut {\
    //         float4 position [[position]];\
    //         float2 uv;\
    //     };\
    //     vertex VertexOut vs_main(uint vertexID [[vertex_id]]) {\
    //         float2 positions[4] = {\
    //             {-1.0, -1.0},\
    //             { 1.0, -1.0},\
    //             {-1.0,  1.0},\
    //             { 1.0,  1.0}\
    //         };\
    //         float2 uvs[4] = {\
    //             {0.0, 1.0},\
    //             {1.0, 1.0},\
    //             {0.0, 0.0},\
    //             {1.0, 0.0}\
    //         };\
    //         VertexOut out;\
    //         out.position = float4(positions[vertexID], 0.0, 1.0);\
    //         out.uv = uvs[vertexID];\
    //         return out;\
    //     }\
    //     fragment float4 fs_main(VertexOut in [[stage_in]],\
    //                             texture2d<float> colorTex [[texture(0)]],\
    //                             sampler samp [[sampler(0)]]) {\
    //         return colorTex.sample(samp, in.uv);\
    //     }\
    //     ";
    //     id<MTLLibrary> library = [outputDevice->outputDevice->device newLibraryWithSource:shaderSource options:nil error:&error];

    //     if (!library) {
    //         gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){
    //             .message = gnCreateString("Failed to compile framebuffer shader")
    //         });
    //         return GN_FAILED_TO_CREATE_DEVICE;
    //     }
    //     // id<MTLFunction> vs = library->newFunction(NS::String::string("vs_main", NS::UTF8StringEncoding));
    //     id<MTLFunction> vs = [library newFunctionWithName:@"vs_main"];
    //     id<MTLFunction> fs = [library newFunctionWithName:@"fs_main"];

    //     if (vs == nil) {
    //         gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){
    //             .message = gnCreateString("Failed to compile frambuffer vertex shader")
    //         });
    //         return GN_FAILED_TO_CREATE_DEVICE;
    //     }

    //     if (fs == nil) {
    //         gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){
    //             .message = gnCreateString("Failed to compile frambuffer fragment shader")
    //         });
    //         return GN_FAILED_TO_CREATE_DEVICE;
    //     }

    //     MTLRenderPipelineDescriptor* pipelineDesc =[[MTLRenderPipelineDescriptor alloc] init];;
    //     pipelineDesc.vertexFunction = vs;
    //     pipelineDesc.fragmentFunction = fs;
    //     pipelineDesc.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;

    //     outputDevice->outputDevice->framebuffer = [outputDevice->outputDevice->device newRenderPipelineStateWithDescriptor:pipelineDesc error:&error];
    //     if (!outputDevice->outputDevice->framebuffer) {
    //         gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){
    //             .message = gnCreateString("Failed to create frambuffer render pipeline")
    //         });
    //         return GN_FAILED_TO_CREATE_DEVICE;
    //     }
    // }

    return GN_SUCCESS;
}

void gnDestroyOutputDeviceFn(gnOutputDevice* device) {
    for (int i = 0; i < device->outputDevice->queueCount; i++) {
        [device->outputDevice->queues[i] release];
    }
    [device->outputDevice->device release];
    free(device->outputDevice);
}

// struct mtlFramebufferVertex {
//     float x, y;
//     float u, v;
// };
