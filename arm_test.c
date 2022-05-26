#include "arm.h"

#include <unitc.h>
#include <string.h>

arm_t arm;

static void before_each()
{
    // Zero the registers
	
    memset(arm.general_registers, 0, GENERAL_REGISTERS_SIZE);	
    memset(arm.status_registers, 0, STATUS_REGISTERS_SIZE);

    arm.SP = 0;
    arm.LR = 0;
    arm.PC = 0;
    arm.CPSR = 0;
    arm.SPSR = 0;
}

static void test_set_state_arm()
{
    test_name("test_set_state_arm");
		
    //  This test ensures that when the set_state() function is called with 
    //  the enum argument of 'ARM', the ARM registers are set correctly.
	
    // When setting the state to ARM, registers r13, r14 and r15, are set to
    // the SP, LR and PC, respectively. So I will set the general registers
    // values to test.
	
    arm.general_registers[13] = 1;
    arm.general_registers[14] = 2;
    arm.general_registers[15] = 3;

    // Call to set_state() with the enum argument as 'ARM'.
    set_state(&arm, ARM);

    ASSERT_EQUAL(arm.SP, 1);	
    ASSERT_EQUAL(arm.LR, 2);	
    ASSERT_EQUAL(arm.PC, 3);	
}

int main(int argc, char *argv[])
{	
    set_before_each(before_each);

    void (*tests[])() = 
	{
        test_set_state_arm
    };

    run_tests(tests, 1);

    return 0;
}
