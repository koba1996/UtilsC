#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

#define MINIMUM_ALLOCATION 10

typedef struct list
{
    void *data;
    int size;
    int elements;
    size_t sizeOfElement;
} List;

List* listCreate(size_t sizeOfElement);
int listLength(List* list);
List* listAddElement(List* list, void* element);
List* listAddMultiple(List* list, int count, void* elements);
void* listGetElement(List* list, int index);
List* listSetElement(List* list, void* element, int index);
int listFindElement(List* list, void* element);
void listFree(List* list);

#endif