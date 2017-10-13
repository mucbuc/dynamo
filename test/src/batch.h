using namespace om636;
using namespace std;

typedef std::function<void()> callback_type;
typedef control::Batch<callback_type> batch_type;

void check_traverse_with_arg()
{
    typedef function<void(int)> callback_type;
    typedef control::Batch<callback_type> batch_type;

    unsigned test_passed(0);
    batch_type batch;

    auto p(batch.hook([&](int i) {
        ASSERT(i == 99);
        ++test_passed;
    }));

    batch.traverse(99);

    ASSERT(test_passed == 1);
    FOOTER;
}

void check_traverse_with_args()
{
    typedef function<void(int, int)> callback_type;
    typedef control::Batch<callback_type> batch_type;

    unsigned test_passed(0);
    batch_type batch;

    auto p(batch.hook([&](int i, int j) {
        ASSERT(i == 99);
        ASSERT(j == 3);
        ++test_passed;
    }));

    batch.traverse(99, 3);

    ASSERT(test_passed == 1);
    FOOTER;
}

void check_traverse_while_traverse()
{
    batch_type batch;
    unsigned passed(0);

    auto p(batch.hook([&]() {
        ++passed;
        batch.traverse();
    }));

    batch.traverse();

    ASSERT(passed == 1);
    FOOTER;
}

void check_traverse()
{
    batch_type batch;
    unsigned passed(0);

    auto temp(batch.hook([&]() {
        ++passed;
    }));

    batch.traverse();
    batch.traverse();

    ASSERT(passed == 2);
    FOOTER;
}