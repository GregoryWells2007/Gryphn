#include "vulkan_device_extensions.h"
#include "utils/gryphn_bool.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

const char* *vkGetGryphnDeviceExtensions(uint32_t* outCount, VkPhysicalDevice device) {
    uint32_t count = 1;
    const char* *extensiosns = malloc(sizeof(const char*) * count);
    extensiosns[count-1] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;

    #ifdef GN_PLATFORM_MACOS
    count++;
    extensiosns = realloc(extensiosns, sizeof(const char*) * count);
    extensiosns[(count - 1)] = "VK_KHR_portability_subset";
    #endif

    uint32_t extensionCount = 0;
    vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, NULL);
    VkExtensionProperties* vkExtensions = malloc(sizeof(VkExtensionProperties) * extensionCount);
    vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, vkExtensions);

    gnBool supportsDescriptorPoolOverallocation = gnFalse;
    for (uint32_t i = 0; i < extensionCount; i++) {
        if (strcmp(VK_NV_DESCRIPTOR_POOL_OVERALLOCATION_EXTENSION_NAME, vkExtensions[i].extensionName) == 0) {
            supportsDescriptorPoolOverallocation = gnTrue;
            break;
        }
    }
    free(vkExtensions);

    // if (supportsDescriptorPoolOverallocation) {
    //     count++;
    //     extensiosns = realloc(extensiosns, sizeof(const char*) * count);
    //     extensiosns[(count - 1)] = VK_NV_DESCRIPTOR_POOL_OVERALLOCATION_EXTENSION_NAME;
    // }

    *outCount = count;

    return extensiosns;
}
