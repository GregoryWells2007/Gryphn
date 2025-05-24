// #include "vulkan_swapchain.h"
// #include "core/presentation_queue/gryphn_device_presentation_details.h"
// #include "../output_device/vulkan_output_devices.h"
// #include "../instance/vulkan_instance.h"

// GN_EXPORT gnDevicePresentationDetails gnGetDevicePresentationDetailsFn(const gnPhysicalOutputDevice& physicalOutputDevice) {
//     SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalOutputDevice.physicalOutputDevice->instance->instance->window_surface, physicalOutputDevice.physicalOutputDevice->device);

//     gnDevicePresentationDetails presentationDetails = gnDevicePresentationDetails{};
//     presentationDetails.MinimumImageCount = swapChainSupport.capabilities.minImageCount;
//     presentationDetails.MaximumImageCount = swapChainSupport.capabilities.maxImageCount;

//     return presentationDetails;
// }
