# Mugen Def Parser

**Mugen Def Parser** is an open-source library for parsing MUGEN character's DEF file format for C++.

## Platforms

- Windows (MSVC / clang / MinGW clang)
- Linux (clang)

## Install

### with CMake (recommended)

Add the following to your `CMakeLists.txt`.

```cmake
include(FetchContent)
FetchContent_Declare(
  mdefparser
  GIT_REPOSITORY https://github.com/HalkazeMUGEN/mdefparser.git
  GIT_TAG v1.0.3
)
FetchContent_MakeAvailable(mdefparser)

target_link_libraries(<target> mdefparser)
```

### without any build tools

Copy the include [folder](https://github.com/HalkazeMUGEN/mdefparser/tree/main/include) to your include folder.

Then, define the macro as follows when you include it.

```c
#define MDEFPARSER_HEADER_ONLY
#include <mdefparser/mdefparser.h>
```

See also [examples](https://github.com/HalkazeMUGEN/mdefparser/tree/main/example).

## Usage samples

### Parse all items

```cpp
#include <mdefparser/mdefparser.h>

void parse_example(const std::filesystem::path& path) {
  try {
    auto parser = mugen::def::DefParserWin{};
    auto def = parser.parse(path);
    
    std::cout << def.info.name << std::endl;
    std::cout << *(def.info.displayname) << std::endl;
  } catch (const std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
  }
}
```

### Parse single item

```cpp
#include <mdefparser/mdefparser.h>

void parse_item_example(const std::filesystem::path& path) {
  try {
    auto parser = mugen::def::DefParserWin{};
    auto author = parser.parse_item<mugen::def::DefParseKey::Author>(path);

    std::cout << author << std::endl;
  } catch (const std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
  }
}
```


See also [examples](https://github.com/HalkazeMUGEN/mdefparser/tree/main/example).

## License

This project is licensed under the terms of the [GNU General Public License v3.0 or later](https://www.gnu.org/licenses/gpl-3.0.html).

You can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
