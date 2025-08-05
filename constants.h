#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string_view>
#include <unordered_set>

constexpr std::string_view kHelpCmd = "--help";
constexpr std::string_view kPatternCmd = "--pattern=";
constexpr std::string_view kExtensionCmd = "--extensions=";
constexpr std::string_view kThreadCmd = "--threads=";
constexpr std::string_view kDetailsCmd = "--details";
constexpr const char* kInvalidArgsMsg = "Invalid arguments. Use --help for usage.\n";
constexpr const char* kWatchThreadsMsg = "=== WATCH THE THREADS MULTY ===\n";
constexpr const char* kWowMsg = "\n===WOW===\n";
constexpr const char* kOopsMsg = "===No game, find something else===\n";

static const std::unordered_set<std::string> allowed_exts = {
    "c", "cpp", "h", "json", "txt", "md"
};

#endif // CONSTANTS_H
