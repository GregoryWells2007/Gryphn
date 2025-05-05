#include <gryphn/gryphn_utils.h>
#include "core/sync_objects/gryphn_sync_semaphore.h"
#include "core/presentation_queue/gryphn_presentation_queue.h"
#include "core/presentation_queue/gryphn_present_queue_state.h"

struct gnPlatformCommandPresentData;
struct gnCommandBuffer;

struct gnCommandPresentData {
ACCESS_LEVEL:
    gnPlatformCommandPresentData* commandPresentData = nullptr;

    gnSyncSemaphore* semaphore;
    gnPresentationQueue* presentationQueue;
    gnUInt* imageIndex;
public:
    gnCommandPresentData() {}
};

void gnCommandPresentDataSetSignalSemaphore(gnCommandPresentData& presentCommandData, gnSyncSemaphore& semaphore);
void gnCommandPresentDataSetPresentationQueue(gnCommandPresentData& presentCommandData, gnPresentationQueue& presentationQueue);
void gnCommandPresentDataSetImageIndex(gnCommandPresentData& presentCommandData, gnUInt* imageIndex);

inline gnPresentationQueueState (*gnCommandPresentGetValidPresentationQueue)(gnCommandPresentData& presentCommandData);
inline gnReturnCode (*gnCommandPresent)(gnCommandPresentData& presentCommandData);
