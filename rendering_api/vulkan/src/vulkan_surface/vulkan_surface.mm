#ifdef GN_PLATFORM_MACOS
#include "vulkan_surface.h"
#include "../instance/vulkan_instance.h"
#include <AppKit/AppKit.h>
#include <vulkan/vulkan_metal.h>
#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>
#import <QuartzCore/QuartzCore.h>
#import <Metal/Metal.h>


#include "vulkan/vulkan_metal.h"
GN_EXPORT gnReturnCode gnCreateMacOSWindowSurfaceFn(struct gnWindowSurface_t* windowSurface, gnInstance* instance, struct gnMacOSWindowSurfaceInfo_t createInfo) {
    NSWindow* window = (__bridge NSWindow*)createInfo.window;
    NSView* view = [window contentView];

    CAMetalLayer* layer = [CAMetalLayer layer];
    [layer setContentsScale:[window backingScaleFactor]];
    [layer setFramebufferOnly:YES];

    [view setLayer:layer];
    [view setWantsLayer:YES];

    windowSurface->windowSurface = new gnPlatformWindowSurface();
    VkMetalSurfaceCreateInfoEXT surfaceCreateInfo = {};
    surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT;
    surfaceCreateInfo.pNext = nullptr;
    surfaceCreateInfo.flags = 0;
    surfaceCreateInfo.pLayer = layer;

    VkResult result = vkCreateMetalSurfaceEXT(instance->instance->vk_instance, &surfaceCreateInfo, nullptr, &windowSurface->windowSurface->surface);
    if (result != VK_SUCCESS)
        return GN_FAILED_TO_ATTACH_WINDOW;
    return GN_SUCCESS;
}
#endif
