#include <memory>
#include <vector>

#include <tmp/src/test.h>

#include <lib/circuit/src/index.h>

template <class T>
void test_wait_pop(T s)
{
    auto tmp = std::thread([=]() {
        int i(0);
        s->wait_pop(i);
        ASSERT(i == 99);
    });

    s->push(99);
    tmp.join();
}

int main()
{
    using namespace om636::circuit;

    test_wait_pop(std::make_shared<CircuitStack<int>>());
    test_wait_pop(std::make_shared<CircuitQueue<int>>());


    CircuitQueue<int> a, b;
    a.swap(b);

    return 0;
}
