#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <set>
#include <string>

// Function declarations
void print_help();
bool parse_extensions(std::string &extensionStr, std::set<std::string>& extensions);
bool parse_args(int argc, char* argv[], std::string& pattern, std::set<std::string>& extensions, int& threads, bool& show_details);

#endif // ARG_PARSER_H
