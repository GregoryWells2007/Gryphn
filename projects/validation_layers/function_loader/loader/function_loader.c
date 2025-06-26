#include "function_loader.h"

gnInstanceFunctions loadFunctionLoaderInstanceFunctions(gnInstanceFunctions* callbacks) {
    return *callbacks;
}
gnDeviceFunctions loadFunctionLoaderDeviceFunctions(gnDeviceFunctions* callbacks) {
    return *callbacks;
}
gnCommandFunctions loadFunctionLoaderCommandFunctions(gnCommandFunctions* callbacks) {
    return *callbacks;
}
