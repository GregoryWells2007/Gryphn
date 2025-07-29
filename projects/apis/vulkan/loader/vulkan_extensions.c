#include "vulkan_loader.h"

gnBool vulkanIsExtensionSupported(gnExtension extension){
    if (extension == GN_EXT_SYNCHRONIZATION) return GN_TRUE;
    if (extension == GN_EXT_QUEUES) return GN_TRUE;
    return GN_FALSE;
}
