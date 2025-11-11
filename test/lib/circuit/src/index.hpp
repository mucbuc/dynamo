#pragma once

#include "impl/circuit_host.hpp"
#include "impl/queue.hpp"
#include "impl/stack.hpp"

namespace om636 {
namespace circuit {

    template <typename T>
    using CircuitStack = CircuitHost<T, StackPolicy>;

    template <typename T>
    using CircuitQueue = CircuitHost<T, QueuePolicy>;

    template <typename T>
    std::shared_ptr<Circuit<T>> make_stack()
    {
        return std::make_shared<CircuitStack<T>>();
    }

    template <typename T>
    std::shared_ptr<Circuit<T>> make_queue()
    {
        return std::make_shared<CircuitQueue<T>>();
    }
} // circuit
} // om636
