#pragma once

#include <string>
#include <vector>

namespace private_assert {
template <typename T = void>
struct archiver {
    static archiver& instance();

    ~archiver();

    void pass();
    void fail(
        const char*,
        int,
        const char* function,
        const char* = "");

private:
    std::size_t m_passed = 0;
    std::vector<std::string> m_failed;
};
}

#include "archiver.hxx"
