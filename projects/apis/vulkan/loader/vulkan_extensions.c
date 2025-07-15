#include "vulkan_loader.h"

gnBool vulkanIsExtensionSupported(gnExtension extension){
    if (extension == GN_EXT_SYNCHRONIZATION) return gnTrue;
    if (extension == GN_EXT_QUEUES) return gnTrue;
    return gnFalse;
}
