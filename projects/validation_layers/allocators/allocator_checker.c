#include "allocator_checker.h"
#include <core/src/gryphn_handles.h>
#include "core/src/instance/gryphn_debugger.h"
#include <stdio.h>
#include <stdlib.h>

void* gnMallocFunc (size_t size, void* userData) {
    char outBuffer[500];
    snprintf(outBuffer, sizeof(outBuffer), "Allocating %lu bytes with malloc", size);

    gnDebuggerSetVerboseMessage(userData, (gnMessageData) {
        .message = gnCreateString(outBuffer)
    });
    return malloc(size);
}
void* gnCallocFunc (int cnt, size_t size, void* userData) {
    char outBuffer[500];
    snprintf(outBuffer, sizeof(outBuffer), "Allocating %i items of %lu bytes with calloc", cnt, size);
    gnDebuggerSetVerboseMessage(userData, (gnMessageData){
        .message = gnCreateString(outBuffer)
    });
    return calloc(cnt, size);
}
void* gnReallocFunc (void* ptr, size_t size, void* userData) {
    char outBuffer[500];
    snprintf(outBuffer, sizeof(outBuffer), "Reallocating %p with new size %lu", ptr, size);
    gnDebuggerSetVerboseMessage(userData, (gnMessageData){
        .message = gnCreateString(outBuffer)
    });
    return realloc(ptr, size);
}
void gnFreeFunc (void* ptr, void* userData) {
    char outBuffer[500];
    snprintf(outBuffer, sizeof(outBuffer), "Freeing %p", ptr);
    gnDebuggerSetVerboseMessage(userData, (gnMessageData){
        .message = gnCreateString(outBuffer)
    });
    free(ptr);
}
