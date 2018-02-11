#include "string/TRIE.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

using std::string;
using std::vector;
using vinalx::TRIE;

TEST(BasicTest, TestEmpty) {
    TRIE t;
    EXPECT_EQ(t.Size(), 0);
    EXPECT_FALSE(t.Find(""));
    EXPECT_FALSE(t.Find("whatever"));
    EXPECT_FALSE(t.Find("should"));
    EXPECT_FALSE(t.Find("be"));
    EXPECT_FALSE(t.Find("false"));
}

TEST(BasicTest, TestInsertTrivial) {
    TRIE t;
    t.Insert("");
    EXPECT_TRUE(t.Find(""));
    t.Insert("trivial");
    EXPECT_TRUE(t.Find("trivial"));
    EXPECT_FALSE(t.Find("trivia"));
    EXPECT_FALSE(t.Find("triviall"));
}

TEST(BasicTest, TestInsertMany) {
    TRIE t;
    vector<string> strs{"trie", "algorithm",   "test", "basic", "insert",
                        "many", "teststrings", "in",   "the",   "tree"};
    vector<string> falsity{"these", "strings", "are", "not", "inside"};
    int i = 0;
    for (const auto &str : strs) {
        EXPECT_EQ(i, t.Size());
        ++i;
        t.Insert(str);
    }
    for (const auto &str : strs) {
        EXPECT_TRUE(t.Find(str));
    }
    for (const auto &str : falsity) {
        EXPECT_EQ(i, t.Size());
        EXPECT_FALSE(t.Erase(str));
    }
}

TEST(BasicTest, TestErase) {
    TRIE t;
    vector<string> strs{"trie", "algorithm",   "test", "basic", "insert",
                        "many", "teststrings", "in",   "the",   "tree"};
    int i = strs.size();
    for (const auto &str : strs) {
        t.Insert(str);
    }
    // std::shuffle(begin(strs), end(strs), std::random_device());
    std::reverse(begin(strs), end(strs));
    for (const auto &str : strs) {
        EXPECT_TRUE(t.Erase(str)) << str << " not erased";
        --i;
        EXPECT_EQ(i, t.Size());
    }
}