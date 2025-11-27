#ifndef CDOUBLYLINKEDLIST_LIBRARY_H
#define CDOUBLYLINKEDLIST_LIBRARY_H

#include <limits.h>

/*
 * Define a doubly-linked list of heap-allocated strings.
 * Write functions to insert, find, and delete items from it.
 * Test them.
*/

typedef struct Node {
    struct Node *next;
    struct Node *prev;
    char *data;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
    size_t len;
} List;


typedef enum Error {
    SUCCESS = 0,
    NO_RESULT = -1,
    NOT_A_LIST = -2,
    NULL_WHILE_ITERATING = -3,
    HUGE_STRING = -4,
    NO_VALID_SEARCH_TERM = -5,
    ALLOC_FAILED = -6,
    EMPTY_LIST = -7,
    OUTPUT_INVALID = -8,
    INVALID_POSITION = -9,
    NO_STRING_PROVIDED = -10,
} Error;

typedef enum Position {
    AFTER,
    BEFORE,
} Position;

Error new_list(List **out);
Error new_node(const char *string, Node **out);
Error insert(List *l, Node *node, Node *new_node, Position position);
inline Error insert_after(List *l, Node *node, Node *new_node) {return insert(l, node, new_node, AFTER);}
inline Error insert_before(List *l, Node *node, Node *new_node) {return insert(l, node, new_node, BEFORE);}
inline Error insert_end(List *l, Node *new_node) {return insert(l, l->tail, new_node, AFTER);}
inline Error insert_beginning(List *l, Node *new_node) {return insert(l, l->head, new_node, BEFORE);}
Error remove_node(List *l, Node *node);
Error find(const List *l, const char *string, Node **out);
Error delete_list(List *l);

/*
Error new(List **out);
// int init(List *out, size_t maxlen);
int append(List *l, const char *x);
int append_left(List *l, const char *x);
int clear(List *l);
int contains(List *l, const char *item);
// int copy(List *l, List *out);
ssize_t count(List *l, const char *x);
int getitem(List *l, ssize_t index, const char **out);
ssize_t index(List *l, const char *x);
ssize_t index_bounded(List *l, const char *x, ssize_t start, ssize_t stop);
int insert(List *l, ssize_t i, const char *x);
ssize_t len(List *l);
int pop(List *l, const char **out);
int pop_left(List *l, const char **out);
int remove(List *l, const char *x);
// int reverse(List *l);
int rotate(List *l, ssize_t n);
*/

#endif //CDOUBLYLINKEDLIST_LIBRARY_H
