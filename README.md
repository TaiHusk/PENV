# PENV
This is a simple C++ program that prints out certain critical environment variables in a formatted way.

**Features:**
- **Retrieves environment variables using the `env` command.**
- **Parses the output of the `env` command and extracts relevant information.**
- **Displays a formatted list of environment variables.**
- **Includes formatting labels for specific variables, improving readability.**

**Prerequisites:**
- **C++17 or later:** The code utilizes modern C++ features like `std::format`.
- **`smart_view_vector`:** This header file is part of the experimental C++29 standard. You can find it in the [CXX29 / C++ 29](https://github.com/TaiHusk/CXX29) repository.
- `env` command available (part of most Unix-like systems)

**How to Compile and Run:**

1. **Install the `smart_view_vector` header file:**
   - Download the header file from the [TaiHusk/CXX29](https://github.com/TaiHusk/CXX29) repository.
   - Place the header file in your project directory or include it in your compiler's include path.
2. **Compile the code:**
   ```bash
   g++ -o runner -std=c++20 ./src/main.cpp
   ```
3. **Run the executable:**
   ```bash
   ./runner
   ```

**Output:**

The program will display a formatted list of critical environment variables, such as:

```
host type: Linux
user: your_username
home: /home/your_username
color term: xterm-256color
name: your_computer_name
term: xterm
language: en_US.UTF-8
shell: /bin/bash
pwd: /home/your_username
wayland display: wayland-0
XDG_RUNTIME_DIR: /run/user/1000
XDG_DATA_DIRS: /usr/local/share:/usr/share
```

## Dependencies

This program uses the following dependencies:

- `<cstdio>`: For file operations (`popen`, `pclose`, `FILE`, etc.)
- `<iostream>`: For standard input/output streams (`std::cout`, `std::endl`, etc.)
- `<sstream>`: For string stream operations (`std::stringstream`)
- `<string>`: For string manipulation (`std::string`)
- `<vector>`: For dynamic array operations (`std::vector`)
- `<format>`: For string formatting (`std::format`)
- `<c++/29/experimental/smart_view_vector>`: For the `smart_view_vector::includes` function (from the C++29 experimental std)

## **Customization:**

- **Modify the `criticality_name` vector:** Add or remove environment variables to customize the output.
- **Add or change formatting labels in the `format_label` vector:** Improve the readability of the output.

## **Note:**

- The program uses the `popen` function to execute the `env` command. This function may not be available on all platforms.
- The output may vary depending on your system configuration.
- The program uses the `smart_view_vector` class from the `C++29` standard library, which is part of the experimental features. This may not be available on all platforms.

