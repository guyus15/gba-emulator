#include <unitc.h>
#include <arm.h>

#include <stblib.h>

arm_t arm;

static void before_each()
{
	// Zero the registers
	
	memset(arm->general_registers, 0, GENERAL_REGISTERS_SIZE);	
	memset(arm->status_registers, 0, STATUS_REGISTERS_SIZE);

	arm->SP = 0;
	arm->LR = 0;
	arm->PC = 0;
	arm->CPSR = 0;
	arm->SPSR = 0;
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
