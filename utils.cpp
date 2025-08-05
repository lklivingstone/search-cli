#include <iostream>
#include <vector>
#include <thread>

#include "constants.h"
#include "search_result.h"

void print_details(int threads, std::thread::id curr_thread, int file_sz) {
    std::cout << kWatchThreadsMsg;
    std::cout << "Processing " << file_sz << " files using " << threads << " threads\n";
    std::cout << "Main thread ID: " << curr_thread << "\n\n";
    return;
}

void print_output(std::vector<SearchResult>& results, bool& show_details) {
    if (show_details)
	std::cout << kWowMsg;

    for (const auto& res : results) {
	std::cout << res.filename << ": ";
	for (int line : res.lines)
	    std::cout << line << " ";
	std::cout << '\n';
    }
    if (results.empty()) std::cout << kOopsMsg;
    return;
}
