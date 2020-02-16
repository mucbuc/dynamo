#pragma once

#include "impl/batch.h"

namespace om636 {

namespace control {
    template <typename... T>
    std::shared_ptr<BatchImpl<dummy, T...>> make_batch()
    {
        return std::make_shared<BatchImpl<dummy, T...>>();
    }

}

}
