#include "vulkan_instance.h"
#include "vulkan_result_converter.h"
GN_ARRAY_LIST_DEFINITION(vkString)


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
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: severity = GN_MESSAGE_VERBOSE; break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: severity = GN_MESSAGE_INFO; break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: severity = GN_MESSAGE_WARNING; break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: severity = GN_MESSAGE_ERROR; break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT: {
        VkDebugUtilsMessengerCallbackDataEXT callbackData = {
            .pMessage = "Error triggered with VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT, this indicates a big within vulkan"
        };
        vk_debuggerDebugCallback(VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT, VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT, &callbackData, pUserData);
        severity = GN_MESSAGE_ERROR;
    }
    }

    switch (messageType) {
    case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT: type = GN_DEBUG_MESSAGE_GENERAL; break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT: type = GN_DEBUG_MESSAGE_VALIDATION; break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT: type = GN_DEBUG_MESSAGE_PERFORMANCE; break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT: type = GN_DEBUG_MESSAGE_PERFORMANCE; break;
    }

    vkUserData* userData = (vkUserData*)pUserData;
    gnDebuggerCallback callback = userData->debuggerCallback;
    gnBool result = callback(severity, type, data, userData->userData);
    if (result == GN_FALSE) return VK_FALSE;
    return VK_TRUE;
}

gnReturnCode vulkanCreateInstance(gnInstanceHandle instance, gnInstanceCreateInfo* instanceInfo, gryphnInstanceFunctionLayers* next, gnAllocators* alloctors) {
    if (next != NULL) { return GN_SUCCESS; }
    instance->instance = alloctors->malloc(sizeof(gnPlatformInstance), alloctors->userData);

    vkStringArrayList extensions = vkStringArrayListCreate();
    vkStringArrayListAdd(extensions, "VK_KHR_surface");
    vkStringArrayListReserve(extensions, 5);

    #ifdef GN_PLATFORM_MACOS
    vkStringArrayListAdd(extensions, "VK_EXT_metal_surface");
    vkStringArrayListAdd(extensions, "VK_KHR_portability_enumeration");
    #elif GN_PLATFORM_WINDOWS
    vkStringArrayListAdd(extensions, "VK_KHR_win32_surface");
    #elif GN_PLATFORM_LINUX
    #ifdef GN_WINDOW_X11
    vkStringArrayListAdd(extensions, "VK_KHR_xlib_surface");
    #endif
    #endif


    VkApplicationInfo appInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = gnToCString(instanceInfo->applicationInfo.applicationName),
        .applicationVersion = instanceInfo->applicationInfo.applicationVersion,
        .pEngineName = gnToCString(instanceInfo->applicationInfo.engineName),
        .engineVersion = instanceInfo->applicationInfo.engineVersion,
        .apiVersion = VK_API_VERSION_1_3,
    };

    VkInstanceCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .flags = 0,
        .pApplicationInfo = &appInfo
    };

    #ifdef GN_PLATFORM_MACOS
    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    #endif

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
    const char* enabledLayerNames = "VK_LAYER_KHRONOS_validation";
    if (instance->enabledLayerCounts[GN_DEBUGGER_LAYER_PLATFORM] > 0) {
        vkStringArrayListAdd(extensions, VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        createInfo.enabledLayerCount = 1;
        createInfo.ppEnabledLayerNames = &enabledLayerNames;

        instance->instance->userData.debuggerCallback = instanceInfo->debuggerInfo.callback;
        instance->instance->userData.userData = instanceInfo->debuggerInfo.userData;

        debugCreateInfo = (VkDebugUtilsMessengerCreateInfoEXT){
            .pNext = NULL,
            .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
            .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
            .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        };
        debugCreateInfo.pfnUserCallback = vk_debuggerDebugCallback;
        debugCreateInfo.pUserData = &instance->instance->userData;
        createInfo.pNext = &debugCreateInfo;
    }


    createInfo.enabledExtensionCount = vkStringArrayListCount(extensions);
    createInfo.ppEnabledExtensionNames = vkStringArrayListData(extensions);
    return VkResultToGnReturnCode(vkCreateInstance(&createInfo, NULL, &instance->instance->vk_instance));
}

void vulkanDestroyInstance(gnInstanceHandle instance, gryphnInstanceFunctionLayers* next, gnAllocators* alloctors) {
    if (next != NULL) { return; }
    vkDestroyInstance(instance->instance->vk_instance, NULL);
    alloctors->free(instance->instance, alloctors->userData);
}
