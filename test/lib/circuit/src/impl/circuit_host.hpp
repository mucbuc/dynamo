#pragma once

#include <condition_variable>
#include <mutex>

#include "../interface.hpp"

namespace om636 {
namespace circuit {

    template <typename T, template <typename> class U>
    struct CircuitHost
        : Circuit<T>,
          U<T> {
        typedef Circuit<T> base_type;
        using typename base_type::value_type;

        CircuitHost() = default;
        CircuitHost(const CircuitHost&);
        CircuitHost(CircuitHost&&);
        CircuitHost& operator=(CircuitHost);

        void swap(CircuitHost&);
        bool empty() const;

        ~CircuitHost() override = default;
        void push(value_type&&) override;
        bool check_pop(value_type&) override;
        void wait_pop(value_type&) override;
        std::shared_ptr<base_type> clone() const override;

    private:
        typedef U<T> policy_type;
        typedef std::mutex mutex_type;
        typedef std::lock_guard<mutex_type> lock_type;
        
        mutable mutex_type m_mutex;
        std::condition_variable m_condition;
    };

} // circuit
} // om636

#include "circuit_host.hxx"
