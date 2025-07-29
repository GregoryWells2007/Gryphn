#pragma once
#include "stdint.h"
#include "core/gryphn_return_code.h"
#include "core/src/gryphn_handles.h"

gnReturnCode gnPresentationQueueGetImageAsync(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphoreHandle semaphore, uint32_t* imageIndex);
