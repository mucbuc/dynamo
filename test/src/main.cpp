#include <iostream>
#include <functional>

#include <plank/src/test.h>

#include <lib/dynamo/src/batch.h>

#include "batch.h"

int main(int argc, const char * argv[])
{
    check_traverse();
	check_traverse_while_traverse();
	return 0;
}