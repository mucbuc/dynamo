# circuit

Syncronize container operations for single objects

## Interface
```
#pragma once

namespace om636 {
namespace circuit {

    template <class T>
    struct Circuit {
        typedef T value_type;

        virtual ~Circuit() = default;
        virtual void push(value_type&&) = 0;
        virtual bool check_pop(value_type&) = 0;
        virtual void wait_pop(value_type&) = 0;
        virtual Circuit* clone() const = 0;
    };

} // circuit
} // om636

```


## Example
```
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
```

