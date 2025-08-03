#pragma once
#include <vulkan/vulkan.h>
#include "instance/gryphn_instance.h"
#include "utils/lists/gryphn_array_list.h"
#include "loader/src/gryphn_instance_functions.h"

typedef struct vkUserData {
    gnDebuggerCallback debuggerCallback;
    void* userData;
} vkUserData;

typedef struct gnPlatformInstance_t {
    VkInstance vk_instance;
    vkUserData userData;
} gnPlatformInstance;

gnReturnCode vulkanCreateInstance(gnInstanceHandle instance, gnInstanceCreateInfo* instanceInfo, PFN_gnCreateInstance_layer* next);
void vulkanDestroyInstance(gnInstanceHandle instance, PFN_gnDestroyInstance_layer* next);

typedef const char* vkString;
GN_ARRAY_LIST(vkString);
