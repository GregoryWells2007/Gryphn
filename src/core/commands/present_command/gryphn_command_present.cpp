#include "gryphn_command_present.h"

void gnCommandPresentDataSetSignalSemaphore(gnCommandPresentData& presentCommandData, gnSyncSemaphore& semaphore) {
    presentCommandData.semaphore = &semaphore;
}
void gnCommandPresentDataSetPresentationQueue(gnCommandPresentData& presentCommandData, gnPresentationQueue& presentationQueue) {
    presentCommandData.presentationQueue = &presentationQueue;
}
void gnCommandPresentDataSetImageIndex(gnCommandPresentData& presentCommandData, gnUInt* imageIndex) {
    presentCommandData.imageIndex = imageIndex;
}
