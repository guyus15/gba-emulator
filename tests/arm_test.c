#include "../arm.h"

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

// Test 1
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
    
    // Check that values have been set correctly
    ASSERT_EQUAL(arm.state, ARM);

    ASSERT_EQUAL(*(arm.SP), 1);	
    ASSERT_EQUAL(*(arm.LR), 2);	
    ASSERT_EQUAL(*(arm.PC), 3);	
}

// Test 2
static void test_set_state_thumb()
{
    test_name("test_set_state_thumb");

    // This test ensures that when the set_state() function is called with
    // the enum argument of 'THUMB', the ARM regsiters are set correctly.
    
    // When setting the state to Thumb, the Stack Pointer, Link Register and
    // Program Counter are set to individual values. They do not rely on
    // general registers.

    // First set the state to ARM so we can see that values correctly map over
    // when switched to Thumb state.

    arm.general_registers[13] = 3;
    arm.general_registers[14] = 4;
    arm.general_registers[15] = 5;

    set_state(&arm, ARM);

    // Call to set_state() with the enum argument as 'THUMB'.
    set_state(&arm, THUMB);

    // Check that values have been set correctly
    ASSERT_EQUAL(arm.state, THUMB);

    ASSERT_EQUAL(*(arm.SP), 3); 
    ASSERT_EQUAL(*(arm.LR), 4); 
    ASSERT_EQUAL(*(arm.PC), 5); 
}

// Test 4
static void test_set_state_arm_then_thumb()
{
    test_name("test_set_state_arm_then_thumb");
    // This test ensures that the program behaves correctly when we call the 
    // set_state() function first with the argument 'ARM' and then with the
    // argument 'THUMB'

    arm.general_registers[13] = 1;
    arm.general_registers[14] = 2;
    arm.general_registers[15] = 3;

    set_state(&arm, ARM);

    set_state(&arm, THUMB);

    // Check values are the correct values
    ASSERT_EQUAL(*(arm.SP), 1);
    ASSERT_EQUAL(*(arm.LR), 2);
    ASSERT_EQUAL(*(arm.PC), 3);
}

// Test 5
static void test_set_state_thumb_then_arm()
{
    test_name("test_set_state_thumb_then_arm");

    // This test ensures that the program behaves correctly when we call the 
    // set_state() function first with the argument 'THUMB' and then with the
    // argument 'ARM'
    
    arm.general_registers[13] = 1;
    arm.general_registers[14] = 2;
    arm.general_registers[15] = 3;

    set_state(&arm, THUMB);

    set_state(&arm, ARM);

    // Check values are the correct values
    ASSERT_EQUAL(*(arm.SP), 1);
    ASSERT_EQUAL(*(arm.LR), 2);
    ASSERT_EQUAL(*(arm.PC), 3);
}

// Test 3
static void test_set_mode()
{
    test_name("test_set_mode");

    // This test ensures that when the set_mode() function is called,
    // the mode of operation of the processor is set correctly.
    
    // Call to set_mode() with the enum argument as 'USR'
    set_mode(&arm, USR);
    ASSERT_EQUAL(arm.mode, USR);

    // Call to set_mode() with the enum argument as 'FIQ'
    set_mode(&arm, FIQ);
    ASSERT_EQUAL(arm.mode, FIQ);

    // Call to set_mode() with the enum argument as 'IRQ'
    set_mode(&arm, IRQ);
    ASSERT_EQUAL(arm.mode, IRQ);

    // Call to set_mode() with the enum argument as 'SVC'
    set_mode(&arm, SVC);
    ASSERT_EQUAL(arm.mode, SVC);
    
    // Call to set_mode() with the enum argument as 'ABT'
    set_mode(&arm, ABT);
    ASSERT_EQUAL(arm.mode, ABT);

    // Call to set_mode() with the enum argument as 'SYS'
    set_mode(&arm, SYS);
    ASSERT_EQUAL(arm.mode, SYS); 

    // Call to set_mode() with the enum argument as 'UND'
    set_mode(&arm, UND);
    ASSERT_EQUAL(arm.mode, UND);
}

int main(int argc, char *argv[])
{	
    set_before_each(before_each);

    void (*tests[])() = 
	{
        test_set_state_arm,
        test_set_state_thumb,
        test_set_mode,
        test_set_state_arm_then_thumb,
        test_set_state_thumb_then_arm
    };

    run_tests(tests, 5);

    return 0;
}
