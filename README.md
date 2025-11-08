# dynamo

![Test](https://github.com/mucbuc/dynamo/workflows/Test/badge.svg)

Dispatch work to agents.

## Interface
```
#pragma once

#include <functional>
#include <memory>

namespace om636 {
namespace control {

    template <typename... T>
    class Batch {
    public:
        typedef std::function<void(T...)> function_type;
        typedef std::shared_ptr<function_type> agent_type;
        typedef agent_type listener_type;

        virtual ~Batch() = default;
        virtual agent_type hook(function_type) = 0;
        virtual agent_type hook_once(function_type) = 0;
        virtual void invoke(T...) = 0;
    };

    template <typename... T>
    std::shared_ptr<Batch<T...>> make_queue();

    template <typename... T>
    std::shared_ptr<Batch<T...>> make_stack();

} // control
} // om636

```

## Example 
```
#include <tmp/src/test.h>

#include <lib/dynamo/src/impl/batch.h>
#include <lib/dynamo/src/interface.h>

int main()
{
    auto b = om636::control::make_queue<int>();

    int sum{ 0 };

    auto q = b->hook([&](int i) { sum += i; });
    auto p = b->hook([&](int i) { sum *= i; });
    b->invoke(5);
    ASSERT(sum == 25);
    return 0;
}

```

### Dependencies

Dynamo uses Circuit for thread syncronization

### Plan

Instead of copy and insert elements inside of invoke, push the elements one by one as they get traversed (obviosly don't add elements that are dead)...

![doc header](https://s3-us-west-2.amazonaws.com/mod-resources/mod-header.svg)
