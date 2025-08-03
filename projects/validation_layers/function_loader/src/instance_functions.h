#pragma once
#include "core/src/instance/gryphn_instance.h"
#include <core/src/window_surface/gryphn_surface_create_functions.h>

gnReturnCode checkCreateInstance(gnInstanceHandle instance, gnInstanceCreateInfo* info, gryphnInstanceFunctionLayers* next);
void checkDestroyInstance(gnInstanceHandle instance, gryphnInstanceFunctionLayers* next);

gnPhysicalDevice* checkGetPhysicalDevices(gnInstanceHandle instance, uint32_t* count);
gnBool checkCanDevicePresent(gnPhysicalDevice device, gnWindowSurfaceHandle windowSurface);

gnReturnCode checkCreateOutputDevice(gnInstanceHandle instance, gnOutputDeviceHandle device, gnOutputDeviceInfo deviceInfo);
void checkDestroyOutputDevice(gnOutputDeviceHandle device);

#ifdef GN_PLATFORM_MACOS
gnReturnCode checkCreateSurfaceMacOS(gnWindowSurfaceHandle windowSurface, gnInstanceHandle instance, gnMacOSWindowSurfaceInfo createInfo);
#endif
#ifdef GN_PLATFORM_LINUX
#ifdef GN_WINDOW_X11
gnReturnCode checkCreateX11WindowSurface(gnWindowSurface surface, gnInstance instance, gnX11WindowSurfaceInfo info);
#endif
#endif

void checkDestroyWindowSurface(gnWindowSurfaceHandle windowSurface);
gnSurfaceDetails checkGetSurfaceDetails(gnWindowSurfaceHandle windowSurface, gnPhysicalDevice device);
