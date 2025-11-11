#include <lib/asserter/src/test.hpp>

#include <lib/circuit/src/interface.hpp>
#include <lib/circuit/src/index.hpp>


using namespace std;
using namespace om636::circuit;

int main()
{
    auto s = make_stack<int>();

    s->push(88);
    s->push(77);

    int i(0);
    s->wait_pop(i);
    ASSERT(i == 77);
    if (s->check_pop(i)) {
        ASSERT(i == 88);
    }
}
