// Implementation of the List ADT

// !!! DO NOT MODIFY THIS FILE !!!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "Record.h"

#define DEFAULT_CAPACITY 64

struct list {
    Record *items;
    int     size;
    int     capacity;
};

////////////////////////////////////////////////////////////////////////

// Creates a new empty list
List ListNew(void) {
    List l = malloc(sizeof(*l));
    if (l == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }

    l->size = 0;
    l->capacity = DEFAULT_CAPACITY;
    l->items = malloc(l->capacity * sizeof(Record));
    return l;
}

// Frees the given list, but not the records contained in the list
void ListFree(List l) {
    free(l->items);
    free(l);
}

// Returns the number of items in the list
int ListSize(List l) {
    return l->size;
}

// Adds a record to the end of the list. Does NOT make a copy of the
// record before adding it to the list.
void ListAppend(List l, Record r) {
    if (l->size == l->capacity) {
        l->items = realloc(l->items, 2 * l->capacity * sizeof(Record));
        l->capacity *= 2;
    }
    l->items[l->size++] = r;
}

// Extends the list `l` with the records from the list `add`.
void ListExtend(List l, List add) {
    for (int i = 0; i < add->size; i++) {
        ListAppend(l, add->items[i]);
    }
}

////////////////////////////////////////////////////////////////////////

struct listIterator {
    int  curr;
    List list;
};

// Creates an iterator for the given list
ListIterator ListItNew(List l) {
    ListIterator it = malloc(sizeof(*it));
    if (it == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }

    it->curr = 0;
    it->list = l;
    return it;
}

// Gets the next item in the list. The item should not be modified.
Record ListItNext(ListIterator it) {
    if (it->curr == it->list->size) {
        fprintf(stderr, "No more items in iterator!\n");
        exit(EXIT_FAILURE);
    }

    Record item = it->list->items[it->curr];
    it->curr++;
    return item;
}

// Checks if the list has a next item
bool ListItHasNext(ListIterator it) {
    return it->curr < it->list->size;
}

// Frees the given iterator
void ListItFree(ListIterator it) {
    free(it);
}

////////////////////////////////////////////////////////////////////////
