#define CHECK_FUNCTION_WITH_RETURN_CODE(instance, function, type, ...) \
loaderLayer* nextLayer = loaderGetNextLayer(instance); \
if (nextLayer->type.function == NULL) { \
    gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){ \
        .message = gnCreateString("Failed to load " #function " this indicates a bug within gryphn") \
    }); \
    resetLayer(instance); \
    return GN_FAILED_TO_LOAD_FUNCTION; \
} \
return nextLayer->type.function(__VA_ARGS__);

#define CHECK_RETURNED_FUNCTION(instance, function, type, fail_return, ...) \
loaderLayer* nextLayer = loaderGetNextLayer(instance); \
if (nextLayer->type.function == NULL) { \
    gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){ \
        .message = gnCreateString("Failed to load " #function " this indicates a bug within gryphn") \
    }); \
    resetLayer(instance); \
    return fail_return; \
} \
return nextLayer->type.function(__VA_ARGS__);

#define CHECK_VOID_FUNCTION(instance, function, type, ...) \
loaderLayer* nextLayer = loaderGetNextLayer(instance); \
if (nextLayer->type.function == NULL) { \
    gnDebuggerSetErrorMessage(instance->debugger, (gnMessageData){ \
        .message = gnCreateString("Failed to load " #function " this indicates a bug within gryphn") \
    }); \
    resetLayer(instance); \
    return; \
} \
nextLayer->type.function(__VA_ARGS__);
