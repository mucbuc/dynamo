
#define CONTINUE_ON_FAILURE 1

#include <asserter/src/test.hpp>

int main()
{
    int i = 3;
    ASSERT(i == 2)(i);
    ASSERT(i == 4)(i);

    return 0;
}
