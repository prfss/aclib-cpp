#include "aclext/matrix.hpp"
#include "atcoder/modint"
#include "gtest/gtest.h"

using namespace aclext;

using mint = atcoder::modint1000000007;

mint add(mint a, mint b) { return a + b; }
mint mul(mint a, mint b) { return a * b; }
mint zero() { return 0; }
mint one() { return 1; }
using Mat = Matrix<mint, add, mul, zero, one>;

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

using MatSub = Matrix<mint, add, mul, zero, one, true>;
TEST(MatrixTest, WithSubtraction) {
    MatSub a({ { 1, 2, 3, 4 }, { 5, 6, 7, 8 } });

    MatSub zero24 = MatSub(2, 4);

    MatSub b({ { 1, 2 }, { 3, 4 } });

    MatSub zero22 = MatSub(2, 2);

    EXPECT_EQ(a - a, zero24);
    EXPECT_EQ(b * b - b * b, zero22);
}