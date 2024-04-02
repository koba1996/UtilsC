#include "List.h"
#include <stdlib.h>

List* listCreate(size_t sizeOfElement) {
    List* newList = (List*) calloc(1, sizeof(List));
    newList->size = 0;
    newList->sizeOfElement = sizeOfElement;
    newList->data = calloc(MINIMUM_ALLOCATION, sizeOfElement);
}

int listSize(List* list) {
    return list->size;
}