#include "vulkan_device_extensions.h"
#include "stdlib.h"

const char* *vkGetGryphnDeviceExtensions(uint32_t* count) {
    const char* *extensiosns = malloc(sizeof(const char*));
    extensiosns[0] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;

    *count = 1;
    #ifdef GN_PLATFORM_MACOS
    *count++;
    extensiosns = realloc(sizeof(const char*), *count);
    extensiosns[1] = "VK_KHR_portability_subset";
    #endif

    return extensiosns;
}
