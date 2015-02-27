using namespace om636;
using namespace std;

typedef std::function<void()> callback_type;
typedef control::Batch<callback_type> batch_type;

void check_traverse_while_traverse()
{
	batch_type batch;
	unsigned passed(0);
    
    auto p( batch.hook( [&](){
        ++passed;
        batch.traverse();
    } ) );
    
    batch.traverse();

    ASSERT( passed == 1 );
    FOOTER;
}

void check_traverse()
{
	batch_type batch;
	unsigned passed(0);

	auto temp(batch.hook( [&](){
		++passed;
	} ) );

	batch.traverse();	
	batch.traverse();	

	ASSERT( passed == 2 );
	FOOTER;
}