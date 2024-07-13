#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <format>
#include <c++/29/experimental/smart_view_vector>

int main() {
    FILE* pipe = popen("env", "r");

    char buffer[128];
    std::stringstream ss;

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        ss << buffer;
    }

    std::vector<std::pair<std::string, std::string>> env;
    std::string line;

    // Define critical environment variables to display
    const std::vector<std::string> criticality_name = {
        "HOSTTYPE", "USER", "HOME", "COLORTERM", "NAME", "TERM", 
        "LANG", "SHELL", "PWD",
        "WAYLAND_DISPLAY",
        "XDG_RUNTIME_DIR", "XDG_DATA_DIRS",
    };

    // Define formatting labels for specific variables
    const std::vector<std::pair<std::string, std::string>> format_label = {
        std::pair{"COLORTERM", "color term"},
        std::pair{"WAYLAND_DISPLAY", "wayland display"},
        std::pair{"XDG_RUNTIME_DIR", "XDG_RUNTIME_DIR"},
        std::pair{"XDG_DATA_DIRS", "XDG_DATA_DIRS"},
        std::pair{"LANG", "language"},
        std::pair{"HOSTTYPE", "host type"},
    };

    // Parse environment variables from the output of 'env' command
    while (std::getline(ss, line, '\n')) {
        size_t pos = line.find('=');

        if (pos != std::string::npos) {
            std::string var_name = line.substr(0, pos);
            std::string var_value = line.substr(pos + 1);

            // Check if the variable is in the criticality list
            if (smart_view_vector::includes(criticality_name, var_name)) {
                env.emplace_back(var_name, var_value);
            }
        }
    }

    // Prepare output text
    std::vector<std::string> text;

    // Iterate through critical environment variables
    for (const std::string& label: criticality_name) {
        // Find the corresponding environment variable
        auto pair_env = std::find_if(env.begin(), env.end(), [&label](const std::pair<std::string, std::string>& pair) {
            return pair.first == label;
        });

        // If found, format the output based on formatting labels
        if (pair_env != env.end()) {
            auto pair_fmt = std::find_if(format_label.begin(), format_label.end(), [&pair_env](const std::pair<std::string, std::string>& pair) {
                return pair.first == pair_env->first;
            });

            if (pair_fmt != format_label.end()) {
                text.push_back(std::format("{0}: {1}", pair_fmt->second, pair_env->second));
            } else {
                // Convert the variable name to lowercase if no format label is found
                std::transform(pair_env->first.begin(), pair_env->first.end(), pair_env->first.begin(), tolower);
                text.push_back(std::format("{0}: {1}", pair_env->first, pair_env->second));
            }
        }
    }

    // Print formatted environment variables
    for (const std::string& line: text) {
        std::cout << line << std::endl;
    }

    return 0;
}
