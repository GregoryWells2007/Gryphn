#include "submit/gryphn_submit.h"
#include "sync/semaphore/metal_semaphore.h"
#include "commands/command_buffer/metal_command_buffer.h"
#include "debugger/gryphn_debugger.h"
#include "commands/command_pool/metal_command_pool.h"
#include "synchronization/commands/gryphn_sync_submit.h"

gnReturnCode metalSyncSubmit(gnOutputDevice device, gnSubmitSyncInfo info);
gnReturnCode metalSubmit(gnOutputDevice device, gnSubmitInfo info);
