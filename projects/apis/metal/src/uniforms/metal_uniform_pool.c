#include <core/uniforms/gryphn_uniform_pool.h>
#include <core/uniforms/gryphn_uniform.h>
#include "metal_uniform.h"

gnReturnCode gnCreateUniformPoolFn(gnUniformPool pool, gnDeviceHandle device) {
    return GN_SUCCESS;
}

gnUniform* gnUniformPoolAllocateUniformsFn(gnUniformPool pool, const gnUniformLayout layout) {
    gnUniform* uniforms = malloc(sizeof(gnUniform) * layout.uniformBindingCount);
    for (int i = 0; i < layout.uniformBindingCount; i++) {
        uniforms[i] = malloc(sizeof(struct gnUniform_t));
        uniforms[i]->uniform = malloc(sizeof(struct gnPlatformUniform_t));
        uniforms[i]->uniform->type = layout.uniformBindings[i].type;
    }
    return uniforms;
}

void gnDestroyUniformPoolFn(gnUniformPool pool) { }
