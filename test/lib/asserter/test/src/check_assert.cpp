#include <string>

#include <asserter/src/asserter.hpp>

int main()
{
    using namespace std;
    string a("hello assert");

    ASSERT(a.empty())(a)(a.size());
    return 0;
}
