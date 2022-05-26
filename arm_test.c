#include <unitc.h>
#include <arm.h>

arm_t arm;

static void before_each()
{
	
}

int main(int argc, char *argv[])
{	
	set_before_each_function(before_each);

	void (*tests[])() = 
	{

	};

	run_tests(tests, 0);

	return 0;
}
