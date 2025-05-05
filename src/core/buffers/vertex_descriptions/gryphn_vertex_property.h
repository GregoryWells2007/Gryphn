#pragma once
#include <gryphn/gryphn_utils.h>

enum gnVertexDataFormat {
    GN_FLOAT, GN_FLOAT2, GN_FLOAT3, GN_FLOAT4, GN_UINT
};

struct gnVertexProperty {
ACCESS_LEVEL:

public:
    int binding;
    int location;
    gnVertexDataFormat format;
    size_t offset;
public:
    gnVertexProperty() {}
};
