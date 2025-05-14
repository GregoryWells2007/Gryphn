#pragma once
#include "stdlib.h"

typedef struct gnCList {
    int count;
    int maxCount;
    void* data;
} gnCList;

const int GROWTH_RATE = 2; // i heard somewhere that 1.5 is better but imma use 2 because I also heard that its better somewhere else

inline gnCList gnCreateCList(int count) {
    gnCList newList;

    if (count == 0) {

    } else {
        newList.count = count;
        newList.maxCount = count;
        newList.data = malloc(sizeof(void*) * count);
    }

    return newList;
}

inline void gnCListResize(gnCList* cList, int count) {
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

inline void gnCListReserve(gnCList* cList, int count) {
    while (cList->count > cList->maxCount) {
        int oldMaxCount = cList->maxCount;
        cList->maxCount *= GROWTH_RATE;
        if (cList->count == oldMaxCount) {
            cList->maxCount += 1;
        }
    }

    cList->data = realloc(cList->data, cList->maxCount);
}
