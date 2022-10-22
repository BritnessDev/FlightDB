// Interface to the Tree ADT

#ifndef TREE_H
#define TREE_H

#include "List.h"
#include "Record.h"

typedef struct tree *Tree;

////////////////////////////////////////////////////////////////////////
// Provided functions

/**
 * Creates a new tree that will use the given comparison function
 */
Tree TreeNew(int (*compare)(Record, Record));

/**
 * Frees the given tree. If freeRecords is true, also frees the records.
 */
void TreeFree(Tree t, bool freeRecords);

////////////////////////////////////////////////////////////////////////
// Functions you need to implement

/**
 * Inserts a record into the tree.
 * Returns true if the record was inserted into the tree, and false if
 * the tree already contains a record that compares equal to the given
 * record.
 * The time complexity of this function must be O(log n).
 */
bool TreeInsert(Tree t, Record rec);

/**
 * Searches the tree for a record that compares equal to the given
 * record. Returns the record if it exists, and NULL otherwise.
 * The time complexity of this function must be O(log n).
 */
Record TreeSearch(Tree t, Record rec);

/**
 * Searches for all records between the two given records (inclusive)
 * and returns the records in a list in ascending order. Returns an
 * empty list if there are no such records.
 * The time complexity of this function must be O(m + log n), where m is
 * the length of the returned list.
 */
List TreeSearchBetween(Tree t, Record lower, Record upper);

/**
 * Returns the smallest record greater than or equal to the given record,
 * or NULL if there is no such record.
 * The time complexity of this function must be O(log n).
 */
Record TreeNext(Tree t, Record rec);


////////////////////////////////////////////////////////////////////////

#endif

