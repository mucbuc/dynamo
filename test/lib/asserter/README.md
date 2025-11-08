# asserter

![Verify Assertion Failure](https://github.com/mucbuc/asserter/workflows/Verify%20Assertion%20Failure/badge.svg)

assertion util inspired by John Torjo's solution described [here](https://www.drdobbs.com/cpp/enhancing-assertions/184403745)

## build

see `test/build_and_run`

## standard usage

```
string a("hello assert");

ASSERT(a.empty())(a)(a.size());
```

Example output:
```
assertion failed: a.empty()
file: /Users/mucbuc/work/wgsl_check/ext/asserter/test/src/check_assert.cpp
line: 10
function: main
a: hello assert
a.size(): 12
Assertion failed: (false), function local_t, file check_assert.cpp, line 10.
./build_and_run: line 5: 93154 Abort trap: 6           ./build/Example
```

## test usage

To track passed assertions use `test.hpp` instead of `asserter.hpp`. This will also write a file `result.json` containing number of assertions passed.
