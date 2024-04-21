// Copyright 2024 EltIsma

#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <string>
#include <sstream>
#include <deque>
#include <utility>
#include <map>
#include <vector>
#include <unordered_map>
#include <random>

typedef std::deque<std::string> prefix;  // очередь префиксов

class TextGenerator {
 private:
    std::map<prefix, std::vector<std::string> > statetab; // префикс-суффиксы
 public:
    void buildTable(std::istream &file, int prefix_length);
    std::string generate_text(int text_size);
    prefix buildPrefix(const std::vector<std::string>& words,
    int prefix_length);
    std::pair<prefix, std::string> buildEntry(const prefix& p,
    const std::string& suffix);
};

#endif  // INCLUDE_TEXTGEN_H_
