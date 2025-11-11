#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#include <cassert>
#endif

// /////////////////////////////////////////////////////////////////////////////////////////////
// // asserter_t
// /////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
template <class U>
const asserter_t<T>& asserter_t<T>::print_current_val(const U& value, const char* message) const
{
    std::cout << message << ": " << value << std::endl;
    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
asserter_t<T>::asserter_t(bool value)
    : SMART_ASSERT_A { *this }
    , SMART_ASSERT_B { *this }
    , m_value(value)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool asserter_t<T>::pass() const
{
    return m_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void asserter_t<T>::on_failure() const
{
#ifdef __EMSCRIPTEN__
    emscripten_force_exit(1);
#else
    assert(false);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
const asserter_t<T>& asserter_t<T>::print_message(
    const char* file,
    int line,
    const char* function,
    const char* message) const
{
    static const char* code_red("\x1b[31m");
    static const char* code_reset("\x1b[39;49m");

    using namespace std;

    if (pass()) {
        cout << "assertion passed: " << message << endl
             << "file: " << file << endl
             << "line: " << line << endl
             << "function: " << function << endl;
    } else {
        cout << code_red
             << "assertion failed: " << message << endl
             << "file: " << file << endl
             << "line: " << line << endl
             << "function: " << function
             << code_reset << endl;
    }
    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
const asserter_t<T>& asserter_t<T>::archive_result(
    const char* file,
    int line,
    const char* function,
    const char* message) const
{
    auto& a(private_assert::archiver<>::instance());
    if (pass()) {
        a.pass();
    } else {
        a.fail(file, line, function, message);
    }
    return *this;
}
