#include <core/uniforms/gryphn_uniform.h>
#include "metal_uniform.h"

void gnUpdateBufferUniformFn(gnUniform uniform, gnBufferUniformInfo* info) {
    uniform->uniform->data = malloc(sizeof(gnBufferUniformInfo));
    memcpy(uniform->uniform->data, info, sizeof(gnBufferUniformInfo));
}
