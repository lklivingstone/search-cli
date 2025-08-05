#include <iostream>
#include <algorithm>
#include <cctype>
#include <stdexcept>

#include "arg_parser.h"
#include "constants.h"

// Print help message
void print_help() {
    std::cout << "Usage:\n"
    << "  ./search_cli --pattern=\"PATTERN\" --extension=cpp,c,py,txt --threads=N\n\n"
    << "Options:\n"
    << "  --pattern     The text or regex to search for (required)\n"
    << "  --extension   Comma-separated file types (choose from: c, cpp, py, txt)\n"
    << "  --threads     Number of parallel threads (required)\n"
    << "  --details	Show thread ID for each file being processed (optional)\n"
    << "  --help        Print this help message\n\n"
    << "Supported file types: c, cpp, py, txt\n"
    << "You may specify any combination and count of these extensions.\n"
    << "Example:\n"
    << "  ./search_cli --pattern=\"main\" --extension=cpp,py --threads=8 --details\n\n";
}

bool parse_extensions(std::string &extensionStr, std::set<std::string>& extensions) {
    int index = 0;
    while (index < extensionStr.length()) {
	int end = extensionStr.find(',', index);
	std::string ext = extensionStr.substr(index, end-index);

	ext.erase(
	    std::remove_if(ext.begin(), ext.end(),
		[](char c) {
		    return std::isspace(static_cast<unsigned char>(c));
		} 
	    ), ext.end()
	);

	if (!ext.empty()) {
	    if (allowed_exts.count(ext)) {
		extensions.insert('.'+ext);
	    }
	    else {
		std::cerr << "Error: Unsupported Extension: " << ext << "\n";
		return false;
	    }
	}

	if (end == std::string::npos) break;
	index = end + 1;
    }
    return true;
}

bool parse_args(int argc, char* argv[], std::string& pattern, std::set<std::string>& extensions, int& threads, bool& show_details) {
    bool is_pattern_set = false, is_extensions_set = false, is_threads_set = false;
    for (int i=1; i<argc; i++) {
	std::string arg = argv[i];
	
	if (arg == kHelpCmd) {
	    print_help();
	    exit(0);
	}
	else if (arg == kDetailsCmd) {
	    show_details = true;
	}
	else if (arg.find(kPatternCmd) == 0) {
	    is_pattern_set = true;
	    pattern = arg.substr(kPatternCmd.length());
	}
	else if (arg.find(kExtensionCmd) == 0) {
	    std::string extensionStr = arg.substr(kExtensionCmd.length()); 
	    if (!parse_extensions(extensionStr, extensions)) return false;
	    is_extensions_set = true;
	}
	else if (arg.find(kThreadCmd) == 0) {
	    try {
		threads = std::stoi(arg.substr(kThreadCmd.length()));
		if (threads <= 0) {
		    throw std::invalid_argument("Thread count must be a positive integer.");
		    return false;
		}
	    } catch (const std::invalid_argument& e) {
		std::cerr << "Error: Invalid thread count provided. " 
			  << "Please provide a valid integer.\n";
		return false;
	    }
	    is_threads_set = true;
	}
	else {
	    std::cerr << "Unknown argument: " << arg << "\n";
	    return false;
	}
    }
    return is_pattern_set && is_extensions_set && is_threads_set;
}

