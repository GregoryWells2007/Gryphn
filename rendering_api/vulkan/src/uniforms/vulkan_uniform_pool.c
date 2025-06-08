#include "vulkan_uniform_pool.h"
#include "stdlib.h"

gnReturnCode gnCreateUniformPoolFn(gnUniformPool pool, gnDeviceHandle device) {
    pool->uniformPool = malloc(sizeof(struct gnPlatformUniformPool_t));

    pool->uniformPool->maxUniformPools = 0;
    pool->uniformPool->uniformPoolCount = 0;

    return GN_SUCCESS;
}
