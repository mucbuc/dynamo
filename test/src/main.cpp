#include <iostream>
#include <functional>

#include <plank/src/test.h>

#include <lib/dynamo/src/batch.h>

#include "batch.h"

int main(int argc, const char * argv[])
{
    check_traverse();
	//check_traverse_while_traverse();
	check_traverse_with_arg();
	check_traverse_with_args();

	return 0;
}