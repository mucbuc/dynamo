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
            kill_all( elements() );
            kill_all( m_elements_add );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		void Batch<T>::traverse()
		{
            merge_new_elements();

            const batch_type & sub( process( elements() ) );
            elements().erase( sub.begin(), sub.end() );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		template<class V>
		void Batch<T>::traverse(V arg)
		{
            merge_new_elements();

            const batch_type & sub( process( elements(), arg ) );
            elements().erase( sub.begin(), sub.end() );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		template<typename V, typename W>
		void Batch<T>::traverse(V first_arg, W second_arg )
		{
            merge_new_elements();

            const batch_type & sub( process( elements(), first_arg, second_arg ) );
            elements().erase( sub.begin(), sub.end() );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        void Batch<T>::traverse_destructive()
        {
            process_and_kill( elements() );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        template<class V>
        void Batch<T>::traverse_destructive(V arg)
        {
            process_and_kill( elements(), arg );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        template<typename V, typename W>
        void Batch<T>::traverse_destructive(V first_arg, W second_arg )
        {
            process_and_kill( elements(), first_arg, second_arg );
        }

        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        auto Batch<T>::process( batch_type batch ) -> batch_type 
        {
            batch_type result;
            for_each( batch.begin(), batch.end(), [&](pointer_type p) {
                if (!p->is_dead())
                    p->invoke();
                else
                    result.insert(p);
            } );
            return result;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        template<typename V>
        auto Batch<T>::process( batch_type batch, V v ) -> batch_type
        {
            batch_type result;
            for_each( batch.begin(), batch.end(), [&](pointer_type p) {
                if (!p->is_dead())
                    p->invoke(v);
                else
                    result.insert(p);
            } );
            return result;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        template<typename V, typename W>
        auto Batch<T>::process( batch_type batch, V v, W w ) -> batch_type
        {
            batch_type result;
            for_each( batch.begin(), batch.end(), [&](pointer_type p) {
                if (!p->is_dead())
                    p->invoke(v, w);
                else
                    result.insert(p);
            } );
            return result;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        void Batch<T>::process_and_kill( batch_type batch )
        {
            for_each( batch.begin(), batch.end(), [](pointer_type p) {
                if (!p->is_dead())
                    p->kill_invoke();
            } );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        template<typename V>
        void Batch<T>::process_and_kill( batch_type batch, V v )
        {
            for_each( batch.begin(), batch.end(), [&](pointer_type p) {
                if (!p->is_dead())
                   p->kill_invoke(v);
            } );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        template<typename V, typename W>
        void Batch<T>::process_and_kill( batch_type batch, V v, W w )
        {
            for_each( batch.begin(), batch.end(), [&](pointer_type p) {
                if (!p->is_dead())
                    p->kill_invoke(v, w);
            } );
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
        void Batch<T>::kill_all(batch_type & batch)
        {
            for_each( batch.begin(), batch.end(), [](pointer_type p) {
                p->kill();
            } );
            batch.clear();
        }

        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        void Batch<T>::merge_new_elements()
        {
            elements().insert(m_elements_add.begin(), m_elements_add.end() );
            m_elements_add.clear();
        }
        
    } 	// control 
}	// om636