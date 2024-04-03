#include "List.h"
#include <stdlib.h>
#include <memory.h>

void* listReallocMemory(List* list, int extra) {
    int multiplier = extra / MINIMUM_ALLOCATION + (extra % MINIMUM_ALLOCATION != 0);
    list->data = realloc(list->data, (list->size + MINIMUM_ALLOCATION * multiplier) * list->sizeOfElement);
    if (!list->data) {
        free(list);
        return NULL;
    }
    list->size += MINIMUM_ALLOCATION * multiplier;
    return list->data;
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

List* listAddElement(List* list, void* element) {
    if (list->elements + 1 > list->size) {
        if (!(listReallocMemory(list, 1))) {
            return NULL;
        }
    }
    void* destination = list->data + list->elements * list->sizeOfElement;
    memcpy(destination, element, list->sizeOfElement);
    list->elements++;
    return list;
}

List* listAddMultiple(List* list, int count, void* elements) {
    if (list->elements + count > list->size) {
        if (!(listReallocMemory(list, count))) {
            return NULL;
        }
    }
    for(int i = 0; i < count; i++)
    {
        listAddElement(list, elements + i * list->sizeOfElement);
    }
    return list;
}

List* listSetElement(List* list, void* element, int index) {
    if (list->size <= index) {
        if (!(listReallocMemory(list, index + 1 - list->size))) {
            return NULL;
        }
    }
    list->elements = index;
    listAddElement(list, element);
    return list;
}

void* listGetElement(List* list, int index) {
    if (list->elements <= index) {
        return NULL;
    }
    void* destination = list->data + index * list->sizeOfElement;
    return destination;
}

int listFindElement(List* list, void* element) {
    for (int i = 0; i < list->elements; i++) {
        if (memcmp(list->data + list->sizeOfElement * i, element, list->sizeOfElement) == 0) {
            return i;
        }
    }
    return -1;
}

void listFree(List* list) {
    free(list->data);
    free(list);
}