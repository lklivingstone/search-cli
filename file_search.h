#ifndef FILE_SEARCH_H
#define FILE_SEARCH_H

#include <string>
#include <vector>
#include<set>

std::vector<std::string> get_files_with_extensions (
    const std::string& folder, const std::set<std::string>& extensions
);

#endif
