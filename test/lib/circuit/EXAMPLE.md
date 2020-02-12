const fs = require('fs'),
  path = require('path'),
  tbt = "```";

template = `
## Example
${tbt}
#include <tmp/src/test.h>

#include <lib/circuit/src/index.h>

using namespace std;
using namespace om636::circuit;

int main()
{
    CircuitStack<int> s;
	
    s.push(88);
    s.push(77);

    int i;
    s.wait_pop(i);
    if (s.check_pop(i)) {
    
    }
}
${tbt}
`;
