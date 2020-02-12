#pragma once

#include "impl/circuit_host.h"
#include "impl/queue.h"
#include "impl/stack.h"

namespace om636 {
namespace circuit {

    template <typename T>
    using CircuitStack = CircuitHost<T, StackPolicy>;

    template <typename T>
    using CircuitQueue = CircuitHost<T, QueuePolicy>;

} // circuit
} // om636
