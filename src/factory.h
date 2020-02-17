#pragma once

#include "impl/batch.h"

#include <lib/circuit/src/impl/queue.h>
#include <lib/circuit/src/impl/stack.h>

namespace om636 {

namespace control {
    template <typename... T>
    std::shared_ptr<BatchImpl<QueuePolicy, T...>> make_batch()
    {
        return std::make_shared<BatchImpl<QueuePolicy, T...>>();
    }

}

}
