namespace om636 {
namespace control {

    /////////////////////////////////////////////////////////////////////////////////////
    // shared_agent
    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    template <typename V>
    shared_agent<T...>::shared_agent(V&& callback)
        : m_callback(callback)
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    bool shared_agent<T...>::invoke(T... args)
    {
        if (!is_dead()) {
            m_callback(args...);
	    return !is_dead();
	}
        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    void shared_agent<T...>::kill_invoke(T... args)
    {
        if (!is_dead()) {
            callback_type temp(m_callback);
            kill();
            temp(args...);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    void shared_agent<T...>::kill()
    {
        m_callback = callback_type();
    }

    /////////////////////////////////////////////////////////////////////////////////////
    template <typename... T>
    bool shared_agent<T...>::is_dead()
    {
        return !m_callback;
    }

} //control
} // om636amespace om636 {
