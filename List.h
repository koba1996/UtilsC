#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

int MINIMUM_ALLOCATION = 10;

typedef struct list
{
    void *data;
    int size;
    size_t sizeOfElement;
} List;

List* listCreate(size_t sizeOfElement);
int listSize(List* list);

#endif