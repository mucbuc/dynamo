#pragma once

#include "impl/batch.h"

#include <lib/circuit/src/impl/queue.h>
#include <lib/circuit/src/impl/stack.h>

namespace om636 {

namespace control {
    template <typename... T>
    std::shared_ptr<Batch<T...>> make_queue()
    {
        return std::make_shared<BatchImpl<om636::circuit::QueuePolicy, T...>>();
    }

    template <typename... T>
    std::shared_ptr<Batch<T...>> make_stack()
    {
        return std::make_shared<BatchImpl<om636::circuit::StackPolicy, T...>>();
    }

}

}
