#include "List.h"
#include <stdlib.h>
#include <memory.h>

int getBuffer(int spaceNeeded) {
    return (spaceNeeded / MINIMUM_ALLOCATION + (spaceNeeded % MINIMUM_ALLOCATION != 0)) * MINIMUM_ALLOCATION;
}

void* listReallocMemory(List* list, int newSize) {
    int buffer = getBuffer(newSize);
    list->data = realloc(list->data, buffer * list->sizeOfElement);
    if (!list->data) {
        free(list);
        return NULL;
    }
    list->size = buffer;
    return list->data;
}

List* listCreateWithSize(size_t sizeOfElement, int numberOfElements) {
    int buffer = getBuffer(numberOfElements);
    List* newList = (List*) calloc(1, sizeof(List));
    if (newList) {
        newList->sizeOfElement = sizeOfElement;
        newList->data = malloc(buffer * sizeOfElement);
        newList->size = buffer;
        newList->elements = 0;
    }
    return newList;
}

List* listCreate(size_t sizeOfElement) {
    List* newList = (List*) calloc(1, sizeof(List));
    if (newList) {
        newList->sizeOfElement = sizeOfElement;
        newList->data = malloc(MINIMUM_ALLOCATION * sizeOfElement);
        newList->size = MINIMUM_ALLOCATION;
        newList->elements = 0;
    }
    return newList;
}

void* getDataAt(List* list, int index) {
    return list->data + index * list->sizeOfElement;
}

int listLength(List* list) {
    return list->elements;
}

List* listAddElement(List* list, void* element) {
    if (list->elements + 1 > list->size) {
        if (!(listReallocMemory(list, list->elements + 1))) {
            return NULL;
        }
    }
    void* destination = getDataAt(list, list->elements);
    memcpy(destination, element, list->sizeOfElement);
    list->elements++;
    return list;
}

List* listAddMultiple(List* list, int count, void* elements) {
    if (list->elements + count > list->size) {
        if (!(listReallocMemory(list, list->elements + count))) {
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
        if (!(listReallocMemory(list, index + 1))) {
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
    void* destination = getDataAt(list, index);
    return destination;
}

int listFindElement(List* list, void* element) {
    for (int i = 0; i < list->elements; i++) {
        if (memcmp(getDataAt(list, i), element, list->sizeOfElement) == 0) {
            return i;
        }
    }
    return -1;
}

List* listcpy(List* list) {
    List* newList = listCreateWithSize(list->sizeOfElement, list->elements);
    if (newList) {
        for (int i = 0; i < list->elements; i++) {
            listAddElement(newList, getDataAt(list, i));
        }
    }
    return newList;
}

int listIsEqual(List* first, List* second) {
    if (first->sizeOfElement != second->sizeOfElement || first->elements != second->elements) {
        return 0;
    }
    size_t soe = first->sizeOfElement;
    int elements = first->elements;
    for (int i = 0; i < elements; i++) {
        if (memcmp(getDataAt(first, i), getDataAt(second, i), soe) != 0) {
            return 0;
        }
    }
    return 1;
}

List* listcat(List* head, List* tail) {
    if (head->sizeOfElement != tail->sizeOfElement) {
        return NULL;
    }
    if (head->elements + tail->elements > head->size) {
        if (!listReallocMemory(head, head->elements + tail->elements)) {
            return NULL;
        }
    }
    for (int i = 0; i < tail->elements; i++) {
        listAddElement(head, getDataAt(tail, i));
    }
    return head;
}

// TODOs
// Sort
// rfind?

void listFree(List* list) {
    free(list->data);
    free(list);
}