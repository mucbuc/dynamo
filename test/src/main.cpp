#include <functional>
#include <iostream>

#include <lib/asserter/src/test.hpp>
#include <lib/dynamo/src/impl/batch.hpp>

#include "batch.hpp"

int main(int argc, const char* argv[])
{
    check_traverse();
    check_unhook_while_traverse();
    check_traverse_while_traverse();
    check_traverse_with_arg();
    check_traverse_with_args();
    dead_agent_removal();
    return 0;
}
