#ifndef BATCH_H__iFZqmDoIwhGaYO3df4xe5LCQXrbBvj
#define BATCH_H__iFZqmDoIwhGaYO3df4xe5LCQXrbBvj

#include <map>
#include <memory>
#include <set>

#include "agent.h"
#include "listener.h"

namespace om636
{
	namespace control 
	{
		template<typename T> 
		class Batch 
		{
		public: 

			typedef T callback_type;
			typedef Agent< callback_type > agent_type;
            typedef std::shared_ptr< agent_type > pointer_type;
            typedef Listener< pointer_type > listener_type;
            typedef std::multiset< pointer_type > batch_type;
		
			Batch() = default;
			virtual ~Batch() = default;
            Batch(const Batch &) = delete;
            Batch & operator=(const Batch &) = delete;
			
			listener_type hook(callback_type);
            void unhook();
			void traverse();
			
			template<class V> 
			void traverse( V );
			
			template<typename V, typename W> 
			void traverse( V, W );			

			void traverse_destructive();
			
			template<class V> 
			void traverse_destructive( V );
			
			template<typename V, typename W> 
			void traverse_destructive( V, W );
            
		    static void process_and_kill( batch_type & );
            
            template<typename V>
            static void process_and_kill( batch_type &, V );
            
            template<typename V, typename W>
            static void process_and_kill( batch_type &, V, W );
            
            static batch_type process( batch_type );
            
            template<typename V>
            static batch_type process( batch_type, V );
            
            template<typename V, typename W>
            static batch_type process( batch_type, V, W );
            
            static void kill_all(batch_type &);
            
            batch_type & elements();
           	const batch_type & elements() const;

        private:

        	void merge_new_elements();

			batch_type m_elements;
			batch_type m_elements_add;
		};
	}	//control
}	// om636

#include "batch.hxx"

#endif 