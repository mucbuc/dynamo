using namespace om636;
using namespace std;

void check_traverse()
{
	typedef std::function<void()> callback_type;
	control::Batch<callback_type> batch;
	bool passed(0);

	auto temp(batch.hook( [&](){
		passed = 1;
	} ) );

	batch.traverse();	

	ASSERT( passed );
	FOOTER;
}