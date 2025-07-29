#pragma once
#include <core/gryphn_return_code.h>
#include <vulkan/vulkan.h>

static inline gnReturnCode VkResultToGnReturnCode(VkResult result) {
    switch (result) {
        case VK_SUCCESS: return GN_SUCCESS;
        // case VK_NOT_READY: return ;
        // case VK_TIMEOUT: return ;
        // case VK_EVENT_SET: return ;
        // case VK_EVENT_RESET: return ;
        // case VK_INCOMPLETE: return ;
        case VK_ERROR_OUT_OF_HOST_MEMORY: return GN_OUT_OUT_HOST_MEMEORY;
        case VK_ERROR_OUT_OF_DEVICE_MEMORY: return GN_OUT_OUT_DEVICE_MEMORY;
        case VK_ERROR_INITIALIZATION_FAILED: return GN_FAILED_CREATE_OBJECT;
        // case VK_ERROR_DEVICE_LOST: return ;
        // case VK_ERROR_MEMORY_MAP_FAILED: return ;
        case VK_ERROR_LAYER_NOT_PRESENT: return GN_UNLOADED_LAYER;
        case VK_ERROR_EXTENSION_NOT_PRESENT: return GN_UNLOADED_EXTENSION;
        // case VK_ERROR_FEATURE_NOT_PRESENT: return ;
        // case VK_ERROR_INCOMPATIBLE_DRIVER: return ;
        // case VK_ERROR_TOO_MANY_OBJECTS: return ;
        case VK_ERROR_FORMAT_NOT_SUPPORTED: return GN_UNSUPPORTED_FORMAT;
        // case VK_ERROR_FRAGMENTED_POOL: return ;
        case VK_ERROR_UNKNOWN: return GN_UNKNOWN_ERROR;
        // case VK_ERROR_OUT_OF_POOL_MEMORY: return ;
        // case VK_ERROR_INVALID_EXTERNAL_HANDLE: return ;
        // case VK_ERROR_FRAGMENTATION: return ;
        // case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS: return ;
        // case VK_PIPELINE_COMPILE_REQUIRED: return ;
        // case VK_ERROR_NOT_PERMITTED: return ;
        // case VK_ERROR_SURFACE_LOST_KHR: return ;
        // case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: return ;
        case VK_SUBOPTIMAL_KHR: return GN_SUBOPTIMAL_PRESENTATION_QUEUE;
        case VK_ERROR_OUT_OF_DATE_KHR: return GN_OUT_OF_DATE_PRESENTATION_QUEUE;
        // case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: return ;
        // case VK_ERROR_VALIDATION_FAILED_EXT: return GN_UNKNOWN_ERROR;
        // case VK_ERROR_INVALID_SHADER_NV: return GN_UNKNOWN_ERROR;
        // case VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR: return GN_UNKNOWN_ERROR;
        // case VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR: return GN_UNKNOWN_ERROR;
        // case VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR: return GN_UNKNOWN_ERROR;
        // case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR: return GN_UNKNOWN_ERROR;
        // case VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR: return GN_UNKNOWN_ERROR;
        // case VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR: return GN_UNKNOWN_ERROR;
        // case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT: return GN_UNKNOWN_ERROR;
        // case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT: return GN_UNKNOWN_ERROR;
        // case VK_THREAD_IDLE_KHR: return GN_UNKNOWN_ERROR;
        // case VK_THREAD_DONE_KHR: return GN_UNKNOWN_ERROR;
        // case VK_OPERATION_DEFERRED_KHR: return GN_UNKNOWN_ERROR;
        // case VK_OPERATION_NOT_DEFERRED_KHR: return GN_UNKNOWN_ERROR;
        // case VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR: return GN_UNKNOWN_ERROR;
        // case VK_ERROR_COMPRESSION_EXHAUSTED_EXT: return GN_UNKNOWN_ERROR;
        // case VK_INCOMPATIBLE_SHADER_BINARY_EXT: return GN_UNKNOWN_ERROR;
        // case VK_PIPELINE_BINARY_MISSING_KHR: return GN_UNKNOWN_ERROR;
        // case VK_ERROR_NOT_ENOUGH_SPACE_KHR: return GN_UNKNOWN_ERROR;
    }
}
