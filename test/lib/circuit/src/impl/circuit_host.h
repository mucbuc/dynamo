#pragma once

#include <condition_variable>
#include <mutex>
#include <thread>

#include "../interface.h"

namespace om636 {
namespace twice_size {

    template <typename T, template <typename> class U>
    struct CircuitHost
        : Circuit<T>,
          U<T> {
        typedef Circuit<T> base_type;
        using typename base_type::value_type;

        CircuitHost() = default;
        CircuitHost(CircuitHost&&);
        CircuitHost& operator=(CircuitHost);

        void swap(CircuitHost&);
        bool empty() const;
        bool is_locked() const;

        ~CircuitHost() override = default;
        void push(value_type&&) override;
        bool check_pop(value_type&) override;
        void wait_pop(value_type&) override;

    private:
        typedef U<T> policy_type;
        typedef std::lock_guard<std::mutex> lock_type;
        typedef std::mutex mutex_type;

        mutable mutex_type m_mutex;
        std::condition_variable m_condition;
    };

} // twice_size
} // om636

#include "circuit_host.hxx"
