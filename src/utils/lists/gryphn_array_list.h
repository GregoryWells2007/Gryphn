#pragma once
#include "stdlib.h"

typedef struct gnArrayList {
    int count;
    int maxCount;
    void* data;
} gnArrayList;

const int GROWTH_RATE = 2; // i heard somewhere that 1.5 is better but imma use 2 because I also heard that its better somewhere else

inline gnArrayList gnCreateArrayList(int count) {
    gnArrayList newList;

    if (count == 0) {

    } else {
        newList.count = count;
        newList.maxCount = count;
        newList.data = malloc(sizeof(void*) * count);
    }

    return newList;
}

inline void gnArrayListResize(gnArrayList* cList, int count) {
    cList->count = count;
    while (cList->count > cList->maxCount) {
        int oldMaxCount = cList->maxCount;
        cList->maxCount *= GROWTH_RATE;
        if (cList->count == oldMaxCount) {
            cList->maxCount += 1;
        }
    }

    cList->data = realloc(cList->data, cList->maxCount);
}

inline void gnArrayListReserve(gnArrayList* cList, int count) {
    while (cList->count > cList->maxCount) {
        int oldMaxCount = cList->maxCount;
        cList->maxCount *= GROWTH_RATE;
        if (cList->count == oldMaxCount) {
            cList->maxCount += 1;
        }
    }

    cList->data = realloc(cList->data, cList->maxCount);
}
