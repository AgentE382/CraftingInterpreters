//
// Created by Martin on 2/18/2024.
//
#include "tau/tau.h"

TAU_MAIN()

TEST(a, count) {
    int count = 10000000;
    REQUIRE_EQ(count, 10000000);
}

TEST(b, require) {
    REQUIRE_LE(1, 1);
    REQUIRE_LE(1, 2);
}