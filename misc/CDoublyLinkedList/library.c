#include "library.h"

#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>


#define ALLOC_STRUCT(TypeName)               \
    void *result = malloc(sizeof(TypeName)); \
    if (result == nullptr) {                 \
        return ALLOC_FAILED;                 \
    }                                        \
    new_struct = (TypeName *)result;

#define ALLOC_NODE(ptr)            \
    Error err;                     \
    if ((err = alloc(&l->head))) { \
        free(l->head);             \
        return err;                \
    }

#define CHECK_LIST_NONNULL(l) \
    if (l == nullptr) {       \
        return NOT_A_LIST;    \
    }

#define CHECK_LIST_NONEMPTY(l) \
    if (!l->len) {          \
        return EMPTY_LIST;  \
    }

#define CHECK_LIST(l)      \
    CHECK_LIST_NONNULL(l)    \
    CHECK_LIST_NONEMPTY(l)

#define CHECK_SEARCH_ARGUMENT(a)     \
    if (a == nullptr) {              \
        return NO_VALID_SEARCH_TERM; \
    }                                \

#define CHECK_NODE(n)                \
    if (n == nullptr) {              \
        return NULL_WHILE_ITERATING; \
    }

#define FIND_END(n, dir) \
    while (n->dir) {     \
        n = n->dir;      \
    }

#define CLEAR_NODE(n)  \
    n->next = nullptr; \
    n->prev = nullptr; \
    n->data = 0;       \
    free(n);

#define CLEAR_DIR(n, t, dir) \
    while (n->dir) {         \
        t = n->dir;          \
        CLEAR_NODE(n)        \
        n = t;               \
    }                        \

#define STR_EQ(a, b) (a == b || strcmp(a, b) == 0)


Error new_node(const char *string, Node **out) {
    Node *new_struct;
    ALLOC_STRUCT(Node)
    new_struct->data = string;
    *out = new_struct;
    return SUCCESS;
}

Error insert(List *l, Node *node, Node *new_node, const Position position) {
    CHECK_LIST_NONNULL(l)
    CHECK_SEARCH_ARGUMENT(node)
    if (new_node == nullptr || new_node->data == nullptr) {
        return NO_STRING_PROVIDED;
    }
    switch (position) {
        case BEFORE:
            if (l->head == node) {
                l->head = new_node;
            }
            new_node->next = node;
            new_node->prev = node->prev;
            node->prev = new_node;
            return SUCCESS;
        case AFTER:
            if (l->tail == node) {
                l->tail = new_node;
            }
            new_node->prev = node;
            new_node->next = node->next;
            node->next = new_node;
            return SUCCESS;
        default:
            return INVALID_POSITION;
    }
}

Error remove_node(List *l, Node *node) {
    // preliminary error checks
    CHECK_LIST(l)
    CHECK_SEARCH_ARGUMENT(node)
    // removing the first node in the list
    if (node == l->head) {
        l->head = node->next;
    }
    // removing the last node in the list
    if (node == l->tail) {
        l->tail = node->prev;
    }
    // update circular pointers
    if (node->next != nullptr) {
        node->next->prev = node->prev;
    }
    if (node->prev != nullptr) {
        node->prev->next = node->next;
    }
    CLEAR_NODE(node)
    return SUCCESS;
}

Error find(const List *l, const char *string, Node **out) {
    // only variable
    Node *node = nullptr;
    // preliminary error checks
    CHECK_LIST(l)
    CHECK_SEARCH_ARGUMENT(string)
    if (out == nullptr) {
        return OUTPUT_INVALID;
    }
    // traverse either direction just in case - should only ever need first loop
    if (l->head != nullptr) {
        node = l->head;
        while (node != nullptr) {
            if (STR_EQ(node->data, string)) {
                *out = node;
                return SUCCESS;
            }
            node = node->next;
        }
        if (node != l->tail) {
            return NULL_WHILE_ITERATING;
        }
        return NO_RESULT;
    }
    if (l->tail != nullptr) {
        node = l->tail;
        while (node != nullptr) {
            if (STR_EQ(node->data, string)) {
                *out = node;
            }
            node = node->prev;
        }
        if (node != l->head) {
            return NULL_WHILE_ITERATING;
        }
        return NO_RESULT;
    }
    return NULL_WHILE_ITERATING;
}

