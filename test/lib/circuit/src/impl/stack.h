#pragma once

#include <stack>

namespace om636 {
namespace circuit {

    template <typename T>
    struct StackPolicy {
        typedef T value_type;

        template <class U>
        static void on_copy(U& lhs, const U& rhs)
        {
            ASSERT(lhs.is_locked());
            ASSERT(rhs.is_locked());
            lhs.m_stack = rhs.m_stack;
        }

        template <class U>
        static void on_init(U& lhs, U&& rhs)
        {
            ASSERT(lhs.is_locked());
            ASSERT(rhs.is_locked());
            lhs.m_stack = std::move(rhs.m_stack);
        }

        template <class U>
        static void on_swap(U& lhs, U& rhs)
        {
            ASSERT(lhs.is_locked());
            ASSERT(rhs.is_locked());
            lhs.m_stack.swap(rhs.m_stack);
        }

        template <class U>
        static void on_pop(U& lhs, value_type& v)
        {
            ASSERT(lhs.is_locked());
            v = std::move(lhs.m_stack.top());
            lhs.m_stack.pop();
        }

        template <class U>
        static void on_push(U& lhs, value_type&& v)
        {
            ASSERT(lhs.is_locked());
            lhs.m_stack.push(std::move(v));
        }

        template <class U>
        static bool on_empty(U& h)
        {
            ASSERT(h.is_locked());
            return h.m_stack.empty();
        }

    private:
        std::stack<value_type> m_stack;
    };

} // circuit
} // om636
