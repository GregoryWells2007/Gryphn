#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

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

std::vector<const char*> getRequiredExtensions(bool validation_layers_required) {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (validation_layers_required) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
    extensions.push_back("VK_KHR_portability_enumeration");
    extensions.push_back("VK_EXT_metal_surface");

    return extensions;
}

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

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &instance->instance->appInfo;
    createInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    auto extensions = getRequiredExtensions(instance->debugger);

    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());;
    createInfo.ppEnabledExtensionNames = extensions.data();

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

GN_EXPORT gnReturnCode gnInstanceSetWindowFn(gnInstance& instance, GLFWwindow* window) {
    instance.instance->window = window;

    if (glfwVulkanSupported() != GLFW_TRUE) {
        return gnReturnError(GN_UNSUPPORTED_RENDERING_API, "vulkan is not actually supported\n");
    }

    VkResult result = glfwCreateWindowSurface(instance.instance->vk_instance, window, nullptr, &instance.instance->window_surface);\
    if (result != VK_SUCCESS)
        return gnReturnError(GN_FAILED_TO_ATTACH_WINDOW, std::to_string(result).c_str());
    return GN_SUCCESS;
}
