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
void listAddElement(List* list, void* element);
void* listGetElement(List* list, int index);
void listFree(List* list);
void listSetElement(List* list, void* element, int index);

#endif