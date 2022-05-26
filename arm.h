#ifndef ARM_HEADER
#define ARM_HEADER

#include <stdint.h>

#define ARM_STATE_SP_INDEX 13
#define ARM_STATE_LR_INDEX 14
#define ARM_STATE_PC_INDEX 15

typedef struct
{
	int32_t general_registers[31];
	int32_t status_registers[6];
	
	// If in ARM mode, r13 is used as the Stack Pointer (SP), r14 is used as
	// the subroutine Link Register (LR), and r15 holds the Program 
	// Counter (PC).
	
	int32_t SP;
	int32_t LR;
	int32_t PC;
	int32_t CPSR;
	int32_t SPSR;
} arm_t;

typedef enum
{
	ARM = 0,
	THUMB
} mode_e;

void set_mode(mode_e mode);

#endif
