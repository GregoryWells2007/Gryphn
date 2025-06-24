#include "gryphn_loader.h"
#include <apis/vulkan/loader/vulkan_loader.h>

gnInstanceFunctions loadInstanceFunctions(gnRenderingAPI api) {
    switch (api) {
    case GN_RENDERINGAPI_NONE: return (gnInstanceFunctions){ NULL };
    case GN_RENDERINGAPI_VULKAN: return loadVulkanFunctions(api);
    }
}
