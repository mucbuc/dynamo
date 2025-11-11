#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
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
template <typename O>
bool archiver<T>::print_results(O& out)
{
    using namespace std;
    out << "{\n";
    out << "  \"passed\": " << m_passed;
    if (m_failed) {
        out << "," << "\n";
        out << "  \"failed\": " << m_failed;
    }
    out << "\n";
    out << "}\n";
    return out.good();
}

template <typename T>
archiver<T>::~archiver()
{
    using namespace std;
    ofstream out(m_results_file);

    if (!out || !print_results(out)) {
        cerr << "Error: archiver failed to open or write to " << m_results_file << ". Writing to std::cerr instead" << endl;
        print_results(cerr);
    }
}

template <class T>
void archiver<T>::pass()
{
    ++m_passed;
}

template <class T>
void archiver<T>::fail()
{
    ++m_failed;
}
} // private_assert
