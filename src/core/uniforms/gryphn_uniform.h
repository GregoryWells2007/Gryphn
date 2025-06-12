#pragma once
#include "stdint.h"
#include "stdlib.h"
#include "utils/lists/gryphn_array_list.h"
#include "core/gryphn_handles.h"

typedef struct gnBufferUniformInfo {
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
GN_ARRAY_LIST(gnUniform)

void gnUpdateBufferUniform(gnUniform uniform, gnBufferUniformInfo bufferInfo);
