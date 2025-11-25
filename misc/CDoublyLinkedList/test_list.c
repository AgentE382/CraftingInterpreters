//
// Created by Martin on 2/18/2024.
//
#include "library.h"
#include "tau/tau.h"

TAU_MAIN()

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
    CHECK_EQ(insert(&l, nullptr, nullptr, 3), NO_VALID_SEARCH_TERM);
    CHECK_EQ(insert(nullptr, &n, nullptr, 3), NOT_A_LIST);
    CHECK_EQ(insert(nullptr, nullptr, &nn, 3), NOT_A_LIST);
    CHECK_EQ(insert(nullptr, nullptr, nullptr, AFTER), NOT_A_LIST);
    // 2 bad
    CHECK_EQ(insert(&l, &n, nullptr, 3), NO_STRING_PROVIDED);
    CHECK_EQ(insert(&l, nullptr, &nn, 3), NO_VALID_SEARCH_TERM);
    CHECK_EQ(insert(&l, nullptr, nullptr, AFTER), NO_VALID_SEARCH_TERM);
    CHECK_EQ(insert(nullptr, &n, nullptr, AFTER), NOT_A_LIST);
    CHECK_EQ(insert(nullptr, nullptr, &nn, AFTER), NOT_A_LIST);
    CHECK_EQ(insert(&l, &n, &nn, 3), NO_STRING_PROVIDED);
    nn.data = s;
    CHECK_EQ(insert(&l, &n, &nn, 3), INVALID_POSITION);
    nn.data = nullptr;
    // 1 bad
    CHECK_EQ(insert(nullptr, &n, &nn, AFTER), NOT_A_LIST);
    CHECK_EQ(insert(&l, nullptr, &nn, AFTER), NO_VALID_SEARCH_TERM);
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
