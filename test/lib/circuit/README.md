# circuit

![Test](https://github.com/mucbuc/circuit/workflows/Test/badge.svg)

Synchronize container operations for single objects

## Interface
```
#pragma once

#include <memory>

namespace om636 {
namespace circuit {

    template <class T>
    struct Circuit {
        typedef T value_type;

        virtual ~Circuit() = default;
        virtual void push(value_type&&) = 0;
        virtual bool check_pop(value_type&) = 0;
        virtual void wait_pop(value_type&) = 0;
        virtual std::shared_ptr<Circuit> clone() const = 0;
    };

    template <typename T>
    std::shared_ptr<Circuit<T>> make_stack();

    template <typename T>
    std::shared_ptr<Circuit<T>> make_queue();

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
    auto s = make_stack<int>();

    s->push(88);
    s->push(77);

    int i(0);
    s->wait_pop(i);
    if (s->check_pop(i)) {
    }
}

```

