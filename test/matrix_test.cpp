#include "aclext/matrix.hpp"
#include "atcoder/modint"
#include "gtest/gtest.h"

using namespace aclext;

using mint = atcoder::modint1000000007;
using Mat = Matrix<mint>;

TEST(MatrixTest, Fibonacci) {
    function<int(int)> fib = [&](int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;

        Mat a({ { 1, 1 }, { 1, 0 } });
        Mat v = Mat::column_vector({ fib(1), fib(0) });

        return int(((a ^ (n - 1)) * v)[0][0].val());
    };

    EXPECT_EQ(fib(0), 0);
    EXPECT_EQ(fib(1), 1);
    EXPECT_EQ(fib(2), 1);
    EXPECT_EQ(fib(3), 2);
    EXPECT_EQ(fib(4), 3);
    EXPECT_EQ(fib(5), 5);
    EXPECT_EQ(fib(6), 8);
    EXPECT_EQ(fib(100), 687995182);
}