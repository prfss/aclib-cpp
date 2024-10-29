#include "aclib/li_chao_tree.hpp"
#include "gtest/gtest.h"

using namespace std;

struct F {
    int a, b;
    int operator()(int x) {
        return a * x + b;
    }
};

using LCTree = LiChaoTree<int, int, F>;

TEST(LiChaoTreeTest, SmallExample) {
    LCTree lct(-10, 6);

    lct.add({ 4, 0 });
    EXPECT_EQ(lct(0), 0);
    EXPECT_EQ(lct(2), 8);
    lct.add({ 3, 2 });
    EXPECT_EQ(lct(1), 4);
    EXPECT_EQ(lct(2), 8);
    EXPECT_EQ(lct(3), 11);
    lct.add({ 1, 9 });
    EXPECT_EQ(lct(3), 11);
    EXPECT_EQ(lct(4), 13);
    lct.add({ -1, 15 });
    EXPECT_EQ(lct(4), 11);
    lct.add({ 1, 5 });
    EXPECT_EQ(lct(3), 8);
    EXPECT_EQ(lct(4), 9);
    EXPECT_EQ(lct(6), 9);
}
