#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <thread>

#include "search_result.h"

void print_details(int threads, std::thread::id curr_thread, int file_sz);
void print_output(std::vector<SearchResult>& results, bool& show_details);

#endif // UTILS_H
