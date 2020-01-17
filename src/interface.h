#pragma once

#include <functional>
#include <memory>

namespace om636 {
namespace control {

    template <typename... T>
    class Batch {
    public:
        typedef std::function<void(T...)> function_type;
        typedef std::shared_ptr<function_type> agent_type;
        typedef agent_type listener_type;

        virtual ~Batch() = default;
        virtual agent_type hook(function_type) = 0;
        virtual void invoke(T...) = 0;
        virtual void invoke_once(T...) = 0;
    };

} // control
} // om636
