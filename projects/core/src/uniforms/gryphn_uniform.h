#pragma once
#include "stdint.h"
#include "stdlib.h"
#include "utils/lists/gryphn_array_list.h"
#include "utils/gryphn_bool.h"
#include "gryphn_handles.h"

typedef struct gnBufferUniformInfo {
    uint32_t binding;
    gnBuffer buffer;
    size_t offset;
    size_t size;
    gnBool dynamic;
} gnBufferUniformInfo;

typedef struct gnStorageUniformInfo {
    gnBuffer buffer;
    size_t offset, size;
    uint32_t binding;
} gnStorageUniformInfo;

typedef struct gnImageUniformInfo {
    uint32_t binding;
    gnTexture texture;
} gnImageUniformInfo;

#ifdef GN_REVEAL_IMPL
struct gnUniform_t {
    struct gnPlatformUniform_t* uniform;
    gnUniformPool pool;
};
#endif
GN_ARRAY_LIST_HEADER(gnUniform);

void gnUpdateBufferUniform(gnUniform uniform, gnBufferUniformInfo bufferInfo);
void gnUpdateStorageUniform(gnUniform uniform, gnStorageUniformInfo storageInfo);
void gnUpdateImageUniform(gnUniform uniform, gnImageUniformInfo imageInfo);
