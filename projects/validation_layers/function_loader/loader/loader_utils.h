#define CHECK_FUNCTION_WITH_RETURN_CODE(instance, function, ...) \
loaderLayer* nextLayer = loaderGetNextLayer(instance); \
if (nextLayer->deviceFunctions.function == NULL) { \
    gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){ \
        .message = gnCreateString("Failed to load destroy " #function " function") \
    }); \
    resetLayer(instance); \
    return GN_FAILED_TO_LOAD_FUNCTION; \
} \
return nextLayer->deviceFunctions.function(__VA_ARGS__);

#define CHECK_FUNCTION_WITH_RETURN_CODE_COMMAND(instance, function, ...) \
loaderLayer* nextLayer = loaderGetNextLayer(instance); \
if (nextLayer->commandFunctions.function == NULL) { \
    gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){ \
        .message = gnCreateString("Failed to load destroy " #function " function") \
    }); \
    resetLayer(instance); \
    return GN_FAILED_TO_LOAD_FUNCTION; \
} \
return nextLayer->commandFunctions.function(__VA_ARGS__);

#define CHECK_VOID_FUNCTION(instance, function, ...) \
loaderLayer* nextLayer = loaderGetNextLayer(instance); \
if (nextLayer->deviceFunctions.function == NULL) { \
    gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){ \
        .message = gnCreateString("Failed to load destroy " #function " function") \
    }); \
    resetLayer(instance); \
    return; \
} \
nextLayer->deviceFunctions.function(__VA_ARGS__);

#define CHECK_VOID_FUNCTION_COMMAND(instance, function, ...) \
loaderLayer* nextLayer = loaderGetNextLayer(instance); \
if (nextLayer->commandFunctions.function == NULL) { \
    gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){ \
        .message = gnCreateString("Failed to load destroy " #function " function") \
    }); \
    resetLayer(instance); \
    return; \
} \
nextLayer->commandFunctions.function(__VA_ARGS__);
