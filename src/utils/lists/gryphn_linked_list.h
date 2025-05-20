#pragma once
#include "stdlib.h"

// why would one use a linked list
typedef struct gnLinkedList {
    void* data;
    gnLinkedList* nextNode;
} gnLinkedList;

static gnLinkedList gnCreateLinkedList(int count) {
    gnLinkedList list;

    gnLinkedList* currentNode = &list;
    for (int i = 0; i < count; i++) {
        if ((i + 1) < count) {
            currentNode->nextNode = (gnLinkedList*)malloc(sizeof(gnLinkedList));
            currentNode = currentNode->nextNode;
        }
    }

    return list;
}
