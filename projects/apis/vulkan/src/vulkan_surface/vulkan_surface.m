#ifdef GN_PLATFORM_MACOS
#include "vulkan_surface.h"
#include "window_surface/gryphn_surface_create_functions.h"
#include "../instance/vulkan_instance.h"
#include <AppKit/AppKit.h>
#include <vulkan/vulkan_metal.h>
#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>
#import <QuartzCore/QuartzCore.h>
#import <Metal/Metal.h>


#include "vulkan/vulkan_metal.h"
gnReturnCode createMacOSWindowSurface(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnMacOSWindowSurfaceInfo createInfo) {
    windowSurface->windowSurface = malloc(sizeof(gnPlatformWindowSurface));
    VkMetalSurfaceCreateInfoEXT surfaceCreateInfo = {};
    surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT;
    surfaceCreateInfo.pNext = NULL;
    surfaceCreateInfo.flags = 0;
    surfaceCreateInfo.pLayer = createInfo.layer;

    VkResult result = vkCreateMetalSurfaceEXT(instance->instance->vk_instance, &surfaceCreateInfo, NULL, &windowSurface->windowSurface->surface);
    if (result != VK_SUCCESS)
        return GN_FAILED_TO_ATTACH_WINDOW;
    return GN_SUCCESS;
}
#endif
