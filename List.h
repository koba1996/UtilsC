#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

#define MINIMUM_ALLOCATION 10

typedef struct list
{
    void *data;
    void *defaultElement;
    int size;
    int elements;
    size_t sizeOfElement;
} List;

List* listCreate(size_t sizeOfElement);
List* listCreateDefault(size_t sizeOfElement, void* defaultValue, int startSize);
int listLength(List* list);
void* listSetDefault(List* list, void* defaultValue);
List* listAddElement(List* list, void* element);
List* listAddMultiple(List* list, int count, void* elements);
void* listGetElement(List* list, int index);
List* listSetElement(List* list, void* element, int index);
int listFindElement(List* list, void* element);
int listFindLastElement(List* list, void* element);
List* listcpy(List* list);
int listIsEqual(List* first, List* second);
List* listcat(List* head, List* tail);
void listSort(List* list);
List* listSubList(List* list, int start, int end);
void listReverse(List* list);
void listFree(List* list);

#endif