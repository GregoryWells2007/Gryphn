#pragma once
#include <vulkan/vulkan.h>
#include <core/debugger/gryphn_debugger.h>

struct gnPlatformDebugger {
    VkDebugUtilsMessengerEXT debugMessenger;
    VkInstance* instance;
};

void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
