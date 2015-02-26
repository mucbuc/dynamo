#include <iostream>
#include <functional>

#include <plank/src/test.h>

#include <lib/dynamo/src/batch.h>

int main(int argc, const char * argv[])
{
	using namespace om636;
	using namespace std;


	typedef std::function<void()> callback_type;
	control::Batch<callback_type> batch;

	ASSERT(1);
	std::cout << "hello test cases" << std::endl;
	return 0;
}