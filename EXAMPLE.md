const fs = require('fs'),
  path = require('path'),
  tbt = "```";

template = `
## Example
${tbt}
#include <tmp/src/test.h>

#include <lib/dynamo/src/factory.h>
#include <lib/dynamo/src/interface.h>

int main()
{
    auto b = om636::control::make_batch<int>();

    int sum { 0 };

    auto q = b->hook([&](int i) { sum += i; });
    auto p = b->hook([&](int i) { sum *= i; });
    b->invoke(5);
    return sum == 25;
}
${tbt}
`;
