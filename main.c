#include "List.h"
#include <assert.h>

// Sadly I cannot write actual unit tests in language C
// But a wise man once said: "There is no such thing as best practice. If it works, it works."

void testCreateNewList() {
    List* list = listCreate(sizeof(int));
    assert(list->size == 0);
    assert(list->sizeOfElement == sizeof(int));
}

void testCheckLengthOfNewList() {
    List* list = listCreate(sizeof(int));
    assert(listSize(list) == 0);
}

int main() {
    testCreateNewList();
    testCheckLengthOfNewList();
}