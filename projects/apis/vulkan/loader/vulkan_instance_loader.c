#include "vulkan_loader.h"
#include "instance/vulkan_instance.h"

gnInstanceFunctions loadVulkanFunctions(gnRenderingAPI api) {
    return (gnInstanceFunctions){
        ._gnCreateInstance = createInstance
    };
}
