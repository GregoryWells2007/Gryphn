#include "gryphn_command_submit.h"

void gnCommandSubmitDataSetWaitSemaphore(gnCommandSubmitData& data, gnSyncSemaphore& semaphore) {
    data.waitSemaphore = &semaphore;
}
void gnCommandSubmitDataSetCommandBuffer(gnCommandSubmitData& data, gnCommandBuffer& commandBuffer) {
    data.commandBuffer = &commandBuffer;
}
void gnCommandSubmitDataSetSignalSemaphore(gnCommandSubmitData& data, gnSyncSemaphore& semaphore) {
    data.signalSemaphore = &semaphore;
}
