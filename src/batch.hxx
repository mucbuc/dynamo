namespace om636
{
	namespace control
	{        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		auto Batch<T>::hook( callback_type c ) -> listener_type
		{
            pointer_type agent( new agent_type( c ) );
            m_elements.insert( agent );
			return listener_type( agent );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		void Batch<T>::unhook()
		{
            kill_all( m_elements );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		void Batch<T>::traverse()
		{
            batch_type copy( elements() );
            process( copy );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		template<class V>
		void Batch<T>::traverse(V arg)
		{
            batch_type copy( elements() );
            process( copy, arg );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		template<typename V, typename W>
		void Batch<T>::traverse(V first_arg, W second_arg )
		{
            batch_type copy( elements() );
            process( copy, first_arg, second_arg );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        void Batch<T>::traverse_destructive()
        {
            batch_type copy( elements() );
            process_and_kill( copy );
            m_elements.clear();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        template<class V>
        void Batch<T>::traverse_destructive(V arg)
        {
            batch_type copy( elements() );
            process_and_kill( copy, arg );
            m_elements.clear();
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        template<typename V, typename W>
        void Batch<T>::traverse_destructive(V first_arg, W second_arg )
        {
            batch_type copy( elements() );
            process_and_kill( copy, first_arg, second_arg );
            m_elements.clear();
        }

        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        void Batch<T>::process( const batch_type & batch )
        {
            for_each( batch.begin(), batch.end(), [&](pointer_type p) {
                if (!p->is_dead())
                {
                    m_elements.insert(p);
                    p->invoke();
                }
            } );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        template<typename V>
        void Batch<T>::process( const batch_type & batch, V v )
        {
            for_each( batch.begin(), batch.end(), [&](pointer_type p) {
                if (!p->is_dead())
                {
                    m_elements.insert(p);
                    p->invoke(v);
                }
            } );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        template<typename V, typename W>
        void Batch<T>::process( const batch_type & batch, V v, W w )
        {
            for_each( batch.begin(), batch.end(), [&](pointer_type p) {
                if (!p->is_dead())
                {
                    m_elements.insert(p);
                    p->invoke(v, w);
                }
            } );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        void Batch<T>::process_and_kill( const batch_type & batch )
        {
            for_each( batch.begin(), batch.end(), [](pointer_type p) {
                if (!p->is_dead())
                    p->kill_invoke();
            } );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        template<typename V>
        void Batch<T>::process_and_kill( const batch_type & batch, V v )
        {
            for_each( batch.begin(), batch.end(), [&](pointer_type p) {
                if (!p->is_dead())
                   p->kill_invoke(v);
            } );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        template<typename V, typename W>
        void Batch<T>::process_and_kill( const batch_type & batch, V v, W w )
        {
            for_each( batch.begin(), batch.end(), [&](pointer_type p) {
                if (!p->is_dead())
                    p->kill_invoke(v, w);
            } );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        auto Batch<T>::elements() -> batch_type
        {
            batch_type result;
            result.swap(m_elements);
            return result;
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
        
    } 	// control 
}	// om636