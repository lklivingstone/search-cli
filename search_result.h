#ifndef SEARCH_RESULT_H
#define SEARCH_RESULT_H

#include <string>
#include <vector>

struct SearchResult {
    std::string filename;
    std::vector<int> lines;
};

#endif
