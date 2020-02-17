namespace om636 {
namespace control {
    /////////////////////////////////////////////////////////////////////////////////////
    template <template <typename> typename P, typename... T>
    auto BatchImpl<P, T...>::hook(function_type callback) -> agent_type
    {
        using namespace std;
        auto agent(make_shared<function_type>(callback));
        impl_ref().push(make_tuple<pointer_type, bool>(agent, true));
        return agent;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <template <typename> typename P, typename... T>
    auto BatchImpl<P, T...>::hook_once(function_type callback) -> agent_type
    {
        using namespace std;
        auto agent(make_shared<function_type>(callback));
        impl_ref().push(make_tuple<pointer_type, bool>(agent, false));
        return agent;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <template <typename> typename P, typename... T>
    void BatchImpl<P, T...>::invoke(T... arg)
    {
        using namespace std;
        batch_type traverse;
        traverse.swap(impl_ref());
        tuple_type agent;
        while (traverse.check_pop(agent)) {
            agent_type s(get<0>(agent).lock());
            if (s) {
                (*s)(arg...);
            }
            s = get<0>(agent).lock();
            if (s && get<1>(agent)) {
                impl_ref().push(move(agent));
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <template <typename> typename P, typename... T>
    auto BatchImpl<P, T...>::impl_ref() -> batch_type&
    {
        return m_impl;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <template <typename> typename P, typename... T>
    auto BatchImpl<P, T...>::impl_ref() const -> const batch_type&
    {
        return m_impl;
    }
} // control
} // om636
