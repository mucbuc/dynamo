# asserter

![Verify Assertion Failure](https://github.com/mucbuc/asserter/workflows/Verify%20Assertion%20Failure/badge.svg)

A C++ assertion library that provides rich contextual information when assertions fail. Instead of just telling you *what* failed, asserter shows you the values of all relevant variables, making debugging significantly faster.

Inspired by John Torjo's assertion technique, asserter captures the context around failed assertions, printing variable values, file location, and function name.

## Why Use asserter?

**Standard assertions:**
```cpp
string a("hello assert");
assert(a.empty());  // Just tells you the assertion failed
```

**With asserter:**
```cpp
string a("hello assert");
ASSERT(a.empty())(a)(a.size());  // Shows you WHY it failed
```

Output:
```
assertion failed: a.empty()
file: /Users/mucbuc/work/wgsl_check/ext/asserter/test/src/check_assert.cpp
line: 10
function: main
a: hello assert
a.size(): 12
```

## Features

- 🎯 **Rich Context Capture** - Include additional values when assertions fail
- 🧪 **Test Mode** - Track number of passed/failed assertions with JSON output
- 🔄 **Continue on Failure** - Option to continue execution after assertion failures
- 🚀 **Header-Only** - Easy integration, no separate compilation needed
- 🌐 **Cross-Platform** - Works with native builds and Emscripten

## Quick Start

### Installation

1. Copy the header files to your project
2. Include the appropriate header:
   - For production: `#include "asserter.hpp"`
   - For testing: `#include "test.hpp"`

### Basic Usage

```cpp
#include "asserter.hpp"

int main() {
    std::string name = "Alice";
    int age = 25;
    
    // Chain context values after the assertion
    ASSERT(age >= 18)(name)(age);
    
    // Works with any expression
    std::vector<int> vec = {1, 2, 3};
    ASSERT(!vec.empty())(vec.size());
    
    return 0;
}
```

## Usage Modes

### Standard Mode (`asserter.hpp`)

Use this for production code or when you want assertions to terminate on failure:

```cpp
#include "asserter.hpp"

ASSERT(condition)(context1)(context2)...; 
// Prints context and terminates on failure
```

### Test Mode (`test.hpp`)

Use this for unit tests to track both passed and failed assertions:

```cpp
#include "test.hpp"

void my_test() {
    ASSERT(true)(variable);   // Recorded as passed
    ASSERT(false)(variable);  // Recorded as failed
}
```

Test mode generates a `result.json` file with assertion statistics:
```json
{
    "passed": 42,
    "failed": 0
}
```

### Continue on Failure

To prevent termination on failed assertions (useful for test suites), define `CONTINUE_ON_FAILURE` before including `test.hpp`:

```cpp
#define CONTINUE_ON_FAILURE
#include "test.hpp"

void test_suite() {
    ASSERT(false)(x);  // Logs failure, continues execution
    ASSERT(true)(y);   // Still runs
}
```

The `result.json` output will include both passed and failed assertion counts.

## Building Examples

### Native Build

```bash
cd test
cmake -B build
cmake --build build
```

### Emscripten Build

```bash
cd test
emcmake cmake -B web-build
cmake --build web-build
```

## Requirements

- C++11 or later
- CMake 3.x (for building examples)
- Emscripten (optional, for WebAssembly builds)

## How It Works

The `ASSERT` macro uses operator chaining to capture context:

```cpp
ASSERT(condition)           // Checks the condition
    (variable1)             // Captures variable1 if assertion fails
    (variable2)             // Captures variable2 if assertion fails
    (expression);           // Captures any expression
```

Each chained call adds more context that will be printed if the assertion fails, making it immediately clear what went wrong.

## Example Output

Given this code:
```cpp
string a("hello assert");
ASSERT(a.empty())(a)(a.size());
```

You get this detailed output:
```
assertion failed: a.empty()
file: /Users/mucbuc/work/wgsl_check/ext/asserter/test/src/check_assert.cpp
line: 10
function: main
a: hello assert
a.size(): 12
Assertion failed: (false), function local_t, file check_assert.cpp, line 10.
```

## Contributing

Contributions are welcome! Please feel free to submit issues or pull requests.

## Related Resources

- Inspired by John Torjo's assertion technique described in [this article](https://erdani.org/publications/cuj-08-2003.php.html)

## License

License
This project is licensed under the GNU General Public License v3.0 - see below for details.
Copyright (C) 2025 Mark Busenitz

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
For the full license text, see the LICENSE file or visit https://www.gnu.org/licenses/gpl-3.0.html
