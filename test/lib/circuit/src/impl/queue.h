#pragma once

#include <queue>

namespace om636 {
namespace circuit {

    template <typename T>
    struct QueuePolicy {
        typedef T value_type;

        template <class U>
        static void on_init(U& lhs, U&& rhs)
        {
            ASSERT(lhs.is_locked());
            ASSERT(rhs.is_locked());
            lhs.m_queue = std::move(rhs.m_queue);
        }

        template <class U>
        static void on_copy(U& lhs, const U& rhs)
        {
            ASSERT(lhs.is_locked());
            ASSERT(rhs.is_locked());
            lhs.m_queue = rhs.m_queue;
        }

        template <class U>
        static void on_swap(U& lhs, U& rhs)
        {
            ASSERT(lhs.is_locked());
            ASSERT(rhs.is_locked());
            lhs.m_queue.swap(rhs.m_queue);
        }

        template <class U>
        static void on_pop(U& lhs, value_type& v)
        {
            ASSERT(lhs.is_locked());
            v = std::move(lhs.m_queue.front());
            lhs.m_queue.pop();
        }

        template <class U>
        static void on_push(U& lhs, value_type&& v)
        {
            ASSERT(lhs.is_locked());
            lhs.m_queue.push(std::move(v));
        }

        template <class U>
        static bool on_empty(U& h)
        {
            ASSERT(h.is_locked());
            return h.m_queue.empty();
        }

    private:
        std::queue<value_type> m_queue;
    };

} // circuit
} // om636
