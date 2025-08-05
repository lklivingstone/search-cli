#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <string>
#include <sstream>
#include <algorithm>
#include <thread>

#include "constants.h"
#include "file_search.h"
#include "search_worker.h"
#include "arg_parser.h"
#include "utils.h"

int main(int argc, char* argv[]) {
    std::string pattern;
    std::set<std::string> extensions;
    int threads;
    bool show_details = false;

    if (!parse_args(argc, argv, pattern, extensions, threads, show_details)) {
	std::cerr << kInvalidArgsMsg;
	return 1;
    }

    auto files = get_files_with_extensions(".", extensions);

    if (show_details) {
	int file_sz = files.size();
	std::thread::id curr_thread = std::this_thread::get_id();
	print_details(threads, curr_thread, file_sz);
    }
    
    auto results = search_files_thread_pool(files, pattern, threads, show_details);

    print_output(results, show_details);

    return 0;
}
