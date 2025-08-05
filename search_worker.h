#ifndef SEARCH_WORKER_H
#define SEARCH_WORKER_H

#include <string>
#include <vector>

#include "search_result.h"

// Search one file for pattern (regex), return SearchResult
SearchResult search_file(const std::string& filename,
    const std::string& pattern,
    bool& show_details
);

// Multithreaded: search all files, return vector of SearchResult
std::vector<SearchResult> search_files_thread_pool (
    const std::vector<std::string>& files,
    const std::string& pattern,
    int threads,
    bool& show_details
);
#endif // SEARCH_WORKER_H
