// Implementation of the Tree ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Record.h"
#include "Tree.h"

typedef struct node *Node;
struct node {
    Record rec;
    Node   left;
    Node   right;

    // IMPORTANT: Do not modify the fields above
    // You may add additional fields below if necessary

};

struct tree {
    Node root;
    int (*compare)(Record, Record);

    // IMPORTANT: Do not modify the fields above
    // You may add additional fields below if necessary

    int size;

};



static void doTreeFree(Node n, bool freeRecords);
static Record doTreeSearch(Node curr, Record rec, Tree t);



////////////////////////////////////////////////////////////////////////
// Provided functions
// !!! DO NOT MODIFY THESE FUNCTIONS !!!

Tree TreeNew(int (*compare)(Record, Record)) {
    Tree t = malloc(sizeof(*t));
    if (t == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    t->root = NULL;
    t->compare = compare;
    return t;
}

void TreeFree(Tree t, bool freeRecords) {
    doTreeFree(t->root, freeRecords);
    free(t);
}

static void doTreeFree(Node n, bool freeRecords) {
    if (n != NULL) {
        doTreeFree(n->left, freeRecords);
        doTreeFree(n->right, freeRecords);
        if (freeRecords) {
            RecordFree(n->rec);
        }
        free(n);
    }
}

////////////////////////////////////////////////////////////////////////
// Functions you need to implement

bool TreeInsert(Tree t, Record rec) {
    // Insert into tree t the record rec
    // Return true if the record was inserted, false if it was already
    // present in the tree

    // check if the tree is empty
    if (t->root == NULL) {
        Node new = malloc(sizeof(*new));
        if (new == NULL) {
            fprintf(stderr, "error: out of memory\n");
            exit(EXIT_FAILURE);
        }
        new->rec = rec;
        new->left = NULL;
        new->right = NULL;
        t->root = new;
        t->size = 1;
        return true;
    }

    // if the tree is not empty, insert into the tree to create a BALANCED tree
    // return true if inserted, false if already present
    Node curr = t->root;
    while (curr != NULL) {
        // if the record is already present, return false
        if (t->compare(rec, curr->rec) == 0) {
            return false;
        }
        // if the record is less than the current node, go left
        if (t->compare(rec, curr->rec) < 0) {
            // if the left node is empty, insert the record
            if (curr->left == NULL) {
                Node new = malloc(sizeof(*new));
                if (new == NULL) {
                    fprintf(stderr, "error: out of memory\n");
                    exit(EXIT_FAILURE);
                }
                new->rec = rec;
                new->left = NULL;
                new->right = NULL;
                curr->left = new;
                t->size++;
                return true;
            }
            // if the left node is not empty, go left
            curr = curr->left;
        }
        // if the record is greater than the current node, go right
        if (t->compare(rec, curr->rec) > 0) {
            // if the right node is empty, insert the record
            if (curr->right == NULL) {
                Node new = malloc(sizeof(*new)); // create a new node
                if (new == NULL) {
                    fprintf(stderr, "error: out of memory\n"); // out of memory
                    exit(EXIT_FAILURE);
                }
                new->rec = rec; // insert the record
                new->left = NULL; // set the left node to NULL
                new->right = NULL; // set the right node to NULL
                curr->right = new; // set the right node to the new node
                t->size++; // increment the size of the tree
                return true; // return true
            }
            // if the right node is not empty, go right
            curr = curr->right; // go right
        }
    }



    return false;


}



Record TreeSearch(Tree t, Record rec) {
    // "Searches the tree for a record that compares equal to the given record. 
    //Returns the record if it exists, and NULL otherwise"
    // prevent memory leaks
    return doTreeSearch(t->root, rec, t);
}

List TreeSearchBetween(Tree t, Record lower, Record upper) {
    // Searches the tree for all records greater than lower (inclusive) and smaller than upper (inclusive) 
    // and returns the records in a list in ascending order. Returns an empty list if there are no such records. 
    // The list must be freed by the caller.

    // if the tree is empty, return an empty list
    if (t->root == NULL) {
        return ListNew();
    }

    // if the tree is not empty, search for the records
    List list = ListNew();
    Node curr = t->root;
    while (curr != NULL) {
        // if the current node is greater than the lower bound and less than the upper bound, add it to the list
        if (t->compare(curr->rec, lower) >= 0 && t->compare(curr->rec, upper) <= 0) {
            // insert the record into the list, use ListAppend
            ListAppend(list, curr->rec);

        }
        // if the current node is less than the lower bound, go right
        if (t->compare(curr->rec, lower) < 0) {
            curr = curr->right; // go right
        }
        // if the current node is greater than the upper bound, go left
        if (t->compare(curr->rec, upper) > 0) {
            curr = curr->left; // go left
        }
    }

    return list;
}



Record TreeNext(Tree t, Record rec) {
    // Searches the tree for a record for the next record
    // Returns the next record if it exists, and NULL otherwise

    // if the tree is empty, return NULL
    if (t->root == NULL) {
        return NULL;
    }

    // if the tree is not empty, search for the next record
    

    // set the root to the given rec and the next record to NULL
    Node curr = t->root;
    Node next = NULL;

    // while the current node is not NULL
    while (curr != NULL) {
        // if the current node is greater than the given record, set the next record to the current node
        if (t->compare(curr->rec, rec) > 0) {
            next = curr;
            curr = curr->left;
        }
        // if the current node is less than the given record, go right
        else if (t->compare(curr->rec, rec) < 0) {
            curr = curr->right;
        }
        // if the current node is equal to the given record, go right
        else if (t->compare(curr->rec, rec) == 0) {
            curr = curr->right;
        }
    }

    // if the next record is NULL, return NULL
    if (next == NULL) {
        return NULL;
    }

    // return the next record
    return next->rec;

}



static Record doTreeSearch(Node curr, Record rec, Tree t) {
    // prevent memory leaks
    if (curr == NULL) {
        return NULL;
    }
    // if the current node is equal to the given record, return the record
    if (t->compare(curr->rec, rec) == 0) {
        return curr->rec;
    }
    // if the current node is less than the given record, go right
    if (t->compare(curr->rec, rec) < 0) {
        return doTreeSearch(curr->right, rec, t);
    }
    // if the current node is greater than the given record, go left
    if (t->compare(curr->rec, rec) > 0) {
        return doTreeSearch(curr->left, rec, t);
    }
    return NULL;
}



////////////////////////////////////////////////////////////////////////
