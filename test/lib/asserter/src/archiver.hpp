#pragma once

#include <string>
#include <vector>

namespace private_assert {
template <typename T = void>
struct archiver {
    static archiver& instance();

    ~archiver();

    void pass();
    void fail();

private:
    std::size_t m_passed = 0;
    std::size_t m_failed = 0;

    template <typename O>
    bool print_results(O&);

    const std::string m_results_file = "result.json";
};
}

#include "archiver.hxx"
