#include "arm.h"

#include <stdlib.h>
#include <stdio.h>

void set_state(arm_t *arm, state_e state)
{
    arm->state = state;

    if (arm->state == ARM)
    {
        printf("Setting the state to ARM\n");

        // Check if the Stack Pointer, Linker Register and Program Counter have
        // been allocated, if they have, free them.
        if (arm->SP != NULL)
        {
            free(arm->SP);
        }
        if (arm->LR != NULL)
        {
            free(arm->LR);
        }
        if (arm->PC != NULL)
        {
            free(arm->PC);
        }

        // In ARM state, r13 is used as the Stack Pointer (SP), r14 is used as
        // the subroutine Link Register (LR), and r15 holds the Program
        // Counter (PC).
        arm->SP = &arm->general_registers[ARM_STATE_SP_INDEX];   
        arm->LR = &arm->general_registers[ARM_STATE_LR_INDEX];
        arm->PC = &arm->general_registers[ARM_STATE_PC_INDEX];
    } else if (arm->state == THUMB)
    {
        int32_t temp1, temp2, temp3;

        if (arm->SP != NULL)
        {
            // Copy values of r13, r14, and r15 to preserve mapping
            temp1 = *(arm->SP);
            temp2 = *(arm->LR);
            temp3 = *(arm->PC);
        } else {
            temp1 = temp2 = temp3 = 0;
        }

        // Allocate memory to store new values.
        arm->SP = (int32_t *) malloc(sizeof(int32_t));
        arm->LR = (int32_t *) malloc(sizeof(int32_t));
        arm->PC = (int32_t *) malloc(sizeof(int32_t));

        *(arm->SP) = temp1;
        *(arm->LR) = temp2;
        *(arm->PC) = temp3;
    }
}

void set_mode(arm_t *arm, mode_e mode)
{
    arm->mode = mode;

}
