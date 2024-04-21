// Copyright 2024 EltIsma

#include <gtest/gtest.h>
#include "../include/textgen.h"

TEST(TextGenerator, BuildPrefix) {
    TextGenerator generator;
    std::vector<std::string> words = {"the", "quick", "brown", "fox"};
    prefix p = generator.buildPrefix(words, 2);
    ASSERT_EQ(p.size(), 2);
    ASSERT_EQ(p[0], "the");
    ASSERT_EQ(p[1], "quick");
}

TEST(TextGenerator, BuildEntry) {
    TextGenerator generator;
    prefix p = {"the", "quick"};
    std::string suffix = "brown";
    std::pair<prefix, std::string> entry = generator.buildEntry(p, suffix);
    ASSERT_EQ(entry.first.size(), 2);
    ASSERT_EQ(entry.first[0], "the");
    ASSERT_EQ(entry.first[1], "quick");
    ASSERT_EQ(entry.second, "brown");
}





