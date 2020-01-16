using namespace om636;
using namespace om636::control;
using namespace std;

void check_unhook_while_traverse()
{
    BatchImpl<> batch;
    unsigned passed(0);

    typename BatchImpl<>::listener_type temp(batch.hook([&]() {
        ++passed;
        temp.reset();
    }));

    batch.invoke();
    batch.invoke();

    ASSERT(passed == 1)
    (passed);
}

void dead_agent_removal()
{
    typedef BatchImpl<int> batch_type;
    batch_type batch;
    batch.hook([](int) {});
    batch.invoke(9);

    ASSERT(batch.elements().empty() && "dead agent removal");
}

void check_traverse_with_arg()
{
    BatchImpl<int> batch;
    int v = 0;
    auto p(batch.hook([&](int i) {
        v = i;
    }));

    batch.invoke(99);

    ASSERT(v == 99);
}

void check_traverse_with_args()
{
    typedef BatchImpl<int, int> batch_type;

    unsigned test_passed(0);
    batch_type batch;

    auto p(batch.hook([&](int i, int j) {
        ASSERT(i == 99);
        ASSERT(j == 3);
        ++test_passed;
    }));

    batch.invoke(99, 3);

    ASSERT(test_passed == 1);
}

void check_traverse_while_traverse()
{
    BatchImpl<> batch;
    unsigned passed(0);

    auto p(batch.hook([&]() {
        ++passed;
        batch.invoke();
    }));

    batch.invoke();

    ASSERT(passed == 1);
}

void check_traverse()
{
    BatchImpl<> batch;
    unsigned passed(0);

    auto temp(batch.hook([&]() {
        ++passed;
    }));

    batch.invoke();
    batch.invoke();

    ASSERT(passed == 2);
}