/*
Error new(List **out) {
    List *new_struct;
    ALLOC_STRUCT(List)
    *out = new_struct;
    return SUCCESS;
}

static Error alloc(Node **out) {
    Node *new_struct;
    ALLOC_STRUCT(Node)
    *out = new_struct;
    return SUCCESS;
}

int append(List *l, const char *x) {
    int err;
    if ((err = insert(l, -1, x))) {
        return err;
    }
}
int append_left(List *l, const char *x) {
    int err;
    if ((err = insert(l, 0, x))) {
        return err;
    }
}

int clear(List *l) {
    CHECK_LIST(l)
    Node *n, *t;
    if ((n = l->head)) {
        CLEAR_DIR(n, t, next)
    }
    if ((n = l->tail)) {
        CLEAR_DIR(n, t, prev)
    }
    l->len = 0;
    free(l);
}

int contains(List *l, const char *item) {
    ssize_t err;
    return (err = index(l, item)) >= 0 || err != NO_RESULT && err;
}

ssize_t index(List *l, const char *x) {
    CHECK_LIST(l)
    Node *n;
    if (((n = l->head) != NULL && STR_EQ(x, n->data))
        || ((n = l->tail) != NULL && STR_EQ(x, n->data))) {
        return true;
    }
    // TODO: Check middle
    if (n == l) {
        return NO_RESULT;
    }
    // TODO: remove above placeholder

    return false;
}

int append(List *l, const char *x) {
    CHECK_LIST(l)

    if (l->tail == NULL) {
        if (l->head == NULL) {
            ALLOC_NODE(&l->head)
            l->tail = l->head;
        } else {
            Node *n = l->head;
            FIND_END(n, next)
            ALLOC_NODE(&n->next)
            l->tail = n->next;
        }
    } else {
        Node *n = l->tail;
        ALLOC_NODE(&l->tail)
        n->next = l->tail;
        l->tail->prev = n;
    }

    l->tail->data = x;
    l->len += 1;
}

// find_string by data or index
static int find_node(const Node *head, const char *in_str, ssize_t *inout_int, Node **out_node) {
    // can't do anything to an imaginary list
    if (head == NULL) {
        return NOT_A_LIST;
    }
    ssize_t index = 0;
    bool str_search = in_str != NULL;
    if (!str_search) {
        if (inout_int != NULL) {
            index = *inout_int;
        } else {
            return NO_VALID_SEARCH_TERM;
        }
    }
    // 0 is head, -1 is tail, positive forward, negative backward
    bool forward = index >= 0 != 0;
    if (index < 0) {
        index = -index;
    }
    // iterate until the appointed node
    const Node *cur = head;
    ssize_t i = 0;
    for (i = 0; str_search ? cur->data != in_str && cur != head : i < index; cur = forward ? cur->next : cur->prev, ++i) {  // TODO: actually strcmp the strings...
        if ((forward ? cur->next : cur->prev) == NULL) {
            return NULL_WHILE_ITERATING;
        }
    }
    if (str_search) {
        if (cur == head) {
            return EXIT_FAILURE;
        }
        if (inout_int != NULL) {
            *inout_int = i;
        }
    }
    if (out_node != NULL) {
        *out_node = (Node *) cur;
    }
    return EXIT_SUCCESS;
}
int find_index(const Node *head, const char *in, ssize_t *out) {
    int err;
    ssize_t index = 0;
    if ((err = find_node(head, in, &index, NULL))) {
        return err;
    }
    *out = index;
    return EXIT_SUCCESS;
}
int find_string(const Node *head, const ssize_t index, const char **out) {
    int err;
    Node *node;
    if ((err = find_node(head, NULL, &index, &node))) {
        return err;
    }
    *out = node->data;
    return EXIT_SUCCESS;
}


// insert at head, tail, or specific index
int ins(Node **head, const char *item, ssize_t index) {
    int err;
    Node *node, *new_node;
    if ((err = alloc(&new_node))) {
        return err;
    }
    new_node->data = item;
    if ((err = find_node(*head, NULL, &index, &node))) {
        return err;
    }
    // TODO: Fix this
    new_node->next = node;
    new_node->prev = node->prev;
    node->prev = new_node;
    new_node->prev->next = new_node;
    if (index == 0) {
        *head = new_node;
    }
}


// delete_index by data or index
static int delete_node(Node *head, const char *data, const ssize_t *index) {
    int err;
    Node *node;
    if ((err = find_node(head, data, index, &node))) {
        return err;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->prev = NULL;
    node->next = NULL;
    if (node->data != NULL) {
        free((char *) node->data);
    }
    free(node);
    return EXIT_SUCCESS;
}
int delete_string(Node *head, const char *data) {
    int err;
    if ((err = delete_node(head, data, NULL))) {
        return err;
    }
    return EXIT_SUCCESS;
}
int delete_index(Node *head, const ssize_t index) {
    int err;
    if ((err = delete_node(head, NULL, &index))) {
        return err;
    }
    return EXIT_SUCCESS;
}
*/
