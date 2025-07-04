#include "instance_functions.h"
#include "core/src/debugger/gryphn_debugger.h"
#include "core/src/output_device/gryphn_output_device.h"
#include "core/src/window_surface/gryphn_surface.h"

gnReturnCode checkCreateInstance(gnInstanceHandle instance, gnInstanceInfo info) {
    loaderLayer* nextLayer = loaderGetNextLayer(instance);
    if (nextLayer->instanceFunctions._gnCreateInstance == NULL) {
        gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load create instance function")
        });
        resetLayer(instance);
        return GN_FAILED_TO_LOAD_FUNCTION;
    }
    return nextLayer->instanceFunctions._gnCreateInstance(instance, info);
}

void checkDestroyInstance(gnInstance instance) {
    loaderLayer* nextLayer = loaderGetNextLayer(instance);
    if (nextLayer->instanceFunctions._gnDestroyInstance == NULL) {
        gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load destroy instance function")
        });
        resetLayer(instance);
        return;
    }
    nextLayer->instanceFunctions._gnDestroyInstance(instance);
}

gnPhysicalDevice* checkGetPhysicalDevices(gnInstanceHandle instance, uint32_t* count) {
    loaderLayer* nextLayer = loaderGetNextLayer(instance);
    if (nextLayer->instanceFunctions._gnGetPhysicalDevices == NULL) {
        gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load get physical devices function")
        });
        resetLayer(instance);
    }
    return nextLayer->instanceFunctions._gnGetPhysicalDevices(instance, count);
}
gnBool checkQueueCanPresentToSurface(const gnPhysicalDevice device, uint32_t queueIndex, const gnWindowSurfaceHandle windowSurface) {
    loaderLayer* nextLayer = loaderGetNextLayer(device.instance);
    if (nextLayer->instanceFunctions._gnQueueCanPresentToSurface == NULL) {
        gnDebuggerSetErrorMessage(device.instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load queue can present to surface function")
        });
        resetLayer(device.instance);
        return gnFalse;
    }
    return nextLayer->instanceFunctions._gnQueueCanPresentToSurface(device, queueIndex, windowSurface);
}

gnReturnCode checkCreateOutputDevice(gnOutputDeviceHandle device, gnInstanceHandle instance, gnOutputDeviceInfo deviceInfo) {
    loaderLayer* nextLayer = loaderGetNextLayer(device->instance);
    if (nextLayer->instanceFunctions._gnCreateOutputDevice == NULL) {
        gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load create output device function")
        });
        resetLayer(device->instance);
        return GN_FAILED_TO_LOAD_FUNCTION;
    }
    return nextLayer->instanceFunctions._gnCreateOutputDevice(device, instance, deviceInfo);
}
void checkDestroyOutputDevice(gnOutputDeviceHandle device) {
    loaderLayer* nextLayer = loaderGetNextLayer(device->instance);
    if (nextLayer->instanceFunctions._gnDestroyOutputDevice == NULL) {
        gnDebuggerSetErrorMessage(device->instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load destroy output device function")
        });
        resetLayer(device->instance);
    }
    return nextLayer->instanceFunctions._gnDestroyOutputDevice(device);
}

#ifdef GN_PLATFORM_MACOS
gnReturnCode checkCreateSurfaceMacOS(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnMacOSWindowSurfaceInfo createInfo) {
    loaderLayer* nextLayer = loaderGetNextLayer(instance);
    if (nextLayer->instanceFunctions._gnCreateMacOSWindowSurface == NULL) {
        gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load create window surface function")
        });
        resetLayer(instance);
        return GN_FAILED_TO_LOAD_FUNCTION;
    }
    return nextLayer->instanceFunctions._gnCreateMacOSWindowSurface(windowSurface, instance, createInfo);
}
#endif
#ifdef GN_PLATFORM_LINUX
#ifdef GN_WINDOW_X11
gnReturnCode checkCreateX11WindowSurface(gnWindowSurface surface, gnInstance instance, gnX11WindowSurfaceInfo info) {
    loaderLayer* nextLayer = loaderGetNextLayer(instance);
    if (nextLayer->instanceFunctions._gnCreateX11WindowSurface == NULL) {
        gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load _gnCreateX11WindowSurface this may indicate a bug within gryphn")
        });
        resetLayer(instance);
        return GN_FAILED_TO_LOAD_FUNCTION;
    }
    return nextLayer->instanceFunctions._gnCreateX11WindowSurface(surface, instance, info);
}
#endif
#endif

void checkDestroyWindowSurface(gnWindowSurfaceHandle windowSurface) {
    loaderLayer* nextLayer = loaderGetNextLayer(windowSurface->instance);
    if (nextLayer->instanceFunctions._gnDestroyWindowSurface == NULL) {
        gnDebuggerSetErrorMessage(windowSurface->instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load destroy create surface function")
        });
        resetLayer(windowSurface->instance);
    }
    return nextLayer->instanceFunctions._gnDestroyWindowSurface(windowSurface);
}
gnSurfaceDetails checkGetSurfaceDetails(gnWindowSurfaceHandle windowSurface, gnPhysicalDevice device) {
    loaderLayer* nextLayer = loaderGetNextLayer(windowSurface->instance);
    if (nextLayer->instanceFunctions._gnGetSurfaceDetails == NULL) {
        gnDebuggerSetErrorMessage(windowSurface->instance->debugger, (gnMessageData){
            .message = gnCreateString("Failed to load get surface details function")
        });
        resetLayer(windowSurface->instance);
    }
    return nextLayer->instanceFunctions._gnGetSurfaceDetails(windowSurface, device);
}
