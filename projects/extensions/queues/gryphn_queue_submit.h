#pragma once
#include <extensions/synchronization/commands/gryphn_sync_submit.h>
#include <core/src/submit/gryphn_submit.h>

gnReturnCode gnQueueSubmit(gnOutputDevice device, gnQueue queue, gnSubmitInfo info);
gnReturnCode gnQueueSubmitSync(gnOutputDevice device, gnQueue queue, gnSubmitSyncInfo info);
