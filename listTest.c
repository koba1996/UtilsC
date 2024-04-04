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

void testCopyList() {
    List* list = listCreate(sizeof(int));
    int arr[] = {1, 2, 3, 4};
    listAddMultiple(list, 4, arr);
    List* other = listcpy(list);
    // change the original array
    listSetElement(list, arr, 2);
    assert(*((int*) listGetElement(other, 0)) == 1);
    assert(*((int*) listGetElement(other, 1)) == 2);
    // the copy should not be affected by the change
    assert(*((int*) listGetElement(other, 2)) == 3);
    assert(*((int*) listGetElement(other, 3)) == 4);
    listFree(list);
    listFree(other);
    printf("Test#8 succeded\n");
}

void testCompareList() {
    List* listi = listCreate(sizeof(int));
    List* listc1 = listCreate(sizeof(char));
    List* listc2 = listCreate(sizeof(char));
    // lists with different types cannot be equal
    assert(!(listIsEqual(listi, listc1)));
    // empty lists with same type should be equal
    assert(listIsEqual(listc1, listc2));
    char c = 'a';
    listAddElement(listc1, &c);
    // lists with different length cannot be equal
    assert(!(listIsEqual(listc1, listc2)));
    c = 'b';
    listAddElement(listc2, &c);
    // lists with different values cannot be equal
    assert(!(listIsEqual(listc1, listc2)));
    // should synergize with listcpy
    assert(listIsEqual(listc1, listcpy(listc1)));
    listFree(listi);
    listFree(listc1);
    listFree(listc2);
    printf("Test#9 succeded\n");
}

void testConcatList() {
    List* listi = listCreate(sizeof(int));
    List* listc1 = listCreate(sizeof(char));
    List* listc2 = listCreate(sizeof(char));
    char arr[] = {'a', 'b'};
    int arri[] = {1, 2};
    listAddMultiple(listc1, 2, arr);
    listAddMultiple(listc2, 2, arr);
    listAddMultiple(listi, 2, arri);
    listcat(listc1, listc2);
    assert(*((char*) listGetElement(listc1, 0)) == 'a');
    assert(*((char*) listGetElement(listc1, 1)) == 'b');
    assert(*((char*) listGetElement(listc1, 2)) == 'a');
    assert(*((char*) listGetElement(listc1, 3)) == 'b');
    assert(listc1->elements == 4);
    assert(listc2->elements == 2);
    assert(!listcat(listc1, listi));
    assert(listc1->elements == 4);
    assert(listi->elements == 2);
    listFree(listi);
    listFree(listc1);
    listFree(listc2);
    printf("Test#10 succeded\n");
}

void testSortList() {
    List* list = listCreate(sizeof(int));
    int arr[] = {3, 2, 4, 1};
    listAddMultiple(list, 4, arr);
    listSort(list);
    assert(*((int*) listGetElement(list, 0)) == 1);
    assert(*((int*) listGetElement(list, 1)) == 2);
    assert(*((int*) listGetElement(list, 2)) == 3);
    assert(*((int*) listGetElement(list, 3)) == 4);
    listFree(list);
    printf("Test#11 succeded\n");
}

void testSortEmptyList() {
    List* list = listCreate(sizeof(int));
    int element = 5;
    listSort(list);
    assert(list->size == 0);
    listAddElement(list, &element);
    listSort(list);
    assert(*((int*) listGetElement(list, 0)) == 5);
    assert(list->size == 1);
    listFree(list);
    printf("Test#12 succeded\n");
}

void testFindLastElement() {
    List* list = listCreate(sizeof(double));
    double arr[] = {1.2, 3.4, 5.6, 3.4};
    double notElement = 7.8;
    listAddMultiple(list, 4, arr);
    int found = listFindLastElement(list, arr + 2);
    int findFirst = listFindLastElement(list, arr + 1);
    int notFound = listFindLastElement(list, &notElement);
    assert(found == 2);
    // should return the last occurence
    assert(findFirst == 3);
    // or -1 if it was not found
    assert(notFound == -1);
    listFree(list);
    printf("Test#13 succeded\n");
}

void testSetElementWithDefault() {
    List* list = listCreate(sizeof(char));
    char c = 'a';
    char def = '\000';
    listSetDefault(list, &def);
    listSetElement(list, &c, 100);
    for (int i = 0; i < 100; i++) {
        assert(*((char*) listGetElement(list, i)) == '\000');
    }
    assert(*((char*) listGetElement(list, 100)) == 'a');
    assert(list->size == 110);
    assert(list->elements == 101);
    listFree(list);
    printf("Test#14 succeded\n");
}

