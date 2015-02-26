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
            kill_all( m_elements );
            kill_all( m_elements_add );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		void Batch<T>::traverse()
		{
            batch_type copy( add_elements() );
            process( copy );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		template<class V>
		void Batch<T>::traverse(V arg)
		{
            batch_type copy( add_elements() );
            process( copy, arg );
        }
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		template<typename V, typename W>
		void Batch<T>::traverse(V first_arg, W second_arg )
		{
            batch_type copy( add_elements() );
            process( copy, first_arg, second_arg );

            //batch_type repeats( m_repeat[ e ] ); //<== bug, not passing args: write test case
            //process( repeats );
        }
        

        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        void Batch<T>::traverse_destructive()
        {
            batch_type copy( add_elements() );
            process_and_kill( copy );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        template<class V>
        void Batch<T>::traverse_destructive(V arg)
        {
            batch_type copy( add_elements() );
            process_and_kill( copy, arg );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        template<typename V, typename W>
        void Batch<T>::traverse_destructive(V first_arg, W second_arg )
        {
            batch_type copy( add_elements() );
            process_and_kill( copy, first_arg, second_arg );
        }

        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        void Batch<T>::process( const batch_type & batch )
        {
            for_each( batch.begin(), batch.end(), [](pointer_type p) {
                if (!p->is_dead())
                    p->invoke();
            } );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        template<typename V>
        void Batch<T>::process( const batch_type & batch, V v )
        {
            for_each( batch.begin(), batch.end(), [&](pointer_type p) {
                if (!p->is_dead())
                    p->invoke(v);
            } );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        template<typename V, typename W>
        void Batch<T>::process( const batch_type & batch, V v, W w )
        {
            for_each( batch.begin(), batch.end(), [&](pointer_type p) {
                if (!p->is_dead())
                    p->invoke(v, w);
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
        auto Batch<T>::add_elements() -> batch_type
        {
            m_elements.insert( m_elements_add.begin(), m_elements_add.end() );
            m_elements_add.clear();
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
        
    } 	// control 
}	// om636