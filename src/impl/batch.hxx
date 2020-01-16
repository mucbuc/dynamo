namespace om636 {
namespace control {
    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    auto BatchImpl<T...>::hook(function_type callback) -> agent_type
    {
        auto agent(std::make_shared<function_type>(callback));
        m_elements.push(agent);
        return agent;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    void BatchImpl<T...>::invoke(T... arg)
    {
        batch_type traverse;
        traverse.swap(elements());
        pointer_type agent;
        while (traverse.check_pop(agent)) {
            auto s(agent.lock());
            if (s) {
                (*s)(arg...);
                elements().push(s);
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    auto BatchImpl<T...>::elements() -> batch_type&
    {
        return m_elements;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    auto BatchImpl<T...>::elements() const -> const batch_type&
    {
        return m_elements;
    }
} // control
} // om636
