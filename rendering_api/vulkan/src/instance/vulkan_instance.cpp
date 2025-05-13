#include "gryphn/gryphn_utils.h"
#include "vector"
#include <cstring>
#include "debugger/vulkan_debugger.h"
#include "vulkan_instance.h"



// now I gotta do some shit to setup debug layers
bool checkValidationLayerSupport(gnList<gnString> layers_to_validate) {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (int i = 0; i < gnListLength(layers_to_validate); i++) {
        gnString layerName = layers_to_validate[i];
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(gnToCString(layerName), layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
            return false;
    }

    return true;
}

// std::vector<const char*> getRequiredExtensions(bool validation_layers_required, gnInstance& instance) {
//     // uint32_t glfwExtensionCount = 0;
//     // const char** glfwExtensions;
//     // glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

//     std::vector<const char*> extensions(instance.instance->extensions, instance.instance->extensions + instance.instance->extensionCount);

//     if (validation_layers_required) {
//         extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
//     }

//     #ifdef GN_PLATFORM_MACOS
//     extensions.push_back("VK_KHR_portability_enumeration");
//     extensions.push_back("VK_EXT_metal_surface");
//     #endif

//     return extensions;
// }

void gnInstanceSetAppInfoFn(gnInstance& instance, gnAppInfo& info) {
    if (instance.instance == nullptr) instance.instance = new gnPlatformInstanceData();

    instance.AppInfo = info;
    instance.instance->appInfo = {};
    // instance.instance_data->appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    // instance.instance_data->appInfo.pApplicationName = gnToCString(info.ApplicationName);
    // instance.instance_data->appInfo.applicationVersion = info.ApplicationVersion;
    // instance.instance_data->appInfo.pEngineName = gnToCString(info.EngineName);
    // instance.instance_data->appInfo.engineVersion = info.EngineVersion;
    // instance.instance_data->appInfo.apiVersion = VK_API_VERSION_1_0; // fuck ass code idk what to do with it
    instance.instance->appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    instance.instance->appInfo.pApplicationName = "Hello Triangle";
    instance.instance->appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    instance.instance->appInfo.pEngineName = "No Engine";
    instance.instance->appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    instance.instance->appInfo.apiVersion = VK_API_VERSION_1_3;
}

GN_EXPORT gnReturnCode gnCreateInstanceFn(gnInstance* instance) {
    if (instance->debugger != nullptr && !checkValidationLayerSupport(instance->debugger->debug_layers)) {
        return gnReturnError(GN_FAILED_CREATE_INSTANCE, "validation layers requested, but not available!");
    }
    gnInstanceSetAppInfoFn(*instance, instance->AppInfo);

    instance->valid = true;

    #ifdef GN_PLATFORM_LINUX
    #ifdef GN_WINDOW_X11
    instance->instance->extensions.push_back("VK_KHR_xlib_surface");
    #endif
    #ifdef GN_WINFDOW_WAYLAND
    instance->instance->extensions.push_back("VK_KHR_wayland_surface");
    #endif
    #endif
    #ifdef GN_PLATFORM_WINDOWS
    instance->instance->extensions.push_back("VK_MVK_macos_surface");
    #endif
    #ifdef GN_PLATFORM_MACOS
    instance->instance->extensions.push_back("VK_MVK_macos_surface");
    instance->instance->extensions.push_back("VK_KHR_portability_enumeration");
    instance->instance->extensions.push_back("VK_EXT_metal_surface");
    #endif


    instance->instance->extensions.push_back("VK_KHR_surface");
    if (instance->debugger)
        instance->instance->extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &instance->instance->appInfo;
    createInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    // auto extensions = getRequiredExtensions(instance->debugger);

    createInfo.enabledExtensionCount = static_cast<uint32_t>(instance->instance->extensions.size());;
    createInfo.ppEnabledExtensionNames = instance->instance->extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (instance->debugger != nullptr) {
        auto validation_layers = instance->debugger->debug_layers;

        gnList<const char*> validation_layers_c = gnCreateList<const char*>();
        for (int i = 0; i < gnListLength(validation_layers); i++)
            gnListAdd(validation_layers_c, gnToCString(validation_layers[i]));

        createInfo.enabledLayerCount = static_cast<uint32_t>(gnListLength(validation_layers_c));
        createInfo.ppEnabledLayerNames = gnListData(validation_layers_c);

        populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateInstance(&createInfo, nullptr, &instance->instance->vk_instance) != VK_SUCCESS) {
        return gnReturnError(GN_FAILED_CREATE_INSTANCE, "im to lazy to query vulkan why");
    }

    if (instance->debugger->debugger == nullptr) instance->debugger->debugger = new gnPlatformDebugger();
    instance->debugger->debugger->instance = &instance->instance->vk_instance;
    return GN_SUCCESS;
}

GN_EXPORT void gnDestroyInstanceFn(gnInstance& instance) {
    instance.valid = false;
    vkDestroySurfaceKHR(instance.instance->vk_instance, instance.instance->window_surface, nullptr);
    vkDestroyInstance(instance.instance->vk_instance, nullptr);
}
