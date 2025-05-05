#include <vulkan/vulkan.h>
#include "vulkan_buffer_description.h"

GN_EXPORT gnReturnCode gnCreateBufferDescriptionFn(gnBufferDescription* bufferDescription, const gnGraphicsPipeline& graphicsPipeline) {
    if (bufferDescription->bufferDescription == nullptr) bufferDescription->bufferDescription = new gnPlatformBufferDescription();

    bufferDescription->bufferDescription->graphicsPipeline = const_cast<gnGraphicsPipeline*>(&graphicsPipeline);
    return GN_SUCCESS;
}
