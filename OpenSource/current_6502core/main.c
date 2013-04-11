
/* NOT generated */


#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#define INS struct INSTRUCTION_S




#define ADC_ABSOLUTE       0x6d /* CARRY,OVERFLOW,NEGATIVE,ZERO, */
#define ADC_ABSOLUTE_X     0x7d /* CARRY,OVERFLOW,NEGATIVE,ZERO, */
#define ADC_ABSOLUTE_Y     0x79 /* CARRY,OVERFLOW,NEGATIVE,ZERO, */
#define ADC_IMMEDIATE      0x69 /* CARRY,OVERFLOW,NEGATIVE,ZERO, */
#define ADC_INDIRECT_X     0x61 /* CARRY,OVERFLOW,NEGATIVE,ZERO, */
#define ADC_INDIRECT_Y     0x71 /* CARRY,OVERFLOW,NEGATIVE,ZERO, */
#define ADC_ZERO_PAGE      0x65 /* CARRY,OVERFLOW,NEGATIVE,ZERO, */
#define ADC_ZERO_PAGE_X    0x75 /* CARRY,OVERFLOW,NEGATIVE,ZERO, */
#define AND_ABSOLUTE       0x2d /* NEGATIVE,ZERO, */
#define AND_ABSOLUTE_X     0x3d /* NEGATIVE,ZERO, */
#define AND_ABSOLUTE_Y     0x39 /* NEGATIVE,ZERO, */
#define AND_IMMEDIATE      0x29 /* NEGATIVE,ZERO, */
#define AND_INDIRECT_X     0x21 /* NEGATIVE,ZERO, */
#define AND_INDIRECT_Y     0x31 /* NEGATIVE,ZERO, */
#define AND_ZERO_PAGE      0x25 /* NEGATIVE,ZERO, */
#define AND_ZERO_PAGE_X    0x35 /* NEGATIVE,ZERO, */
#define ASL_ABSOLUTE       0x0e /* CARRY,NEGATIVE,ZERO, */
#define ASL_ABSOLUTE_X     0x1e /* CARRY,NEGATIVE,ZERO, */
#define ASL_ACCUMULATOR    0x0a /* CARRY,NEGATIVE,ZERO, */
#define ASL_ZERO_PAGE      0x06 /* CARRY,NEGATIVE,ZERO, */
#define ASL_ZERO_PAGE_X    0x16 /* CARRY,NEGATIVE,ZERO, */
#define BCC_RELATIVE       0x90 /*  */
#define BCS_RELATIVE       0xb0 /*  */
#define BEQ_RELATIVE       0xf0 /*  */
#define BIT_ABSOLUTE       0x2c /* OVERFLOW,NEGATIVE,ZERO, */
#define BIT_ZERO_PAGE      0x24 /* OVERFLOW,NEGATIVE,ZERO, */
#define BMI_RELATIVE       0x30 /*  */
#define BNE_RELATIVE       0xd0 /*  */
#define BPL_RELATIVE       0x10 /*  */
#define BRK_IMPLIED        0x00 /* BRK, */
#define BVC_RELATIVE       0x50 /*  */
#define BVS_RELATIVE       0x70 /*  */
#define CLC_IMPLIED        0x18 /* CARRY, */
#define CLD_IMPLIED        0xd8 /* DECIMAL, */
#define CLI_IMPLIED        0x58 /* IRQ, */
#define CLV_IMPLIED        0xb8 /* OVERFLOW, */
#define CMP_ABSOLUTE       0xcd /* CARRY,NEGATIVE,ZERO, */
#define CMP_ABSOLUTE_X     0xdd /* CARRY,NEGATIVE,ZERO, */
#define CMP_ABSOLUTE_Y     0xd9 /* CARRY,NEGATIVE,ZERO, */
#define CMP_IMMEDIATE      0xc9 /* CARRY,NEGATIVE,ZERO, */
#define CMP_INDIRECT_X     0xc1 /* CARRY,NEGATIVE,ZERO, */
#define CMP_INDIRECT_Y     0xd1 /* CARRY,NEGATIVE,ZERO, */
#define CMP_ZERO_PAGE      0xc5 /* CARRY,NEGATIVE,ZERO, */
#define CMP_ZERO_PAGE_X    0xd5 /* CARRY,NEGATIVE,ZERO, */
#define CPX_ABSOLUTE       0xec /* CARRY,NEGATIVE,ZERO, */
#define CPX_IMMEDIATE      0xe0 /* CARRY,NEGATIVE,ZERO, */
#define CPX_ZERO_PAGE      0xe4 /* CARRY,NEGATIVE,ZERO, */
#define CPY_ABSOLUTE       0xcc /* CARRY,NEGATIVE,ZERO, */
#define CPY_IMMEDIATE      0xc0 /* CARRY,NEGATIVE,ZERO, */
#define CPY_ZERO_PAGE      0xc4 /* CARRY,NEGATIVE,ZERO, */
#define DEC_ABSOLUTE       0xce /* NEGATIVE,ZERO, */
#define DEC_ABSOLUTE_X     0xde /* NEGATIVE,ZERO, */
#define DEC_ZERO_PAGE      0xc6 /* NEGATIVE,ZERO, */
#define DEC_ZERO_PAGE_X    0xd6 /* NEGATIVE,ZERO, */
#define DEX_IMPLIED        0xca /* NEGATIVE,ZERO, */
#define DEY_IMPLIED        0x88 /* NEGATIVE,ZERO, */
#define EOR_ABSOLUTE       0x4d /* NEGATIVE,ZERO, */
#define EOR_ABSOLUTE_X     0x5d /* NEGATIVE,ZERO, */
#define EOR_ABSOLUTE_Y     0x59 /* NEGATIVE,ZERO, */
#define EOR_IMMEDIATE      0x49 /* NEGATIVE,ZERO, */
#define EOR_INDIRECT_X     0x41 /* NEGATIVE,ZERO, */
#define EOR_INDIRECT_Y     0x51 /* NEGATIVE,ZERO, */
#define EOR_ZERO_PAGE      0x45 /* NEGATIVE,ZERO, */
#define EOR_ZERO_PAGE_X    0x55 /* NEGATIVE,ZERO, */
#define INC_ABSOLUTE       0xee /* NEGATIVE,ZERO, */
#define INC_ABSOLUTE_X     0xfe /* NEGATIVE,ZERO, */
#define INC_ZERO_PAGE      0xe6 /* NEGATIVE,ZERO, */
#define INC_ZERO_PAGE_X    0xf6 /* NEGATIVE,ZERO, */
#define INX_IMPLIED        0xe8 /* NEGATIVE,ZERO, */
#define INY_IMPLIED        0xc8 /* NEGATIVE,ZERO, */
#define JMP_ABSOLUTE       0x4c /*  */
#define JMP_INDIRECT       0x6c /*  */
#define JSR_ABSOLUTE       0x20 /*  */
#define LDA_ABSOLUTE       0xad /* NEGATIVE,ZERO, */
#define LDA_ABSOLUTE_X     0xbd /* NEGATIVE,ZERO, */
#define LDA_ABSOLUTE_Y     0xb9 /* NEGATIVE,ZERO, */
#define LDA_IMMEDIATE      0xa9 /* NEGATIVE,ZERO, */
#define LDA_ZERO_PAGE      0xa5 /* NEGATIVE,ZERO, */
#define LDA_INDIRECT_X     0xa1 /* NEGATIVE,ZERO, */
#define LDA_INDIRECT_Y     0xb1 /* NEGATIVE,ZERO, */
#define LDA_ZERO_PAGE_X    0xb5 /* NEGATIVE,ZERO, */
#define LDX_ABSOLUTE       0xae /* NEGATIVE,ZERO, */
#define LDX_ABSOLUTE_Y     0xbe /* NEGATIVE,ZERO, */
#define LDX_IMMEDIATE      0xa2 /* NEGATIVE,ZERO, */
#define LDX_ZERO_PAGE      0xa6 /* NEGATIVE,ZERO, */
#define LDX_ZERO_PAGE_Y    0xb6 /* NEGATIVE,ZERO, */
#define LDY_ABSOLUTE       0xac /* NEGATIVE,ZERO, */
#define LDY_ABSOLUTE_X     0xbc /* NEGATIVE,ZERO, */
#define LDY_IMMEDIATE      0xa0 /* NEGATIVE,ZERO, */
#define LDY_ZERO_PAGE      0xa4 /* NEGATIVE,ZERO, */
#define LDY_ZERO_PAGE_X    0xb4 /* NEGATIVE,ZERO, */
#define LSR_ABSOLUTE       0x4e /* CARRY,NEGATIVE,ZERO, */
#define LSR_ABSOLUTE_X     0x5e /* CARRY,NEGATIVE,ZERO, */
#define LSR_ACCUMULATOR    0x4a /* CARRY,NEGATIVE,ZERO, */
#define LSR_ZERO_PAGE      0x46 /* CARRY,NEGATIVE,ZERO, */
#define LSR_ZERO_PAGE_X    0x56 /* CARRY,NEGATIVE,ZERO, */
#define NOP_IMPLIED        0xea /*  */
#define ORA_ABSOLUTE       0x0d /* NEGATIVE,ZERO, */
#define ORA_ABSOLUTE_X     0x1d /* NEGATIVE,ZERO, */
#define ORA_ABSOLUTE_Y     0x19 /* NEGATIVE,ZERO, */
#define ORA_IMMEDIATE      0x09 /* NEGATIVE,ZERO, */
#define ORA_INDIRECT_X     0x01 /* NEGATIVE,ZERO, */
#define ORA_INDIRECT_Y     0x11 /* NEGATIVE,ZERO, */
#define ORA_ZERO_PAGE      0x05 /* NEGATIVE,ZERO, */
#define ORA_ZERO_PAGE_X    0x15 /* NEGATIVE,ZERO, */
#define PHA_IMPLIED        0x48 /*  */
#define PHP_IMPLIED        0x08 /*  */
#define PLA_IMPLIED        0x68 /* NEGATIVE,ZERO, */
#define PLP_IMPLIED        0x28 /* CARRY,OVERFLOW,NEGATIVE,ZERO,BRK,IRQ,DECIMAL, */
#define RESET_INTERNAL       0x03 /* IRQ, */
#define ROL_ABSOLUTE       0x2e /* CARRY,NEGATIVE,ZERO, */
#define ROL_ABSOLUTE_X     0x3e /* CARRY,NEGATIVE,ZERO, */
#define ROL_ACCUMULATOR    0x2a /* CARRY,NEGATIVE,ZERO, */
#define ROL_ZERO_PAGE      0x26 /* CARRY,NEGATIVE,ZERO, */
#define ROL_ZERO_PAGE_X    0x36 /* CARRY,NEGATIVE,ZERO, */
#define ROR_ABSOLUTE       0x6e /* CARRY,NEGATIVE,ZERO, */
#define ROR_ABSOLUTE_X     0x7e /* CARRY,NEGATIVE,ZERO, */
#define ROR_ACCUMULATOR    0x6a /* CARRY,NEGATIVE,ZERO, */
#define ROR_ZERO_PAGE      0x66 /* CARRY,NEGATIVE,ZERO, */
#define ROR_ZERO_PAGE_X    0x76 /* CARRY,NEGATIVE,ZERO, */
#define RTI_IMPLIED        0x40 /* CARRY,OVERFLOW,NEGATIVE,ZERO,BRK,IRQ,DECIMAL, */
#define RTS_IMPLIED        0x60 /*  */
#define SBC_ABSOLUTE       0xed /* CARRY,OVERFLOW,NEGATIVE,ZERO, */
#define SBC_ABSOLUTE_X     0xfd /* CARRY,OVERFLOW,NEGATIVE,ZERO, */
#define SBC_ABSOLUTE_Y     0xf9 /* CARRY,OVERFLOW,NEGATIVE,ZERO, */
#define SBC_IMMEDIATE      0xe9 /*  */
#define SBC_INDIRECT_X     0xe1 /* CARRY,OVERFLOW,NEGATIVE,ZERO, */
#define SBC_INDIRECT_Y     0xf1 /* CARRY,OVERFLOW,NEGATIVE,ZERO, */
#define SBC_ZERO_PAGE      0xe5 /* CARRY,OVERFLOW,NEGATIVE,ZERO, */
#define SBC_ZERO_PAGE_X    0xf5 /* CARRY,OVERFLOW,NEGATIVE,ZERO, */
#define SEC_IMPLIED        0x38 /* CARRY, */
#define SED_IMPLIED        0xf8 /* DECIMAL, */
#define SEI_IMPLIED        0x78 /* IRQ, */
#define STA_ABSOLUTE       0x8d /*  */
#define STA_ABSOLUTE_Y     0x99 /*  */
#define STA_INDIRECT_X     0x81 /*  */
#define STA_INDIRECT_Y     0x91 /*  */
#define STA_ZERO_PAGE      0x85 /*  */
#define STA_ZERO_PAGE_X    0x95 /*  */
#define STA_ABSOLUTE_X     0x9d /*  */
#define S_IRQ_INTERNAL       0x43 /* IRQ, */
#define S_NMI_INTERNAL       0x33 /* IRQ, */
#define STX_ABSOLUTE       0x8e /*  */
#define STX_ZERO_PAGE      0x86 /*  */
#define STX_ZERO_PAGE_Y    0x96 /*  */
#define STY_ABSOLUTE       0x8c /*  */
#define STY_ZERO_PAGE      0x84 /*  */
#define STY_ZERO_PAGE_X    0x94 /*  */
#define TAX_IMPLIED        0xaa /* NEGATIVE,ZERO, */
#define TAY_IMPLIED        0xa8 /* NEGATIVE,ZERO, */
#define TSX_IMPLIED        0xba /* NEGATIVE,ZERO, */
#define TXA_IMPLIED        0x8a /* NEGATIVE,ZERO, */
#define TXS_IMPLIED        0x9a /*  */






