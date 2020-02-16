namespace om636 {
namespace control {
    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    auto BatchImpl<T...>::hook(function_type callback) -> agent_type
    {
        auto agent(std::make_shared<function_type>(callback));
        impl_ref().push(std::make_tuple<pointer_type, bool>(agent, true));
        return agent;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    auto BatchImpl<T...>::hook_once(function_type callback) -> agent_type
    {
        auto agent(std::make_shared<function_type>(callback));
        impl_ref().push(std::make_tuple<pointer_type, bool>(agent, false));
        return agent;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    void BatchImpl<T...>::invoke(T... arg)
    {
        batch_type traverse;
        traverse.swap(impl_ref());
        tuple_type agent;
        while (traverse.check_pop(agent)) {
            agent_type s(std::get<0>(agent).lock());
            if (s) {
                (*s)(arg...);
            }
            s = std::get<0>(agent).lock();
            if (s && std::get<1>(agent)) {
                impl_ref().push(std::move(agent));
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    auto BatchImpl<T...>::impl_ref() -> batch_type&
    {
        return m_impl;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    auto BatchImpl<T...>::impl_ref() const -> const batch_type&
    {
        return m_impl;
    }
} // control
} // om636
