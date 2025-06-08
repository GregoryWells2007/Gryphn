#pragma once
#include "stdint.h"
#include "stdlib.h"
#include "core/gryphn_handles.h"

typedef struct gnBufferUniformInfo {
    gnUniform uniform;
    uint32_t binding;
    gnBuffer buffer;
    size_t offset;
    size_t size;
} gnBufferUniformInfo;

#ifdef GN_REVEAL_IMPL
struct gnUniform_t {
    struct gnPlatformUniform_t* uniform;
    gnUniformPool pool;
};
#endif

void gnUpdateBufferUniform(gnUniform uniform, gnBufferUniformInfo bufferInfo);
