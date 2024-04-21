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

// Test selecting a single suffix from a vector
TEST(TextGeneratorTest, SelectSuffixSingle) {
    std::vector<std::string> suffixes{"jumps"};
    TextGenerator gen;
    std::string suff = gen.selectSuffix(suffixes);
    EXPECT_EQ(suff, "jumps");
}

// Test selecting a suffix from a vector with multiple options
TEST(TextGeneratorTest, SelectSuffixMultiple) {
    std::vector<std::string> suffixes{"over", "under", "around"};
    TextGenerator gen;
    std::string suff = gen.selectSuffix(suffixes);
    // The selected suffix should be one of the options
    EXPECT_TRUE(suff == "over" || suff == "under" || suff == "around");
}

// Test generating text from a manually populated table
TEST(TextGeneratorTest, GenerateText) {
    TextGenerator gen;
    std::map<prefix, std::vector<std::string> > testMap = {
        std::make_pair(prefix{"the", ""},
        std::vector<std::string>{"quick", "lazy"}),
        std::make_pair(prefix{"quick", "the"},
        std::vector<std::string>{"brown"}),
        std::make_pair(prefix{"brown", "quick"},
        std::vector<std::string>{"fox"}),
        std::make_pair(prefix{"fox", "brown"},
        std::vector<std::string>{"jumps"}),
        std::make_pair(prefix{"jumps", "fox"},
        std::vector<std::string>{"over"}),
        std::make_pair(prefix{"over", "jumps"},
        std::vector<std::string>{"the"}),
        std::make_pair(prefix{"lazy", "the"},
        std::vector<std::string>{"dog"})
    };
     gen.set_statetab(testMap);

    std::string text = gen.generate_text(5);
    // The generated text should be one of the possible combinations
    // of words in the table
    EXPECT_TRUE(text == "quick the brown fox jumps over " ||
                text == "quick the brown fox jumps the " ||
                text == "lazy thebrown fox jumps over " ||
                text == "lazy the brown fox jumps the ");
}


