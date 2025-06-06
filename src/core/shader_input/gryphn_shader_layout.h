#pragma once
#include "stdint.h"
#include "stdlib.h"

typedef enum gnVertexFormat {
    GN_FLOAT2
} gnVertexFormat;

typedef struct gnVertexAttribute {
    uint32_t location;
    gnVertexFormat format;
    size_t offset;
} gnVertexAttribute;

typedef struct gnBufferAttribute {
    uint32_t binding;
    size_t size;
    uint32_t attributeCount;
    gnVertexAttribute* attributes;
} gnBufferAttribute;

typedef struct gnShaderInputLayout {
    uint32_t bufferCount;
    gnBufferAttribute* bufferAttributes;
} gnShaderInputLayout;
