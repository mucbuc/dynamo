#pragma once

#include "impl/circuit_host.h"
#include "impl/stack.h"
#include "impl/queue.h"

namespace om636 {
namespace twice_size {

template<typename T>
using CircuitStack = CircuitHost<T, StackPolicy>;

template<typename T>
using CircuitQueue = CircuitHost<T, QueuePolicy>;

} // twice_size
} // om636
    
