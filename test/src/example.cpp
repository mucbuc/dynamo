#include <lib/asserter/src/asserter.hpp>
#include <lib/dynamo/src/impl/batch.hpp>
#include <lib/dynamo/src/interface.hpp>

int main()
{
    auto b = om636::control::make_queue<int>();

    int sum{ 0 };

    auto q = b->hook([&](int i) { sum += i; });
    auto p = b->hook([&](int i) { sum *= i; });
    b->invoke(5);
    ASSERT(sum == 25);
    return 0;
}
