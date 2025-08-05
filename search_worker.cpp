#include <fstream>
#include <regex>
#include <future>
#include <algorithm>
#include <thread>
#include <iostream>

#include "thread_pool.h"
#include "search_worker.h"

std::mutex output_mutex;

SearchResult search_file(
  const std::string& filename,
  const std::string& pattern,
  bool& show_details) {
    SearchResult result{filename};

    if (show_details) {
	std::stringstream ss;
	ss << "[Thread " << std::this_thread::get_id() << "] Processing: " << filename;
	std::lock_guard<std::mutex> lock(output_mutex);
	std::cout << ss.str() << std::endl;
    }

    std::ifstream file(filename);
    if (!file) return result;

    std::string line;
    std::regex re(pattern);
    int line_num = 1;
    while (getline(file, line)) {
	if (std::regex_search(line, re))
	    result.lines.push_back(line_num);
	++line_num;
    }

    if (show_details) {
	std::stringstream ss;
	ss << "[Thread " << std::this_thread::get_id() << "] Completed: " << filename << " (" << result.lines.size() << " matches)";
	std::lock_guard<std::mutex> lock(output_mutex);
	std::cout << ss.str() << std::endl;
    }

    return result;
}

std::vector<SearchResult> search_files_thread_pool (
  const std::vector<std::string>& files,
  const std::string& pattern,
  int threads,
  bool& show_details) {
    auto results = std::make_shared<std::vector<SearchResult>>();
    auto results_mutex = std::make_shared<std::mutex>();
    {
	ThreadPool pool(threads);

	for (const auto& file : files) {
	    pool.enqueue([&file, &pattern, &show_details, &results, &results_mutex]() {
		SearchResult res = search_file(file, pattern, show_details);
		if (!res.lines.empty()) {
		    std::lock_guard<std::mutex> lock(*results_mutex);
		    results->push_back(std::move(res));
		}
	    });
	}
    }
    return *results;
}
