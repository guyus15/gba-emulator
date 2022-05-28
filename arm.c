#include "arm.h"

void set_state(arm_t *arm, state_e state)
{
    arm->state = state;

    if (arm->state == ARM)
    {
        // In ARM state, r13 is used as the Stack Pointer (SP), r14 is used as
        // the subroutine Link Register (LR), and r15 holds the Program
        // Counter (PC).
        arm->SP = arm->general_registers[ARM_STATE_SP_INDEX];   
        arm->LR = arm->general_registers[ARM_STATE_LR_INDEX];
        arm->PC = arm->general_registers[ARM_STATE_PC_INDEX];
    } else if (arm->state == THUMB)
    {
        // Temporary values.
        arm->SP = 0;
        arm->LR = 0;
        arm->PC = 0;    
    }
}

void set_mode(arm_t *arm, mode_e mode)
{
    arm->mode = mode;

}
