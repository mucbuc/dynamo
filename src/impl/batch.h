#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include <lib/circuit/src/impl/circuit_host.h>

#include "../interface.h"

namespace om636 {
namespace control {

    template <template <typename> typename P, typename... T>
    class BatchImpl : public Batch<T...> {
    public:
        typedef Batch<T...> base_type;
        using typename base_type::agent_type;
        using typename base_type::function_type;

        ~BatchImpl() override = default;
        agent_type hook(function_type) override;
        agent_type hook_once(function_type) override;
        void invoke(T...) override;

        typedef std::weak_ptr<typename agent_type::element_type> pointer_type;
        typedef std::tuple<pointer_type, bool> tuple_type;
        typedef circuit::CircuitHost<tuple_type, P> batch_type;
        batch_type& impl_ref();
        const batch_type& impl_ref() const;

    private:
        template <typename U>
        void invoke(U, T...);

        batch_type m_impl;
    };

} //control
} // om636

#include "batch.hxx"
