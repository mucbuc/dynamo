#pragma once

#include "impl/circuit_host.h"
#include "impl/queue.h"
#include "impl/stack.h"

namespace om636 {
namespace circuit {

    template <typename T>
    std::shared_ptr<Circuit<T>> make_stack()
    {
        return std::make_shared<CircuitHost<T, StackPolicy>>();
    }

    template <typename T>
    std::shared_ptr<Circuit<T>> make_queue()
    {
        return std::make_shared<CircuitHost<T, QueuePolicy>>();
    }
} // circuit
} // om636
