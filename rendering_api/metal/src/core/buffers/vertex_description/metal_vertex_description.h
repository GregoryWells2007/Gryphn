#include <core/buffers/vertex_descriptions/gryphn_vertex_description.h>
#include <Metal/Metal.hpp>

struct gnPlatformVertexDescription {
    MTL::VertexDescriptor* vertexDescriptor = nullptr;
    uint32_t binding;
    uint32_t descriptorCount;
};
