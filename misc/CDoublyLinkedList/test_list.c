//
// Created by Martin on 2/18/2024.
//
#include "library.h"
#include "tau/tau.h"

TAU_MAIN()

TEST(ArgumentsAreChecked, new_list) {
    CHECK_EQ(new_list(nullptr), OUTPUT_INVALID);
}
TEST(ArgumentsAreChecked, new_node) {
    Node *p = nullptr;
    CHECK_EQ(new_node(nullptr, nullptr), NO_STRING_PROVIDED);
    CHECK_EQ(new_node("", nullptr), OUTPUT_INVALID);
    CHECK_EQ(new_node(nullptr, &p), NO_STRING_PROVIDED);
}
TEST(ArgumentsAreChecked, insert) {
    const List l = {nullptr, nullptr, 0};
    Node n = {nullptr, nullptr, nullptr}, nn = {nullptr, nullptr, nullptr};
    const char *s = "insert";
    // 4 bad
    CHECK_EQ(insert(nullptr, nullptr, nullptr, 3), NOT_A_LIST);
    // 3 bad
    CHECK_EQ(insert(&l, nullptr, nullptr, 3), NO_STRING_PROVIDED);
    CHECK_EQ(insert(nullptr, &n, nullptr, 3), NOT_A_LIST);
    CHECK_EQ(insert(nullptr, nullptr, &nn, 3), NOT_A_LIST);
    CHECK_EQ(insert(nullptr, nullptr, nullptr, AFTER), NOT_A_LIST);
    // 2 bad
    CHECK_EQ(insert(&l, &n, nullptr, 3), NO_STRING_PROVIDED);
    CHECK_EQ(insert(&l, nullptr, &nn, 3), NO_STRING_PROVIDED);
    CHECK_EQ(insert(&l, nullptr, nullptr, AFTER), NO_STRING_PROVIDED);
    CHECK_EQ(insert(nullptr, &n, nullptr, AFTER), NOT_A_LIST);
    CHECK_EQ(insert(nullptr, nullptr, &nn, AFTER), NOT_A_LIST);
    CHECK_EQ(insert(&l, &n, &nn, 3), NO_STRING_PROVIDED);
    nn.data = s;
    CHECK_EQ(insert(&l, &n, &nn, 3), INVALID_POSITION);
    nn.data = nullptr;
    // 1 bad
    CHECK_EQ(insert(nullptr, &n, &nn, AFTER), NOT_A_LIST);
    CHECK_EQ(insert(&l, nullptr, &nn, AFTER), NO_STRING_PROVIDED);
    CHECK_EQ(insert(&l, &n, nullptr, AFTER), NO_STRING_PROVIDED);
    CHECK_EQ(insert(&l, &n, &nn, 3), NO_STRING_PROVIDED);
    nn.data = s;
    CHECK_EQ(insert(&l, &n, &nn, 3), INVALID_POSITION);
    nn.data = nullptr;
}
TEST(ArgumentsAreChecked, remove_node) {
    List l = {nullptr, nullptr, 0};
    const Node n = {nullptr, nullptr, nullptr};
    // 2 bad
    CHECK_EQ(remove_node(nullptr, nullptr), NOT_A_LIST);
    // 1 bad
    CHECK_EQ(remove_node(&l, nullptr), EMPTY_LIST);
    ++l.len;
    CHECK_EQ(remove_node(&l, nullptr), NO_VALID_SEARCH_TERM);
    --l.len;
    CHECK_EQ(remove_node(nullptr, &n), NOT_A_LIST);
}
TEST(ArgumentsAreChecked, find) {
    List l = {nullptr, nullptr, 0};
    Node *p = nullptr;
    const char *s = "find";
    // 3 bad
    CHECK_EQ(find(nullptr, nullptr, nullptr), NOT_A_LIST);
    // 2 bad
    CHECK_EQ(find(&l, nullptr, nullptr), EMPTY_LIST);
    ++l.len;
    CHECK_EQ(find(&l, nullptr, nullptr), NO_VALID_SEARCH_TERM);
    --l.len;
    CHECK_EQ(find(nullptr, s, nullptr), NOT_A_LIST);
    CHECK_EQ(find(nullptr, nullptr, &p), NOT_A_LIST);
    // 1 bad
    CHECK_EQ(find(nullptr, s, &p), NOT_A_LIST);
    CHECK_EQ(find(&l, nullptr, &p), EMPTY_LIST);
    ++l.len;
    CHECK_EQ(find(&l, nullptr, &p), NO_VALID_SEARCH_TERM);
    CHECK_EQ(find(&l, s, nullptr), OUTPUT_INVALID);
    --l.len;
}
TEST(ArgumentsAreChecked, delete_list) {
    CHECK_EQ(delete_list(nullptr), NOT_A_LIST);
}
TEST(BasicFunctionality, new_list) {
    List *l;
    CHECK_EQ(new_list(&l), SUCCESS);
    CHECK_NULL(l->head);
    CHECK_NULL(l->tail);
    CHECK_EQ(l->len, 0);
}
TEST(BasicFunctionality, new_node) {
    Node *n;
    const char *s = "new_node";
    CHECK_EQ(new_node(s, &n), SUCCESS);
    CHECK_NULL(n->next);
    CHECK_NULL(n->prev);
    CHECK_STREQ(n->data, s);
    CHECK_PTR_NE(s, n->data);
}
TEST(BasicFunctionality, insert) {
    const char *s = "insert", *s2 = "insert2";
    Node *n, *nn;
    List *l;
    new_list(&l);
    new_node(s, &n);
    new_node(s2, &nn);
    l->head = n;
    l->tail = n;
    l->len = 1;
    CHECK_EQ(insert(l, n, nn, AFTER), SUCCESS);
    CHECK_PTR_EQ(l->head, n);
    CHECK_PTR_EQ(l->tail, nn);
    CHECK_EQ(l->len, 2);
    CHECK_PTR_EQ(n->next, nn);
    CHECK_PTR_EQ(nn->prev, n);
    CHECK_STREQ(l->head->data, s);
    CHECK_STREQ(l->tail->data, s2);
}
TEST(BasicFunctionality, remove_node) {
    const char *s = "remove_node";
    Node *n;
    List *l;
    new_list(&l);
    new_node(s, &n);
    l->head = n;
    l->tail = n;
    l->len = 1;
    CHECK_EQ(remove_node(l, n), SUCCESS);
    CHECK_NULL(l->head);
    CHECK_NULL(l->tail);
    CHECK_EQ(l->len, 0);
}
TEST(BasicFunctionality, find) {
    const char *s = "find";
    Node *n;
    List *l;
    new_list(&l);
    new_node(s, &n);
    l->head = n;
    l->tail = n;
    l->len = 1;
    Node *nn = nullptr;
    CHECK_EQ(find(l, s, &nn), SUCCESS);
    CHECK_PTR_EQ(nn, n);
    CHECK_STREQ(nn->data, s);
}
TEST(BasicFunctionality, delete_list) {
    const char *s = "find", *s2 = "find2";
    Node *n, *nn;
    List *l;
    new_list(&l);
    new_node(s, &n);
    new_node(s2, &nn);
    l->head = n;
    l->tail = nn;
    l->len = 2;
    n->next = nn;
    nn->prev = n;
    CHECK_EQ(delete_list(l), SUCCESS);
}
