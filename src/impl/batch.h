#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include <lib/circuit/src/index.h>

#include "../interface.h"

namespace om636 {
namespace control {
    template <typename... T>
    class BatchImpl : public Batch<T...> {
    public:
        typedef Batch<T...> base_type;
        using typename base_type::agent_type;
        using typename base_type::function_type;

        ~BatchImpl() override = default;
        agent_type hook(function_type) override;
        void invoke(T...) override;
        void invoke_once(T...) override;

        typedef std::weak_ptr<typename agent_type::element_type> pointer_type;
        typedef twice_size::CircuitQueue<pointer_type> batch_type;
        batch_type& elements();
        const batch_type& elements() const;

    private:
        template <typename U>
        void invoke(U, T...);

        batch_type m_elements;
    };

} //control
} // om636

#include "batch.hxx"
