#include "aclib/lca.hpp"
#include "gtest/gtest.h"

TEST(LcaTest, SmallExample) {
    const int n = 9;

    Lca lca(n);

    lca.add_edge(5, 0);
    lca.add_edge(5, 2);
    lca.add_edge(0, 3);
    lca.add_edge(0, 4);
    lca.add_edge(3, 1);
    lca.add_edge(2, 6);

    EXPECT_EQ(lca(3, 1), 3);
    EXPECT_EQ(lca(4, 1), 0);
    EXPECT_EQ(lca(1, 6), 5);
    EXPECT_EQ(lca(3, 4), 0);
    EXPECT_EQ(lca(0, 7), -1);
    EXPECT_EQ(lca(7, 8), -1);
    EXPECT_EQ(lca(0, 5), 5);
    EXPECT_EQ(lca(5, 0), 5);

    for (int i = 0; i < n; i++) {
        EXPECT_EQ(lca(i, i), i);
        for (int j = i + 1; j < n; j++) {
            EXPECT_EQ(lca(i, j), lca(j, i));
        }
    }
}
