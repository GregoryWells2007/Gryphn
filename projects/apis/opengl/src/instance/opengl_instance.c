#include "opengl_instance.h"

gnReturnCode openglCreateInstance(gnInstanceHandle instance, gnInstanceCreateInfo* instanceInfo, gryphnInstanceFunctionLayers* next) {
    if (instanceInfo->coreAPI != GN_RENDERINGAPI_OPENGL) return GN_UNSUPPORTED_API;
    return GN_SUCCESS;
}
void openglDestroyInstance(gnInstanceHandle instance, gryphnInstanceFunctionLayers* next) {

}
