#include <gryphn/gryphn_utils.h>
#include "core/buffers/vertex_descriptions/gryphn_binding_description.h"
#include "core/buffers/vertex_descriptions/gryphn_vertex_description.h"
#include "vulkan_vertex_description.h"

GN_EXPORT void gnVertexDescriptionSetPropertiesCountFn(gnVertexDescription& vertexDescription, int count) {
    if (vertexDescription.vertexDescription == nullptr) vertexDescription.vertexDescription = new gnPlatformVertexDescription();

    // anyone smart would not use malloc in C but fuck you im not smart and plus I kinda dont care if this shit breaks brinkerhoff aint going to know
    vertexDescription.vertexDescription->attributeDescriptions = (VkVertexInputAttributeDescription*)malloc(sizeof(VkVertexInputAttributeDescription) * count);
    vertexDescription.vertexDescription->attributeDescriptionCount = count;
}

GN_EXPORT void gnVertexDescriptionSetPropertyFn(gnVertexDescription& vertexDescription, int index, const gnVertexProperty& property) {
    if (vertexDescription.vertexDescription == nullptr) vertexDescription.vertexDescription = new gnPlatformVertexDescription();
    vertexDescription.vertexDescription->attributeDescriptions[index].binding = property.binding;
    vertexDescription.vertexDescription->attributeDescriptions[index].location = property.location;

    if (property.format == GN_FLOAT) vertexDescription.vertexDescription->attributeDescriptions[index].format = VK_FORMAT_R32_SFLOAT;
    else if (property.format == GN_FLOAT2) vertexDescription.vertexDescription->attributeDescriptions[index].format = VK_FORMAT_R32G32_SFLOAT;
    else if (property.format == GN_FLOAT3) vertexDescription.vertexDescription->attributeDescriptions[index].format = VK_FORMAT_R32G32B32_SFLOAT;
    else if (property.format == GN_FLOAT4) vertexDescription.vertexDescription->attributeDescriptions[index].format = VK_FORMAT_R32G32B32A32_SFLOAT;

    else if (property.format == GN_UINT) vertexDescription.vertexDescription->attributeDescriptions[index].format = VK_FORMAT_R32_UINT;

    vertexDescription.vertexDescription->attributeDescriptions[index].offset = property.offset;
}

GN_EXPORT void gnVertexDescriptionSetBindingDescriptionFn(gnVertexDescription& vertexDescription, const gnBindingDescription& description) {
    if (vertexDescription.vertexDescription == nullptr) vertexDescription.vertexDescription = new gnPlatformVertexDescription();
    vertexDescription.vertexDescription->bindingDescription.binding = description.binding;
    vertexDescription.vertexDescription->bindingDescription.stride = description.stride;
    vertexDescription.vertexDescription->bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
}

// gnVertexDescription::gnVertexDescription() {
//     vertexDescription = new gnPlatformVertexDescription();
// }
