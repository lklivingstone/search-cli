#include <filesystem>

#include "file_search.h"

namespace fs = std::filesystem;

std::vector<std::string> get_files_with_extensions (
  const std::string& folder, const std::set<std::string>& extensions) {
    std::vector<std::string> result;
    for (const auto& entry : fs::recursive_directory_iterator(folder)) {
	if (entry.is_regular_file()) {
	    if (extensions.count(entry.path().extension().string()))
		result.push_back(entry.path().string());
	}
    }
    return result;
}
