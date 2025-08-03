#pragma once

#define gryphnFunctionLayer(function) typedef struct function##_layer { \
function func;\
struct function##_layer* next; \
} function##_layer;\
