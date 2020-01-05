#pragma once 

#include <memory>

namespace om636 {
namespace control {

    template <typename... T>
    struct Agent {
        virtual ~Agent() = default;
        virtual void invoke(T...) = 0;
        virtual void kill_invoke(T...) = 0;
        virtual void kill() = 0;
	virtual bool is_dead() const = 0;
    };

    template <typename... T>
    class Batch : public Agent<T...> {
    public:
        typedef std::shared_ptr<Agent<T...>> agent_type;
	typedef agent_type listener_type;
        typedef std::function<void(T...)> function_type;

        virtual ~Batch() = default;
        virtual agent_type hook(function_type) = 0;
    };

} // control
} // om636