void bunch_of_new_lines() {fprintf(stdout, "\n\n");}
int main() {

struct INSTRUCTION_S dummy;
bunch_of_new_lines();perform_ADC_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_ADC_ABSOLUTE_X   (&dummy);
bunch_of_new_lines();perform_ADC_ABSOLUTE_Y   (&dummy);
bunch_of_new_lines();perform_ADC_IMMEDIATE    (&dummy);
bunch_of_new_lines();perform_ADC_INDIRECT_X   (&dummy);
bunch_of_new_lines();perform_ADC_INDIRECT_Y   (&dummy);
bunch_of_new_lines();perform_ADC_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_ADC_ZERO_PAGE_X  (&dummy);
bunch_of_new_lines();perform_AND_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_AND_ABSOLUTE_X   (&dummy);
bunch_of_new_lines();perform_AND_ABSOLUTE_Y   (&dummy);
bunch_of_new_lines();perform_AND_IMMEDIATE    (&dummy);
bunch_of_new_lines();perform_AND_INDIRECT_X   (&dummy);
bunch_of_new_lines();perform_AND_INDIRECT_Y   (&dummy);
bunch_of_new_lines();perform_AND_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_AND_ZERO_PAGE_X  (&dummy);
bunch_of_new_lines();perform_ASL_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_ASL_ABSOLUTE_X   (&dummy);
bunch_of_new_lines();perform_ASL_ACCUMULATOR  (&dummy);
bunch_of_new_lines();perform_ASL_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_ASL_ZERO_PAGE_X  (&dummy);
bunch_of_new_lines();perform_BCC_RELATIVE     (&dummy);
bunch_of_new_lines();perform_BCS_RELATIVE     (&dummy);
bunch_of_new_lines();perform_BEQ_RELATIVE     (&dummy);
bunch_of_new_lines();perform_BIT_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_BIT_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_BMI_RELATIVE     (&dummy);
bunch_of_new_lines();perform_BNE_RELATIVE     (&dummy);
bunch_of_new_lines();perform_BPL_RELATIVE     (&dummy);
bunch_of_new_lines();perform_BRK_IMPLIED      (&dummy);
bunch_of_new_lines();perform_BVC_RELATIVE     (&dummy);
bunch_of_new_lines();perform_BVS_RELATIVE     (&dummy);
bunch_of_new_lines();perform_CLC_IMPLIED      (&dummy);
bunch_of_new_lines();perform_CLD_IMPLIED      (&dummy);
bunch_of_new_lines();perform_CLI_IMPLIED      (&dummy);
bunch_of_new_lines();perform_CLV_IMPLIED      (&dummy);
bunch_of_new_lines();perform_CMP_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_CMP_ABSOLUTE_X   (&dummy);
bunch_of_new_lines();perform_CMP_ABSOLUTE_Y   (&dummy);
bunch_of_new_lines();perform_CMP_IMMEDIATE    (&dummy);
bunch_of_new_lines();perform_CMP_INDIRECT_X   (&dummy);
bunch_of_new_lines();perform_CMP_INDIRECT_Y   (&dummy);
bunch_of_new_lines();perform_CMP_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_CMP_ZERO_PAGE_X  (&dummy);
bunch_of_new_lines();perform_CPX_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_CPX_IMMEDIATE    (&dummy);
bunch_of_new_lines();perform_CPX_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_CPY_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_CPY_IMMEDIATE    (&dummy);
bunch_of_new_lines();perform_CPY_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_DEC_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_DEC_ABSOLUTE_X   (&dummy);
bunch_of_new_lines();perform_DEC_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_DEC_ZERO_PAGE_X  (&dummy);
bunch_of_new_lines();perform_DEX_IMPLIED      (&dummy);
bunch_of_new_lines();perform_DEY_IMPLIED      (&dummy);
bunch_of_new_lines();perform_EOR_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_EOR_ABSOLUTE_X   (&dummy);
bunch_of_new_lines();perform_EOR_ABSOLUTE_Y   (&dummy);
bunch_of_new_lines();perform_EOR_IMMEDIATE    (&dummy);
bunch_of_new_lines();perform_EOR_INDIRECT_X   (&dummy);
bunch_of_new_lines();perform_EOR_INDIRECT_Y   (&dummy);
bunch_of_new_lines();perform_EOR_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_EOR_ZERO_PAGE_X  (&dummy);
bunch_of_new_lines();perform_INC_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_INC_ABSOLUTE_X   (&dummy);
bunch_of_new_lines();perform_INC_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_INC_ZERO_PAGE_X  (&dummy);
bunch_of_new_lines();perform_INX_IMPLIED      (&dummy);
bunch_of_new_lines();perform_INY_IMPLIED      (&dummy);
bunch_of_new_lines();perform_JMP_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_JMP_INDIRECT     (&dummy);
bunch_of_new_lines();perform_JSR_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_LDA_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_LDA_ABSOLUTE_X   (&dummy);
bunch_of_new_lines();perform_LDA_ABSOLUTE_Y   (&dummy);
bunch_of_new_lines();perform_LDA_IMMEDIATE    (&dummy);
bunch_of_new_lines();perform_LDA_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_LDA_INDIRECT_X   (&dummy);
bunch_of_new_lines();perform_LDA_INDIRECT_Y   (&dummy);
bunch_of_new_lines();perform_LDA_ZERO_PAGE_X  (&dummy);
bunch_of_new_lines();perform_LDX_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_LDX_ABSOLUTE_Y   (&dummy);
bunch_of_new_lines();perform_LDX_IMMEDIATE    (&dummy);
bunch_of_new_lines();perform_LDX_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_LDX_ZERO_PAGE_Y  (&dummy);
bunch_of_new_lines();perform_LDY_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_LDY_ABSOLUTE_X   (&dummy);
bunch_of_new_lines();perform_LDY_IMMEDIATE    (&dummy);
bunch_of_new_lines();perform_LDY_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_LDY_ZERO_PAGE_X  (&dummy);
bunch_of_new_lines();perform_LSR_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_LSR_ABSOLUTE_X   (&dummy);
bunch_of_new_lines();perform_LSR_ACCUMULATOR  (&dummy);
bunch_of_new_lines();perform_LSR_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_LSR_ZERO_PAGE_X  (&dummy);
bunch_of_new_lines();perform_NOP_IMPLIED      (&dummy);
bunch_of_new_lines();perform_ORA_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_ORA_ABSOLUTE_X   (&dummy);
bunch_of_new_lines();perform_ORA_ABSOLUTE_Y   (&dummy);
bunch_of_new_lines();perform_ORA_IMMEDIATE    (&dummy);
bunch_of_new_lines();perform_ORA_INDIRECT_X   (&dummy);
bunch_of_new_lines();perform_ORA_INDIRECT_Y   (&dummy);
bunch_of_new_lines();perform_ORA_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_ORA_ZERO_PAGE_X  (&dummy);
bunch_of_new_lines();perform_PHA_IMPLIED      (&dummy);
bunch_of_new_lines();perform_PHP_IMPLIED      (&dummy);
bunch_of_new_lines();perform_PLA_IMPLIED      (&dummy);
bunch_of_new_lines();perform_PLP_IMPLIED      (&dummy);
bunch_of_new_lines();perform_RESET_INTERNAL     (&dummy);
bunch_of_new_lines();perform_ROL_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_ROL_ABSOLUTE_X   (&dummy);
bunch_of_new_lines();perform_ROL_ACCUMULATOR  (&dummy);
bunch_of_new_lines();perform_ROL_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_ROL_ZERO_PAGE_X  (&dummy);
bunch_of_new_lines();perform_ROR_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_ROR_ABSOLUTE_X   (&dummy);
bunch_of_new_lines();perform_ROR_ACCUMULATOR  (&dummy);
bunch_of_new_lines();perform_ROR_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_ROR_ZERO_PAGE_X  (&dummy);
bunch_of_new_lines();perform_RTI_IMPLIED      (&dummy);
bunch_of_new_lines();perform_RTS_IMPLIED      (&dummy);
bunch_of_new_lines();perform_SBC_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_SBC_ABSOLUTE_X   (&dummy);
bunch_of_new_lines();perform_SBC_ABSOLUTE_Y   (&dummy);
bunch_of_new_lines();perform_SBC_IMMEDIATE    (&dummy);
bunch_of_new_lines();perform_SBC_INDIRECT_X   (&dummy);
bunch_of_new_lines();perform_SBC_INDIRECT_Y   (&dummy);
bunch_of_new_lines();perform_SBC_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_SBC_ZERO_PAGE_X  (&dummy);
bunch_of_new_lines();perform_SEC_IMPLIED      (&dummy);
bunch_of_new_lines();perform_SED_IMPLIED      (&dummy);
bunch_of_new_lines();perform_SEI_IMPLIED      (&dummy);
bunch_of_new_lines();perform_STA_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_STA_ABSOLUTE_Y   (&dummy);
bunch_of_new_lines();perform_STA_INDIRECT_X   (&dummy);
bunch_of_new_lines();perform_STA_INDIRECT_Y   (&dummy);
bunch_of_new_lines();perform_STA_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_STA_ZERO_PAGE_X  (&dummy);
bunch_of_new_lines();perform_STA_ABSOLUTE_X   (&dummy);
bunch_of_new_lines();perform_S_IRQ_INTERNAL     (&dummy);
bunch_of_new_lines();perform_S_NMI_INTERNAL     (&dummy);
bunch_of_new_lines();perform_STX_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_STX_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_STX_ZERO_PAGE_Y  (&dummy);
bunch_of_new_lines();perform_STY_ABSOLUTE     (&dummy);
bunch_of_new_lines();perform_STY_ZERO_PAGE    (&dummy);
bunch_of_new_lines();perform_STY_ZERO_PAGE_X  (&dummy);
bunch_of_new_lines();perform_TAX_IMPLIED      (&dummy);
bunch_of_new_lines();perform_TAY_IMPLIED      (&dummy);
bunch_of_new_lines();perform_TSX_IMPLIED      (&dummy);
bunch_of_new_lines();perform_TXA_IMPLIED      (&dummy);
bunch_of_new_lines();perform_TXS_IMPLIED      (&dummy);
}

