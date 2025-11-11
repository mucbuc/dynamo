#include <cassert>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>

namespace private_assert {
template <typename T>
auto archiver<T>::instance() -> archiver&
{
    static archiver local;
    return local;
}

template <typename T>
archiver<T>::~archiver()
{
    using namespace std;

    fstream out("result.json", fstream::out);

    out << "{\n";
    out << "\"passed\": " << m_passed;

    if (m_failed.begin() != m_failed.end()) {
        out << "," << endl;

        auto i(m_failed.begin());
        out << "\"failed\": [" << endl
            << *(i++) << endl;
        while (i != m_failed.end())
            out << ", " << *(i++) << endl;
        out << "]" << endl;
    } else {
        out << endl;
    }
    out << "}\n";
}

template <class T>
void archiver<T>::pass()
{
    ++m_passed;
}

template <class T>
void archiver<T>::fail(
    const char* file,
    int line,
    const char* function,
    const char* message)
{
    using namespace std;

    stringstream entry;
    entry << "{" << endl;

    if (strlen(message)) {
        entry << "\"message\":\"" << message << "\"," << endl;
    }
    entry << "\"file\":\"" << file << "\"," << endl;
    entry << "\"function\":\"" << function << "\"," << endl;
    entry << "\"line\":" << line << endl;
    entry << "}" << endl;

    m_failed.push_back(entry.str());
}
} // private_assert
