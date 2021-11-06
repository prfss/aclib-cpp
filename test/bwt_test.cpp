#include "aclext/bwt.hpp"
#include "gtest/gtest.h"

using namespace aclext;

TEST(BwtTest, SmallExample) {
    const string s = "mississippi";

    const string a = bwt(s);
    const string b = "pssmipissii";

    EXPECT_EQ(a, b);
}
