#include "opengl_uniform_pool.h"
#include "uniforms/uniform/opengl_uniform.h"

gnReturnCode openglCreateUniformPool(gnUniformPool pool, gnDeviceHandle device) {
    return GN_SUCCESS;
}
gnUniform* openglAllocateUniforms(gnUniformPool pool, const gnUniformAllocationInfo allocInfo) {
    gnUniform* uniforms = malloc(sizeof(gnUniform) * allocInfo.setCount);
    for (int i = 0; i < allocInfo.setCount; i++) {
        uniforms[i] = malloc(sizeof(struct gnUniform_t));
        uniforms[i]->uniform = malloc(sizeof(struct gnPlatformUniform_t));
    }
    return uniforms;
}
void openglDestroyUniformPool(gnUniformPool pool) {

}