void testCreateWithStartSize() {
    char def = '\000';
    List* list = listCreateDefault(sizeof(char), &def, 100);
    for (int i = 0; i < 100; i++) {
        assert(*((char*) listGetElement(list, i)) == '\000');
    }
    assert(list->size == 100);
    assert(list->elements == 100);
    listFree(list);
    printf("Test#15 succeded\n");
}

void testGetSubList() {
    List* list = listCreate(sizeof(int));
    int nextNum;
    int *p = &nextNum;
    for (int i = 0; i < 100; i++) {
        *p = i * i;
        listAddElement(list, p);
    }
    assert(listSubList(list, -1, 5) == NULL);
    assert(listSubList(list, 1, 101) == NULL);
    assert(listSubList(list, 10, 5) == NULL);
    List* subList = listSubList(list, 5, 10);
    listSetElement(list, p, 7);
    assert(subList->elements == 5);
    assert(*((int*) listGetElement(subList, 0)) == 25);
    assert(*((int*) listGetElement(subList, 1)) == 36);
    assert(*((int*) listGetElement(subList, 2)) == 49);
    assert(*((int*) listGetElement(subList, 3)) == 64);
    assert(*((int*) listGetElement(subList, 4)) == 81);
    listFree(list);
    listFree(subList);
    printf("Test#16 succeded\n");
}

void testGetSubListFromBack() {
    List* list = listCreate(sizeof(int));
    int nextNum;
    int *p = &nextNum;
    for (int i = 0; i < 10; i++) {
        *p = i * i;
        listAddElement(list, p);
    }
    int l = listLength(list);
    List* subList = listSubList(list, l - 3, l);
    assert(*((int*) listGetElement(subList, 0)) == 49);
    assert(*((int*) listGetElement(subList, 1)) == 64);
    assert(*((int*) listGetElement(subList, 2)) == 81);
    listFree(list);
    listFree(subList);
    printf("Test#17 succeded\n");
}

void testReverseList() {
    List* list = listCreate(sizeof(int));
    int arr[5] = {1, 2, 3, 4, 5};
    listAddMultiple(list, 5, arr);
    listReverse(list);
    assert(list->elements == 5);
    assert(*((int*) listGetElement(list, 0)) == 5);
    assert(*((int*) listGetElement(list, 1)) == 4);
    assert(*((int*) listGetElement(list, 2)) == 3);
    assert(*((int*) listGetElement(list, 3)) == 2);
    assert(*((int*) listGetElement(list, 4)) == 1);
    listFree(list);
    printf("Test#18 succeded\n");
}

void runTests() {
    testCreateNewList();
    testCheckLengthOfNewList();
    testAddElement();
    testAddHundredElements();
    testAddMultipleElements();
    testFindElement();
    testCopyList();
    testCompareList();
    testConcatList();
    testSortList();
    testSortEmptyList();
    testFindLastElement();
    testSetElementWithDefault();
    testCreateWithStartSize();
    testGetSubList();
    testGetSubListFromBack();
    testReverseList();
}

void printIntList(List* list) {
    int length = listLength(list);
    printf("[");
    for (int i = 0; i < length; i++) {
        if (i != 0) {
            printf(", ");
        }
        printf("%d", *((int*) listGetElement(list, i)));
    }
    printf("]\n");
}

void example() {
    printf("Here you can type positive integer numbers, one after the other.\n");
    printf("If you wish to end it and evaluate your result, type 0.\n");
    int number;
    List* list = listCreate(sizeof(int));
    do {
        printf("Type a number! ");
        scanf("%d", &number);
        printf("\n");
        if (number < 0) {
            number *= -1;
        }
        if (number != 0) {
            listAddElement(list, &number);
        }
    } while (number);
    printf("Your numbers: ");
    printIntList(list);
    List* cpy = listcpy(list);
    listSort(cpy);
    printf("Your numbers in ascending order: ");
    printIntList(cpy);
    int l = listLength(cpy);
    List* slice = l > 3 ? listSubList(cpy, l - 3, l) : listcpy(cpy);
    listReverse(slice);
    printf("Your biggest numbers in descending order: ");
    printIntList(slice);
    listFree(list);
    listFree(cpy);
    listFree(slice);
}

int main() {
    runTests();
    // Uncomment the line below this for a fun little example
    // example();
}