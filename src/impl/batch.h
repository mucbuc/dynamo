#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "../interface.h"
#include "agent.h"

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
        void kill_invoke(T...) override;
        void kill() override;
	bool is_dead() const override;

        typedef std::weak_ptr<typename agent_type::element_type> pointer_type;
        typedef std::vector<pointer_type> batch_type;
        batch_type& elements();
        const batch_type& elements() const;

    private:
        batch_type m_elements;
        batch_type m_elements_traverse;
    };

    namespace utils {

        template <typename T, typename... V>
        void process_and_kill(T&&, V...);

        template <typename T, typename... V>
        void process(T&&, V...);

        template <typename T>
        void kill_all(T&);

        struct empty_base {
            virtual ~empty_base() = default;
        };
    }

} //control
} // om636

#include "batch.hxx"
