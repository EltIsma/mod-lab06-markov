// Copyright 2024 EltIsma

#include "../include/textgen.h"
#include <random>
#include <unordered_map>

// Build table of prefixes and suffixes
void TextGenerator::buildTable(std::istream &file, int prefix_length) {
    prefix p;
    std::string word;
    while (file >> word) {
        if (p.size() == prefix_length) {
            statetab[p].push_back(word);
            p.pop_front();
        }
        p.push_back(word);
    }
}

// Function to generate text based on the Markov chain
std::string TextGenerator::generate_text(int size_text) {
    std::mt19937 gen(time(0)); // random number generator
    // distribution for random number
    std::uniform_int_distribution<> dis(0, 99);
    prefix p = statetab.begin()->first;
    std::string text = "";
    for (int i = 0; i < size_text; i++) {
        if (statetab.find(p) == statetab.end()) { // if prefix not found
            break;
        }
        std::vector<std::string> suffixes = statetab.at(p);
        // choose random suffix
        std::string suff = suffixes[dis(gen) % suffixes.size()];
        text += suff + " ";
        p.pop_front();
        p.push_back(suff);
    }
    return text;
}


prefix TextGenerator::buildPrefix(const std::vector<std::string>& words,
int prefix_length) {
    prefix p;
    for (int i = 0; i < std::min(prefix_length,
    static_cast<int>(words.size())); i++) {
        p.push_back(words[i]);
    }
    return p;
}

std::pair<prefix, std::string> TextGenerator::buildEntry(const prefix& p,
 const std::string& suffix) {
    return std::make_pair(p, suffix);
}

std::string TextGenerator::chooseSingleSuffix(
const std::vector<std::string>& suffixes,
std::mt19937& gen) {
    std::uniform_int_distribution<> dis(0, suffixes.size() - 1);
    return suffixes[dis(gen)];
}

std::string TextGenerator::chooseSuffix(const std::vector<std::pair<std::string,
int>>& suffixes, std::mt19937& gen) {
    int total_count = 0;
    for (const auto& suffix : suffixes) {
        total_count += suffix.second;
    }
    std::uniform_int_distribution<> dis(0, total_count - 1);
    int random_count = dis(gen);
    for (const auto& suffix : suffixes) {
        if (random_count < suffix.second) {
            return suffix.first;
        }
        random_count -= suffix.second;
    }
    return ""; // shouldn't reach here
}

prefix TextGenerator::choosePrefix(const std::unordered_map<prefix,
std::vector<std::string>>& statetab, std::mt19937& gen) {
    std::uniform_int_distribution<> dis(0, statetab.size() - 1);
    int random_index = dis(gen);
    auto it = std::next(statetab.begin(), random_index);
    return it->first;
}

