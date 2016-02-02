// create a test
#include "simpletest.h"


TEST_RESULT test1()
{
	int x = 2;

	TEST_ASSERT("x equal with 2", x == 2);

	return TEST_OK;
}

//create another test
TEST_RESULT test2()
{
	int w = 2;
	TEST_ASSERT("w equal 3", w == 3);

	return TEST_OK;
}


//group tests in fixtures
DECLARE_FIXTURE(numbers)
RUN_TEST(test1)
RUN_TEST(test2)
END_FIXTURE


DECLARE_FIXTURE(numbers2)
RUN_TEST(test1)
END_FIXTURE



int main(int argc, char *argv[]) {

	//run the fixtures
	RUN_FIXTURE(numbers)
	RUN_FIXTURE(numbers2)
	return 0;
}

