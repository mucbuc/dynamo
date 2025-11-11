#include <memory>
#include <vector>
#include <thread>

#include <lib/asserter/src/test.hpp>
#include <lib/circuit/src/index.hpp>

template <class T>
void test_wait_pop(T s)
{
#ifndef __EMSCRIPTEN__
    auto tmp = std::thread([=]() {
        int i(0);
        s->wait_pop(i);
        ASSERT(i == 99);
    });

    s->push(99);
    tmp.join();
#else
    s->push(99);
    int i(0);
    s->wait_pop(i);
    ASSERT(i == 99);
#endif 
}

template <class T>
void test_ctor_and_swap()
{
    T a, b;
    a.swap(b);
}

int main()
{
    using namespace om636::circuit;

    test_wait_pop(make_stack<int>());
    test_wait_pop(make_queue<int>());
    test_ctor_and_swap<CircuitQueue<int>>();
    test_ctor_and_swap<CircuitStack<int>>();

    return 0;
}
