#pragma once
#include "stdint.h"
#include "utils/gryphn_error_code.h"
#include "core/src/gryphn_handles.h"

gnReturnCode gnPresentationQueueGetImageAsync(gnPresentationQueueHandle presentationQueue, uint64_t timeout, gnSemaphoreHandle semaphore, uint32_t* imageIndex);
