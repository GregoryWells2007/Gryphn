#include <output_device/gryphn_physical_output_device.h>
#include <Metal/Metal.h>
#include "metal_output_devices.h"
#include "instance/metal_instance.h"
#include "instance/gryphn_instance.h"

#include "metal_shader.msl"

gnReturnCode createMetalOutputDevice(gnInstanceHandle instance, gnOutputDeviceHandle outputDevice, gnOutputDeviceInfo deviceInfo) {
    if (instance == GN_NULL_HANDLE) return GN_INVALID_HANDLE;

    outputDevice->outputDevice = malloc(sizeof(gnPlatformOutputDevice));
    outputDevice->outputDevice->device = deviceInfo.physicalDevice->physicalDevice->device.retain;
    outputDevice->outputDevice->transferQueue = outputDevice->outputDevice->device.newCommandQueue;

    // create full screen quad
    float verticies[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
         1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 0.0f,
    };
    outputDevice->outputDevice->fullScreenQuadBuffer =
        [outputDevice->outputDevice->device
            newBufferWithBytes:verticies
            length:sizeof(verticies)
            options:MTLResourceStorageModeShared
        ];

    NSError *error = nil;
    outputDevice->outputDevice->fullScreenShader = [outputDevice->outputDevice->device
        newLibraryWithSource:@(shader_source)
        options:nil
        error:&error
    ];
    if (!outputDevice->outputDevice->fullScreenShader) {
        gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){
            .message = gnCombineStrings(gnCreateString("Failed to create shader for output device: \n"), error.localizedDescription.UTF8String)
        });
        return GN_DEVICE_LOST;
    }

    outputDevice->outputDevice->fullScreenVertex = [outputDevice->outputDevice->fullScreenShader newFunctionWithName:@"fullscreen_vertex"];
    outputDevice->outputDevice->fullScreenFragment = [outputDevice->outputDevice->fullScreenShader newFunctionWithName:@"fullscreen_fragment"];

    MTLRenderPipelineDescriptor *pipelineDesc = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineDesc.vertexFunction = outputDevice->outputDevice->fullScreenVertex;
    pipelineDesc.fragmentFunction = outputDevice->outputDevice->fullScreenFragment;
    pipelineDesc.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;
    pipelineDesc.depthAttachmentPixelFormat = MTLPixelFormatInvalid;
    pipelineDesc.stencilAttachmentPixelFormat = MTLPixelFormatInvalid;

    outputDevice->outputDevice->fullScreenPipeline = [outputDevice->outputDevice->device newRenderPipelineStateWithDescriptor:pipelineDesc error:&error];
    if (!outputDevice->outputDevice->fullScreenPipeline) {
        gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){
            .message = gnCombineStrings(gnCreateString("Failed to create graphics pipeline for output device: \n"), error.localizedDescription.UTF8String)
        });
        return GN_DEVICE_LOST;
    }

    return GN_SUCCESS;
}

void waitForMetalDevice(gnOutputDeviceHandle device) {
    [device->outputDevice->executingCommandBuffer waitUntilCompleted];
}

void destroyMetalOutputDevice(gnOutputDeviceHandle device) {
    [device->outputDevice->transferQueue release];
    [device->outputDevice->device release];

    [device->outputDevice->fullScreenQuadBuffer release];
    [device->outputDevice->fullScreenShader release];
    [device->outputDevice->fullScreenVertex release];
    [device->outputDevice->fullScreenFragment release];
    [device->outputDevice->fullScreenPipeline release];

    free(device->outputDevice);
}

// struct mtlFramebufferVertex {
//     float x, y;
//     float u, v;
// };
