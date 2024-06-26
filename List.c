#include "List.h"
#include <stdlib.h>
#include <memory.h>

int getBuffer(int spaceNeeded) {
    return (spaceNeeded / MINIMUM_ALLOCATION + (spaceNeeded % MINIMUM_ALLOCATION != 0)) * MINIMUM_ALLOCATION;
}

void* mergeSort(void* data, int length, size_t size) {
    if (length < 2) {
        return data;
    }
    int firstLength = length / 2;
    int secondLength = length - firstLength;
    void* firstHalf = firstLength > 1 ? mergeSort(data, firstLength, size) : data;
    void* secondHalf = secondLength > 1 
        ? mergeSort(data + firstLength * size, secondLength, size) 
        : data + firstLength * size;
    void* sorted = malloc(length * size);
    int p1 = 0, p2 = 0;
    void *destination, *source;
    for (int i = 0; i < length; i++) {
        destination = sorted + i * size;
        if (p1 == firstLength) {
            source = secondHalf + p2 * size;
            p2++;
        } else if (p2 == secondLength) {
            source = firstHalf + p1 * size;
            p1++;
        } else if (memcmp(firstHalf + p1 * size, secondHalf + p2 * size, size) < 0) {
            source = firstHalf + p1 * size;
            p1++;
        } else {
            source = secondHalf + p2 * size;
            p2++;
        }
        memcpy(destination, source, size);
    }
    if (firstLength > 1) {
        free(firstHalf);
    }
    if (secondLength > 1) {
        free(secondHalf);
    }
    return sorted;
}

void* getDataAt(List* list, int index) {
    return list->data + index * list->sizeOfElement;
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

void* listSetDefault(List* list, void* defaultValue) {
    list->defaultElement = malloc(list->sizeOfElement);
    if (list->defaultElement) {
        memcpy(list->defaultElement, defaultValue, list->sizeOfElement);
    }
    return list->defaultElement;
}

List* listCreateWithSize(size_t sizeOfElement, int numberOfElements, void* defaultElement) {
    int buffer = getBuffer(numberOfElements);
    List* newList = (List*) calloc(1, sizeof(List));
    if (newList) {
        newList->sizeOfElement = sizeOfElement;
        newList->data = malloc(buffer * sizeOfElement);
        newList->size = buffer;
        newList->elements = 0;
        if (defaultElement) {
            if (!(listSetDefault(newList, defaultElement))) {
                listFree(newList);
            }
        } else {
            newList->defaultElement = NULL;
        }
        
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
        newList->defaultElement = NULL;
    }
    return newList;
}

List* listCreateDefault(size_t sizeOfElement, void* defaultValue, int startSize) {
    List* newList = listCreateWithSize(sizeOfElement, startSize, defaultValue);
    if (newList) {
        for (; newList->elements < startSize;) {
            listAddElement(newList, newList->defaultElement);
        }
    }
    return newList;
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
    if (list->defaultElement) {
        for (; list->elements < index; list->elements++) {
            memcpy(getDataAt(list, list->elements), list->defaultElement, list->sizeOfElement);
        }
    } else {
        list->elements = index;
    }
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

int listFindLastElement(List* list, void* element) {
    for (int i = list->elements - 1; i >= 0; i--) {
        if (memcmp(getDataAt(list, i), element, list->sizeOfElement) == 0) {
            return i;
        }
    }
    return -1;
}

List* listcpy(List* list) {
    return listSubList(list, 0, list->elements);
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

void listSort(List* list) {
    void* old = list->data;
    list->data = mergeSort(list->data, list->elements, list->sizeOfElement);
    if (old != list->data) {
        free(old);
    }
    // we are allocating the exact amount of memory during sorting and lose any buffer we have
    list->size = list->elements;
}

List* listSubList(List* list, int start, int end) {
    if (start < 0 || end > list->elements || start > end) {
        return NULL;
    }
    List* newList = listCreateWithSize(list->sizeOfElement, end - start, list->defaultElement);
    if (newList) {
        for (int i = start; i < end; i++) {
            listAddElement(newList, getDataAt(list, i));
        }
    }
    return newList;
}

void listReverse(List* list) {
    void* tmp;
    for (int i = 0; i < list->elements / 2; i++) {
        memcpy(tmp, getDataAt(list, i), list->sizeOfElement);
        memcpy(getDataAt(list, i), getDataAt(list, list->elements - 1 - i), list->sizeOfElement);
        memcpy(getDataAt(list, list->elements - 1 - i), tmp, list->sizeOfElement);
    }
}

void listFree(List* list) {
    free(list->data);
    if (list->defaultElement) {
        free(list->defaultElement);
    }
    free(list);
}