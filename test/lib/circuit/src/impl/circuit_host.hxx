namespace om636 {
namespace circuit {

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T, template <typename> class U>
    CircuitHost<T, U>::CircuitHost(CircuitHost&& rhs)
    {
        lock_type lock(m_mutex);
        policy_type::on_init(*this, rhs);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T, template <typename> class U>
    CircuitHost<T, U>& CircuitHost<T, U>::operator=(CircuitHost rhs)
    {
        swap(rhs);
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T, template <typename> class U>
    void CircuitHost<T, U>::swap(CircuitHost& rhs)
    {
        if (this == &rhs)
            return;

        typedef std::unique_lock<mutex_type> lock_type;

        lock_type left_lock(m_mutex, std::defer_lock);
        lock_type right_lock(rhs.m_mutex, std::defer_lock);
        std::lock(left_lock, right_lock);

        policy_type::on_swap(*this, rhs);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T, template <typename> class U>
    bool CircuitHost<T, U>::empty() const
    {
        lock_type lock(m_mutex);
        return policy_type::on_empty(*this);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T, template <typename> class U>
    bool CircuitHost<T, U>::is_locked() const
    {
        bool result(false);
        std::thread([this, &result]() {
            result = m_mutex.try_lock();
	    if (result) {
	        m_mutex.unlock();
            }
        }).join();
        return !result;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T, template <typename> class U>
    void CircuitHost<T, U>::push(value_type&& v)
    {
        lock_type lock(m_mutex);

        policy_type::on_push(*this, std::move(v));
        m_condition.notify_one();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T, template <typename> class U>
    bool CircuitHost<T, U>::check_pop(value_type& value)
    {
        lock_type lock(m_mutex);

        if (policy_type::on_empty(*this))
            return false;

        policy_type::on_pop(*this, value);
        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T, template <typename> class U>
    void CircuitHost<T, U>::wait_pop(value_type& value)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_condition.wait(lock, [this] { return !policy_type::on_empty(*this); });
        policy_type::on_pop(*this, value);
    }
} // circuit
} // om636
