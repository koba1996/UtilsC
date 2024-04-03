#include "List.h"
#include <assert.h>
#include <stdio.h>

// Sadly I cannot write actual unit tests in language C
// But a wise man once said: "There is no such thing as best practice. If it works, it works."

void testCreateNewList() {
    List* list = listCreate(sizeof(int));
    assert(list->size == 10);
    assert(list->elements == 0);
    assert(list->sizeOfElement == sizeof(int));
    listFree(list);
    printf("Test#1 succeded\n");
}

void testCheckLengthOfNewList() {
    List* list = listCreate(sizeof(int));
    assert(listLength(list) == 0);
    listFree(list);
    printf("Test#2 succeded\n");
}

void testAddElement() {
    List* list = listCreate(sizeof(int));
    int newElement = 5;
    listAddElement(list, &newElement);
    void* element = listGetElement(list, 0);
    assert(*((int*) element) == 5);
    assert(list->size == 10);
    assert(list->elements == 1);
    listFree(list);
    printf("Test#3 succeded\n");
}

void testAddHundredElements() {
    List* list = listCreate(sizeof(int));
    int element;
    for (int i = 0; i < 100; i++) {
        element = i * i;
        listAddElement(list, &element);
    }
    for (int i = 0; i < 100; i++) {
        assert(*((int*) listGetElement(list, i)) == i * i);
    }
    assert(list->size == 100);
    assert(list->elements == 100);
    listFree(list);
    printf("Test#4 succeded\n");
}

void testSetElement() {
    List* list = listCreate(sizeof(char));
    char c = 'a';
    listSetElement(list, &c, 100);
    assert(*((char*) listGetElement(list, 100)) == 'a');
    assert(list->size == 110);
    assert(list->elements == 101);
    listFree(list);
    printf("Test#5 succeded\n");
}

void testAddMultipleElements() {
    List* list = listCreate(sizeof(double));
    double arr[] = {1.2, 3.4, 5.6, 7.8};
    listAddMultiple(list, 4, arr);
    assert(*((double*) listGetElement(list, 0)) == 1.2);
    assert(*((double*) listGetElement(list, 1)) == 3.4);
    assert(*((double*) listGetElement(list, 2)) == 5.6);
    assert(*((double*) listGetElement(list, 3)) == 7.8);
    assert(list->size == 10);
    assert(list->elements == 4);
    listFree(list);
    printf("Test#6 succeded\n");
}

void testFindElement() {
    List* list = listCreate(sizeof(double));
    double arr[] = {1.2, 3.4, 5.6, 3.4};
    double notElement = 7.8;
    listAddMultiple(list, 4, arr);
    int found = listFindElement(list, arr + 2);
    int findFirst = listFindElement(list, arr + 1);
    int notFound = listFindElement(list, &notElement);
    assert(found == 2);
    // should return the first occurence
    assert(findFirst == 1);
    // or -1 if it was not found
    assert(notFound == -1);
    listFree(list);
    printf("Test#7 succeded\n");
}

int main() {
    testCreateNewList();
    testCheckLengthOfNewList();
    testAddElement();
    testAddHundredElements();
    testSetElement();
    testAddMultipleElements();
    testFindElement();
}