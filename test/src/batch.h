using namespace om636;
using namespace std;

void check_traverse()
{
	typedef std::function<void()> callback_type;
	control::Batch<callback_type> batch;
	unsigned passed(0);

	auto temp(batch.hook( [&](){
		++passed;
	} ) );

	batch.traverse();	
	batch.traverse();	

	ASSERT( passed == 2 );
	FOOTER;
}