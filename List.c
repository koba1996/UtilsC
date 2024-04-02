#include "List.h"
#include <stdlib.h>
#include <memory.h>

void listReallocMemory(List* list, int extra) {
    int multiplier = extra / MINIMUM_ALLOCATION + (extra % MINIMUM_ALLOCATION != 0);
    list->data = realloc(list->data, (list->size + MINIMUM_ALLOCATION * multiplier) * list->sizeOfElement);
    list->size += MINIMUM_ALLOCATION * multiplier;
}

List* listCreate(size_t sizeOfElement) {
    List* newList = (List*) calloc(1, sizeof(List));
    newList->sizeOfElement = sizeOfElement;
    newList->data = calloc(MINIMUM_ALLOCATION, sizeOfElement);
    newList->size = 10;
    newList->elements = 0;
}

int listLength(List* list) {
    return list->elements;
}

void listAddElement(List* list, void* element) {
    if (list->elements + 1 > list->size) {
        listReallocMemory(list, 1);
    }
    void* destination = list->data + list->elements * list->sizeOfElement;
    memcpy(destination, element, list->sizeOfElement);
    list->elements++;
}

void listSetElement(List* list, void* element, int index) {
    if (list->size <= index) {
        listReallocMemory(list, index + 1 - list->size);
    }
    list->elements = index;
    listAddElement(list, element);
}

void* listGetElement(List* list, int index) {
    if (list->elements <= index) {
        return NULL;
    }
    void* destination = list->data + index * list->sizeOfElement;
    return destination;
}

void listFree(List* list) {
    free(list->data);
    free(list);
}