#include <tmp/src/test.h>

#include <lib/dynamo/src/factory.h>
#include <lib/dynamo/src/interface.h>

int main()
{
    auto b = om636::control::make_stack<int>();

    int sum { 0 };

    auto q = b->hook([&](int i) { sum += i; });
    auto p = b->hook([&](int i) { sum *= i; });
    b->invoke(5);
    ASSERT(sum == 25);
    return 0;
}
