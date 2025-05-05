#include "metal_vertex_description.h"

// MTL::VertexDescriptor* flatVertexDescriptor = MTL::VertexDescriptor::alloc()->init();
// auto attributes = flatVertexDescriptor->attributes();
// attributes->object(0)->setFormat(MTL::VertexFormat::VertexFormatFloat2);
// attributes->object(0)->setOffset(offsetof(Vertex, position));
// attributes->object(0)->setBufferIndex(0);
// attributes->object(1)->setFormat(MTL::VertexFormat::VertexFormatFloat3);
// attributes->object(1)->setOffset(offsetof(Vertex, uv));
// attributes->object(1)->setBufferIndex(0);
// flatVertexDescriptor->layouts()->object(0)->setStride(sizeof(Vertex));

GN_EXPORT void gnVertexDescriptionSetBindingDescriptionFn(gnVertexDescription& vertexDescription, const gnBindingDescription& binding) {
    if (!vertexDescription.vertexDescription) vertexDescription.vertexDescription = new gnPlatformVertexDescription();

    vertexDescription.vertexDescription->binding = binding.binding;
    vertexDescription.vertexDescription->vertexDescriptor = MTL::VertexDescriptor::alloc()->init();
    vertexDescription.vertexDescription->vertexDescriptor->layouts()->object(0)->setStride(binding.stride);
    // auto attributes = vertexDescriptor->attributes();
    // attributes->object(0)->setFormat(MTL::VertexFormat::VertexFormatFloat2);
    // attributes->object(0)->setOffset(offsetof(Vertex, position));
    // attributes->object(0)->setBufferIndex(0);
}

GN_EXPORT void gnVertexDescriptionSetPropertiesCountFn(gnVertexDescription& vertexDescription, int count) {
    if (!vertexDescription.vertexDescription) vertexDescription.vertexDescription = new gnPlatformVertexDescription();
    vertexDescription.vertexDescription->descriptorCount = count;
    // this does nothing on metal but I guess imma do something with it cuz it exists
}

GN_EXPORT void gnVertexDescriptionSetPropertyFn(gnVertexDescription& vertexDescription, int index, const gnVertexProperty& property) {
    if (!vertexDescription.vertexDescription) vertexDescription.vertexDescription = new gnPlatformVertexDescription();

    auto attribute = vertexDescription.vertexDescription->vertexDescriptor->attributes()->object(index);
    attribute->setBufferIndex(0);

    switch(property.format) {
        case GN_FLOAT: attribute->setFormat(MTL::VertexFormat::VertexFormatFloat); break;
        case GN_FLOAT2: attribute->setFormat(MTL::VertexFormat::VertexFormatFloat2); break;
        case GN_FLOAT3: attribute->setFormat(MTL::VertexFormat::VertexFormatFloat3); break;
        case GN_FLOAT4: attribute->setFormat(MTL::VertexFormat::VertexFormatFloat4); break;
        case GN_UINT: attribute->setFormat(MTL::VertexFormat::VertexFormatUInt); break;
    }

    attribute->setOffset(property.offset);
}
