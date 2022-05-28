#ifndef ARM_HEADER
#define ARM_HEADER

#include <stdint.h>

#define GENERAL_REGISTERS_SIZE 31
#define STATUS_REGISTERS_SIZE 6

#define ARM_STATE_SP_INDEX 13
#define ARM_STATE_LR_INDEX 14
#define ARM_STATE_PC_INDEX 15

typedef enum
{
    ARM = 0,
    THUMB
} state_e;

typedef enum
{
    USR = 0, // The usual ARM program execution state
    FIQ,     // Supports data transfer of channel process
    IRQ,     // General-purpose interrupt handling
    SVC,     // A protected mode for the operating system
    ABT,     // Entered after a data or instruction Prefetch Abort
    SYS,     // A privileged user mode for the operating system
    UND,     // Undefined mode, entered when an undefined instruction is executed.
} mode_e;

typedef struct
{
    int32_t general_registers[GENERAL_REGISTERS_SIZE];
    int32_t status_registers[STATUS_REGISTERS_SIZE];
	
    int32_t SP;
    int32_t LR;
    int32_t PC;
    int32_t CPSR;
    int32_t SPSR;

    state_e state;
    mode_e mode;
} arm_t;

void set_state(arm_t *arm, state_e state);

void set_mode(arm_t *arm, mode_e mode);

#endif
