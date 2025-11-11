/*
    Reference: http://www.drdobbs.com/article/print?articleId=184403745
*/

#pragma once

#include "archiver.hpp"

#ifdef NDEBUG

#define ASSERT(expr)                         \
    if (true)                                \
        ;                                    \
    else                                     \
        struct local_t {                     \
            local_t(const asserter_t<>&) { } \
        } local_obj = asserter_t<>(false)

template <typename T = void>
class asserter_t {
public:
    asserter_t(bool = false) { }

    template <class U>
    const asserter_t operator()(const U&) const { return asserter_t(); }
};

#else

#define SMART_ASSERT_A(x) SMART_ASSERT_OP(x, B)
#define SMART_ASSERT_B(x) SMART_ASSERT_OP(x, A)
#define SMART_ASSERT_OP(x, next) SMART_ASSERT_A.print_current_val((x), #x).SMART_ASSERT_##next

#ifndef TARGET_TEST
#define TARGET_TEST 0
#endif

#if !(TARGET_TEST) || !defined(CONTINUE_ON_FAILURE)
#define CONTINUE_ON_FAILURE 0
#endif

#define ASSERT(expr)                                                              \
    if (!(TARGET_TEST) && (expr))                                                 \
        ;                                                                         \
    else                                                                          \
        struct local_t {                                                          \
            local_t(const asserter_t<>& o)                                        \
            {                                                                     \
                if (!(CONTINUE_ON_FAILURE) && !(o.pass())) {                      \
                    o.on_failure();                                               \
                }                                                                 \
            }                                                                     \
        } local_obj = asserter_t<>(bool(expr))                                    \
                          .print_message(__FILE__, __LINE__, __FUNCTION__, #expr) \
                          .archive_result()                                       \
                          .SMART_ASSERT_A

template <typename T = void>
struct asserter_t final {
    asserter_t(bool);

    bool pass() const;
    void on_failure() const;
    const asserter_t& print_message(
        const char* file,
        int line,
        const char* function,
        const char* = "") const;

    const asserter_t& archive_result() const;

    template <class U>
    const asserter_t& print_current_val(const U&, const char*) const;

    asserter_t& SMART_ASSERT_A;
    asserter_t& SMART_ASSERT_B;

private:
    const bool m_value;
};

#include "asserter.hxx"

#endif // NDEBUG
