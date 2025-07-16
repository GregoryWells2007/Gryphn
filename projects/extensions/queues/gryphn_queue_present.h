#pragma once
#include <extensions/synchronization/commands/gryphn_sync_present.h>
#include <core/src/present/gryphn_present.h>

gnReturnCode gnQueuePresent(gnDevice device, gnQueue queue, gnPresentInfo info);
gnReturnCode gnQueuePresentSync(gnDevice device, gnQueue queue, gnPresentSyncInfo info);
