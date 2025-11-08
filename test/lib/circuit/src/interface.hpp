#pragma once

#include <memory>

namespace om636 {
namespace circuit {

    template <class T>
    struct Circuit {
        typedef T value_type;

        virtual ~Circuit() = default;
        virtual void push(value_type&&) = 0;
        virtual bool check_pop(value_type&) = 0;
        virtual void wait_pop(value_type&) = 0;
        virtual std::shared_ptr<Circuit> clone() const = 0;
    };

    template <typename T>
    std::shared_ptr<Circuit<T>> make_stack();

    template <typename T>
    std::shared_ptr<Circuit<T>> make_queue();

} // circuit
} // om636
