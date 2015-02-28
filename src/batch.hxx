namespace om636
{
	namespace control
	{        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		auto Batch<T>::hook( callback_type c ) -> listener_type
		{
            pointer_type agent( new agent_type( c ) );
            m_elements_add.insert( agent );
			return listener_type( agent );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		void Batch<T>::unhook()
		{
            utils::kill_all( elements() );
            utils::kill_all( m_elements_add );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		void Batch<T>::traverse()
		{
            merge_added_elements();

            utils::process( elements() );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		template<class V>
		void Batch<T>::traverse(V arg)
		{
            merge_added_elements();

            utils::process( elements(), arg );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		template<typename V, typename W>
		void Batch<T>::traverse(V first_arg, W second_arg )
		{
            merge_added_elements();

            utils::process( elements(), first_arg, second_arg );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        void Batch<T>::traverse_destructive()
        {
            merge_added_elements();

            utils::process_and_kill( elements() );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        template<class V>
        void Batch<T>::traverse_destructive(V arg)
        {
            merge_added_elements();

            utils::process_and_kill( elements(), arg );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        template<typename V, typename W>
        void Batch<T>::traverse_destructive(V first_arg, W second_arg )
        {
            merge_added_elements();

            utils::process_and_kill( elements(), first_arg, second_arg );
        }

        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        auto Batch<T>::elements() -> batch_type &
        {
            return m_elements;
        }

        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        auto Batch<T>::elements() const -> const batch_type &
        {
            return m_elements;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        void Batch<T>::merge_added_elements()
        {
            elements().insert(m_elements_add.begin(), m_elements_add.end() );
            m_elements_add.clear();
        }

        namespace utils
        {
            /////////////////////////////////////////////////////////////////////////////////////
    		template<typename T>
            void process( T & elements ) 
            {
                T copy(elements);
                for_each( copy.begin(), copy.end(), [&](typename T::value_type p) {
                    if (!p->is_dead())
                        p->invoke();
                    else
                        elements.erase(p);
                } );
            }
            
            /////////////////////////////////////////////////////////////////////////////////////
    		template<typename T, typename V>
            void process( T & elements, V v )
            {
                T copy(elements);
                for_each( copy.begin(), copy.end(), [&](typename T::value_type p) {
                    if (!p->is_dead())
                        p->invoke(v);
                    else
                        elements.erase(p);
                } );
            }
            
            /////////////////////////////////////////////////////////////////////////////////////
    		template<typename T, typename V, typename W>
            void process( T & elements, V v, W w )
            {
                T copy(elements);
                for_each( copy.begin(), copy.end(), [&](typename T::value_type p) {
                    if (!p->is_dead())
                        p->invoke(v, w);
                    else
                        elements.erase(p);
                } );
            }
            
            /////////////////////////////////////////////////////////////////////////////////////
    		template<typename T>
            void process_and_kill( T & elements )
            {
                T copy(elements);
                for_each( copy.begin(), copy.end(), [](typename T::value_type p) {
                    if (!p->is_dead())
                        p->kill_invoke();
                } );
                elements.clear();
            }
            
            /////////////////////////////////////////////////////////////////////////////////////
    		template<typename T, typename V>
            void process_and_kill( T & elements, V v )
            {
                T copy(elements);
                for_each( copy.begin(), copy.end(), [&](typename T::value_type p) {
                    if (!p->is_dead())
                       p->kill_invoke(v);
                } );
                elements.clear();
            }
            
            /////////////////////////////////////////////////////////////////////////////////////
    		template<typename T, typename V, typename W>
            void process_and_kill( T & elements, V v, W w )
            {
                T copy(elements);
                for_each( copy.begin(), copy.end(), [&](typename T::value_type p) {
                    if (!p->is_dead())
                        p->kill_invoke(v, w);
                } );
                elements.clear();
            }
            
            /////////////////////////////////////////////////////////////////////////////////////
            template<typename T>
            void kill_all(T & elements)
            {
                for_each( elements.begin(), elements.end(), [](typename T::value_type p) {
                    p->kill();
                } );
                elements.clear();
            }
        }   // utils        
    } 	// control 
}	// om636