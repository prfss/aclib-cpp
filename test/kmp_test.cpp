#include "aclext/kmp.hpp"
#include "gtest/gtest.h"

TEST(KmpTest, PrefixFunction) {
    const vector<string> s = { "abcabcd", "aabaaab" };
    const vector<vector<int>> pi = { { 0, 0, 0, 1, 2, 3, 0 }, { 0, 1, 0, 1, 2, 2, 3 } };

    for (size_t i = 0; i < s.size(); i++) {
        EXPECT_EQ(pi[i], prefix_function(s[i]));
    }
}

TEST(KmpTest, KmpSearch) {
    vector<string> strs = { "dababbabcbbaabbabb", "ABC ABCDAB ABCDABCDABDE", "1111111111", "abcdaaabceabcdabcdabcdabced", "abcbabcacabc" };
    vector<string> pattern = { "abb", "ABCDABD", "111", "abcdabcd", "bbbb" };
    vector<vector<int>> expected = { { 3, 12, 15 }, { 15 }, { 0, 1, 2, 3, 4, 5, 6, 7 }, { 10, 14 }, {} };

    for (size_t i = 0; i < strs.size(); i++) {
        auto pos = kmp_search(strs[i], pattern[i]);
        EXPECT_EQ(pos, expected[i]);
    }
}

TEST(KmpTest, KmpSearchLong) {
    string s;
    for (int i = 0; i < 100000; i++) {
        s.push_back(i % 26 + 'a');
    }
    string pattern;
    for (int i = 0; i < 5000; i++) {
        pattern.push_back(i % 26 + 'a');
    }

    EXPECT_EQ(kmp_search(s, pattern).size(), (s.size() - pattern.size() + 1) / 26 + 1);
}

TEST(KmpTest, KmpSearchEmpty) {
    vector<string> s = { "", "nonemptystring", "" };
    vector<string> pattern = { "nonemptypattern", "", "" };
    for (size_t i = 0; i < s.size(); i++) {
        if (pattern[i].empty()) {
            EXPECT_DEATH(kmp_search(s[i], pattern[i]), "");
        } else {
            EXPECT_EQ(kmp_search(s[i], pattern[i]).size(), 0);
        }
    }
}