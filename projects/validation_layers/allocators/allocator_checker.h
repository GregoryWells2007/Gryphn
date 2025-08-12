#pragma once
#include <stddef.h>

void* gnMallocFunc (size_t size, void* userData);
void* gnCallocFunc (int cnt, size_t size, void* userData);
void* gnReallocFunc (void* ptr, size_t size, void* userData);
void  gnFreeFunc (void* ptr, void* userData);
