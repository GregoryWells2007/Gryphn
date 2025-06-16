#include "vulkan_instance.h"
#include <debugger/vulkan_debugger.h>
#include <stdio.h>

typedef struct vkUserData {
    gnDebuggerCallback debuggerCallback;
    void* userData;
} vkUserData;

static VKAPI_ATTR VkBool32 VKAPI_CALL vk_debuggerDebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    gnMessageSeverity severity;
    gnMessageType type;
    gnMessageData data = {
        .message = gnCreateString(pCallbackData->pMessage)
    };

    switch (messageSeverity) {
    default: break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: severity = GN_MESSAGE_VERBOSE; break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: severity = GN_MESSAGE_INFO; break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: severity = GN_MESSAGE_WARNING; break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: severity = GN_MESSAGE_ERROR; break;
    }

    switch (messageType) {
    default: break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT: type = GN_DEBUG_MESSAGE_GENERAL; break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT: type = GN_DEBUG_MESSAGE_VALIDATION; break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT: type = GN_DEBUG_MESSAGE_PERFORMANCE; break;
    }

    vkUserData* userData = (vkUserData*)pUserData;
    gnDebuggerCallback callback = userData->debuggerCallback;
    gnBool result = callback(severity, type, data, userData->userData);
    if (result == gnFalse) return VK_FALSE;
    return VK_TRUE;
}

gnReturnCode gnCreateInstanceFn(gnInstanceHandle instance, gnInstanceInfo instanceInfo) {
    instance->instance = malloc(sizeof(gnPlatformInstance));
    instance->instance->instanceMessageCount = 0;

    #ifdef GN_PLATFORM_LINUX
    gnBool isX11 = gnTrue;
    uint32_t extensionCount = 3;
    const char* extensions[3];
    if (isX11) {
        extensions[0] = "VK_KHR_xlib_surface";
        extensions[1] = "VK_KHR_surface";
        extensions[2] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
    } else {
        extensions[0] = "VK_KHR_wayland_surface";
        extensions[1] = "VK_KHR_surface";
        extensions[2] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
    }
    #endif
    #ifdef GN_PLATFORM_WINDOWS
    uint32_t extensionCount = 3;
    const char* extensions[] = {
        "VK_KHR_win32_surface",
        "VK_KHR_surface",
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME
    };
    #endif
    #ifdef GN_PLATFORM_MACOS
    uint32_t extensionCount = 4;
    const char* extensions[] = {
        "VK_KHR_portability_enumeration",
        "VK_EXT_metal_surface",
        "VK_KHR_surface",
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME
    };
    #endif


    VkApplicationInfo appInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = gnToCString(instanceInfo.applicationName),
        .applicationVersion = instanceInfo.applicationVersion,
        .pEngineName = gnToCString(instanceInfo.engineName),
        .engineVersion = instanceInfo.engineVersion,
        .apiVersion = VK_API_VERSION_1_3,
    };

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    VkInstanceCreateFlags createFlags = 0;
    #ifdef GN_PLATFORM_MACOS
    createFlags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    #endif

    createInfo.flags = createFlags;

    if (instanceInfo.debugger != NULL) {
        for (int i = 0; i < instanceInfo.debugger->info.layerCount; i++) {
            if (instanceInfo.debugger->info.layers[i] == GN_DEBUGGER_LAYER_PLATFORM) {
                const char* validation_layers[1] = { "VK_LAYER_KHRONOS_validation" };
                createInfo.enabledLayerCount = 1;
                createInfo.ppEnabledLayerNames = (const char*[]){ "VK_LAYER_KHRONOS_validation" };
            }
        }

        vkUserData* userData = malloc(sizeof(vkUserData));
        userData->debuggerCallback = instanceInfo.debugger->info.callback;
        userData->userData = instanceInfo.debugger->info.userData;

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
        vkPopulateDebugMessengerCreateInfo(&debugCreateInfo);
        debugCreateInfo.pfnUserCallback = vk_debuggerDebugCallback;
        debugCreateInfo.pUserData = userData;
        createInfo.pNext = &debugCreateInfo;
    }


    createInfo.enabledExtensionCount = extensionCount;
    createInfo.ppEnabledExtensionNames = extensions;

    VkResult result = vkCreateInstance(&createInfo, NULL, &instance->instance->vk_instance);
    if (result != VK_SUCCESS)
        return GN_FAILED_CREATE_INSTANCE;
    instance->valid = gnTrue;

    return GN_SUCCESS;
}

void gnDestroyInstanceFn(gnInstanceHandle instance) {
    instance->valid = gnFalse;
    vkDestroyInstance(instance->instance->vk_instance, NULL);
}
