namespace om636 {
namespace control {
    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    auto BatchImpl<T...>::hook(function_type callback) -> agent_type
    {
        auto agent(std::make_shared<shared_agent<T...>>(callback));
        m_elements.push(agent);
        return agent;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    void BatchImpl<T...>::invoke(T... arg)
    {
	m_elements_traverse = std::move(elements());
        pointer_type agent;
	while (m_elements_traverse.check_pop(agent))
	{
 	    auto s(agent->lock());
            if (s) {
                s->invoke(v...);
		if (!s->is_dead()) {
		    elements().push(agent);
		}
            }
 	}		
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename ... T>
    bool BatchImpl<T...>::is_dead() const
    {
        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    void BatchImpl<T...>::kill_invoke(T... arg)
    {
        utils::process_and_kill(std::move(m_elements), arg...);
    }
 
    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    void BatchImpl<T...>::kill()
    {
        utils::kill_all(elements());
        utils::kill_all(m_elements_traverse);
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

    namespace utils {

        /////////////////////////////////////////////////////////////////////////////////////
        template <typename T, typename... V>
        void process(T&& elements, V... v)
        { 
            T copy(std::move(elements));
            for(auto i = copy.begin(); i != copy.end(); ++i)
	    {
                auto s(i->lock());
                if (s) {
                    s->invoke(v...);
                }
	    }
        }

        /////////////////////////////////////////////////////////////////////////////////////
        template <typename T, typename... V>
        void process_and_kill(T&& elements, V... v)
        {
            T copy(std::move(elements));
	    for(auto i = copy.begin(); i != copy.end(); ++i)
	    {
                auto s(i->lock());
                if (s) {
                    s->kill_invoke(v...);
                }
	    }
        }

        /////////////////////////////////////////////////////////////////////////////////////
        template <typename T>
        void kill_all(T& elements)
        {
            for_each(elements.begin(), elements.end(), [](typename T::value_type p) {
                auto s(p.lock());
                if (s) {
                    s->kill();
                }
            });
            elements.clear();
        }
    } // utils
} // control
} // om636
