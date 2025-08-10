#pragma once
#include <stdlib.h>

typedef void* (*PFN_gnMalloc)   (size_t size, void* userData);
typedef void* (*PFN_gnCalloc)   (int cnt, size_t size, void* userData);
typedef void* (*PFN_gnRealloc)  (void* ptr, size_t size, void* userData);
typedef void  (*PFN_gnFree)     (void* ptr, void* userData);

typedef struct gnAllocators {
    void* userData;
    PFN_gnMalloc  malloc;
    PFN_gnCalloc  calloc;
    PFN_gnRealloc realloc;
    PFN_gnFree    free;
} gnAllocators;

#define gnMalloc(allocators, size) allocators->malloc(size, allocators->userData)
