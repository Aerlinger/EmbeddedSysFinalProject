
/* AUTOMATICALLY GENERATED, DO NOT MODIFY */

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

void perform_ADC_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ADC_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   ac<=ac_r+data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
ADC_setup_carry(instruction);
ADC_setup_overflow(instruction);
ADC_setup_negative(instruction);
ADC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ADC_ABSOLUTE_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ADC_ABSOLUTE_X");

	addressing_ABSOLUTE_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   ac<=ac_r+data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
ADC_setup_carry(instruction);
ADC_setup_overflow(instruction);
ADC_setup_negative(instruction);
ADC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ADC_ABSOLUTE_Y   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ADC_ABSOLUTE_Y");

	addressing_ABSOLUTE_Y   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   ac<=ac_r+data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
ADC_setup_carry(instruction);
ADC_setup_overflow(instruction);
ADC_setup_negative(instruction);
ADC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ADC_IMMEDIATE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ADC_IMMEDIATE");

	addressing_IMMEDIATE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   ac<=ac_r+data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
ADC_setup_carry(instruction);
ADC_setup_overflow(instruction);
ADC_setup_negative(instruction);
ADC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ADC_INDIRECT_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ADC_INDIRECT_X");

	addressing_INDIRECT_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   ac<=ac_r+data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
ADC_setup_carry(instruction);
ADC_setup_overflow(instruction);
ADC_setup_negative(instruction);
ADC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ADC_INDIRECT_Y   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ADC_INDIRECT_Y");

	addressing_INDIRECT_Y   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   ac<=ac_r+data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
ADC_setup_carry(instruction);
ADC_setup_overflow(instruction);
ADC_setup_negative(instruction);
ADC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ADC_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ADC_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   ac<=ac_r+data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
ADC_setup_carry(instruction);
ADC_setup_overflow(instruction);
ADC_setup_negative(instruction);
ADC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ADC_ZERO_PAGE_X  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ADC_ZERO_PAGE_X");

	addressing_ZERO_PAGE_X  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   ac<=ac_r+data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
ADC_setup_carry(instruction);
ADC_setup_overflow(instruction);
ADC_setup_negative(instruction);
ADC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_AND_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "AND_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
AND_setup_negative(instruction);
AND_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_AND_ABSOLUTE_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "AND_ABSOLUTE_X");

	addressing_ABSOLUTE_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
AND_setup_negative(instruction);
AND_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_AND_ABSOLUTE_Y   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "AND_ABSOLUTE_Y");

	addressing_ABSOLUTE_Y   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
AND_setup_negative(instruction);
AND_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_AND_IMMEDIATE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "AND_IMMEDIATE");

	addressing_IMMEDIATE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
AND_setup_negative(instruction);
AND_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_AND_INDIRECT_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "AND_INDIRECT_X");

	addressing_INDIRECT_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
AND_setup_negative(instruction);
AND_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_AND_INDIRECT_Y   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "AND_INDIRECT_Y");

	addressing_INDIRECT_Y   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
AND_setup_negative(instruction);
AND_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_AND_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "AND_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
AND_setup_negative(instruction);
AND_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_AND_ZERO_PAGE_X  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "AND_ZERO_PAGE_X");

	addressing_ZERO_PAGE_X  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
AND_setup_negative(instruction);
AND_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ASL_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ASL_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ASL_setup_carry(instruction);
ASL_setup_negative(instruction);
ASL_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ASL_ABSOLUTE_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ASL_ABSOLUTE_X");

	addressing_ABSOLUTE_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ASL_setup_carry(instruction);
ASL_setup_negative(instruction);
ASL_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ASL_ACCUMULATOR  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ASL_ACCUMULATOR");

	addressing_ACCUMULATOR  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ASL_setup_carry(instruction);
ASL_setup_negative(instruction);
ASL_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ASL_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ASL_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ASL_setup_carry(instruction);
ASL_setup_negative(instruction);
ASL_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ASL_ZERO_PAGE_X  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ASL_ZERO_PAGE_X");

	addressing_ZERO_PAGE_X  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ASL_setup_carry(instruction);
ASL_setup_negative(instruction);
ASL_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_BCC_RELATIVE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "BCC_RELATIVE");

	addressing_RELATIVE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_BCS_RELATIVE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "BCS_RELATIVE");

	addressing_RELATIVE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_BEQ_RELATIVE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "BEQ_RELATIVE");

	addressing_RELATIVE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"     if(offset_r>0) then \n     pc<=pc_r+offset_r; \n     else \n     pc<=pc_r-offset_r; \n     end if;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
	to_next_instruction(instruction);

}





void perform_BIT_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "BIT_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
BIT_setup_overflow(instruction);
BIT_setup_negative(instruction);
BIT_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_BIT_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "BIT_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
BIT_setup_overflow(instruction);
BIT_setup_negative(instruction);
BIT_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_BMI_RELATIVE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "BMI_RELATIVE");

	addressing_RELATIVE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_BNE_RELATIVE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "BNE_RELATIVE");

	addressing_RELATIVE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_BPL_RELATIVE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "BPL_RELATIVE");

	addressing_RELATIVE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_BRK_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "BRK_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
BRK_setup_brk(instruction);
	to_next_instruction(instruction);

}





void perform_BVC_RELATIVE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "BVC_RELATIVE");

	addressing_RELATIVE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_BVS_RELATIVE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "BVS_RELATIVE");

	addressing_RELATIVE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_CLC_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "CLC_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"--- DONE\n");
fprintf(stdout,"\n-- end  start from strings--\n");
CLC_setup_carry(instruction);
	to_next_instruction(instruction);

}





void perform_CLD_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "CLD_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"--- DONE\n");
fprintf(stdout,"\n-- end  start from strings--\n");
CLD_setup_decimal(instruction);
	to_next_instruction(instruction);

}





void perform_CLI_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "CLI_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
CLI_setup_irq(instruction);
	to_next_instruction(instruction);

}





void perform_CLV_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "CLV_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"--- DONE\n");
fprintf(stdout,"\n-- end  start from strings--\n");
CLV_setup_overflow(instruction);
	to_next_instruction(instruction);

}





void perform_CMP_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "CMP_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
CMP_setup_carry(instruction);
CMP_setup_negative(instruction);
CMP_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_CMP_ABSOLUTE_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "CMP_ABSOLUTE_X");

	addressing_ABSOLUTE_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
CMP_setup_carry(instruction);
CMP_setup_negative(instruction);
CMP_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_CMP_ABSOLUTE_Y   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "CMP_ABSOLUTE_Y");

	addressing_ABSOLUTE_Y   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
CMP_setup_carry(instruction);
CMP_setup_negative(instruction);
CMP_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_CMP_IMMEDIATE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "CMP_IMMEDIATE");

	addressing_IMMEDIATE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
CMP_setup_carry(instruction);
CMP_setup_negative(instruction);
CMP_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_CMP_INDIRECT_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "CMP_INDIRECT_X");

	addressing_INDIRECT_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
CMP_setup_carry(instruction);
CMP_setup_negative(instruction);
CMP_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_CMP_INDIRECT_Y   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "CMP_INDIRECT_Y");

	addressing_INDIRECT_Y   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
CMP_setup_carry(instruction);
CMP_setup_negative(instruction);
CMP_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_CMP_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "CMP_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
CMP_setup_carry(instruction);
CMP_setup_negative(instruction);
CMP_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_CMP_ZERO_PAGE_X  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "CMP_ZERO_PAGE_X");

	addressing_ZERO_PAGE_X  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
CMP_setup_carry(instruction);
CMP_setup_negative(instruction);
CMP_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_CPX_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "CPX_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
CPX_setup_carry(instruction);
CPX_setup_negative(instruction);
CPX_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_CPX_IMMEDIATE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "CPX_IMMEDIATE");

	addressing_IMMEDIATE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
CPX_setup_carry(instruction);
CPX_setup_negative(instruction);
CPX_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_CPX_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "CPX_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
CPX_setup_carry(instruction);
CPX_setup_negative(instruction);
CPX_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_CPY_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "CPY_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
CPY_setup_carry(instruction);
CPY_setup_negative(instruction);
CPY_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_CPY_IMMEDIATE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "CPY_IMMEDIATE");

	addressing_IMMEDIATE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
CPY_setup_carry(instruction);
CPY_setup_negative(instruction);
CPY_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_CPY_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "CPY_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
CPY_setup_carry(instruction);
CPY_setup_negative(instruction);
CPY_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_DEC_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "DEC_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
DEC_setup_negative(instruction);
DEC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_DEC_ABSOLUTE_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "DEC_ABSOLUTE_X");

	addressing_ABSOLUTE_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
DEC_setup_negative(instruction);
DEC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_DEC_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "DEC_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
DEC_setup_negative(instruction);
DEC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_DEC_ZERO_PAGE_X  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "DEC_ZERO_PAGE_X");

	addressing_ZERO_PAGE_X  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
DEC_setup_negative(instruction);
DEC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_DEX_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "DEX_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"   x<=x_r-1;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
DEX_setup_negative(instruction);
DEX_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_DEY_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "DEY_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"   y<=y_r-1;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
DEY_setup_negative(instruction);
DEY_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_EOR_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "EOR_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
EOR_setup_negative(instruction);
EOR_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_EOR_ABSOLUTE_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "EOR_ABSOLUTE_X");

	addressing_ABSOLUTE_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
EOR_setup_negative(instruction);
EOR_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_EOR_ABSOLUTE_Y   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "EOR_ABSOLUTE_Y");

	addressing_ABSOLUTE_Y   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
EOR_setup_negative(instruction);
EOR_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_EOR_IMMEDIATE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "EOR_IMMEDIATE");

	addressing_IMMEDIATE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
EOR_setup_negative(instruction);
EOR_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_EOR_INDIRECT_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "EOR_INDIRECT_X");

	addressing_INDIRECT_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
EOR_setup_negative(instruction);
EOR_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_EOR_INDIRECT_Y   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "EOR_INDIRECT_Y");

	addressing_INDIRECT_Y   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
EOR_setup_negative(instruction);
EOR_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_EOR_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "EOR_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
EOR_setup_negative(instruction);
EOR_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_EOR_ZERO_PAGE_X  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "EOR_ZERO_PAGE_X");

	addressing_ZERO_PAGE_X  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
EOR_setup_negative(instruction);
EOR_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_INC_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "INC_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
INC_setup_negative(instruction);
INC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_INC_ABSOLUTE_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "INC_ABSOLUTE_X");

	addressing_ABSOLUTE_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
INC_setup_negative(instruction);
INC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_INC_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "INC_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
INC_setup_negative(instruction);
INC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_INC_ZERO_PAGE_X  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "INC_ZERO_PAGE_X");

	addressing_ZERO_PAGE_X  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
INC_setup_negative(instruction);
INC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_INX_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "INX_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
INX_setup_negative(instruction);
INX_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_INY_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "INY_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
INY_setup_negative(instruction);
INY_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_JMP_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "JMP_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    pc<=addr_hi_r & addr_lo_r;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
	to_next_instruction(instruction);

}





void perform_JMP_INDIRECT     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "JMP_INDIRECT");

	addressing_INDIRECT     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_JSR_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "JSR_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_LDA_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LDA_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   ac<=data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
LDA_setup_negative(instruction);
LDA_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LDA_ABSOLUTE_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LDA_ABSOLUTE_X");

	addressing_ABSOLUTE_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   ac<=data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
LDA_setup_negative(instruction);
LDA_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LDA_ABSOLUTE_Y   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LDA_ABSOLUTE_Y");

	addressing_ABSOLUTE_Y   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   ac<=data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
LDA_setup_negative(instruction);
LDA_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LDA_IMMEDIATE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LDA_IMMEDIATE");

	addressing_IMMEDIATE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   ac<=data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
LDA_setup_negative(instruction);
LDA_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LDA_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LDA_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   ac<=data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
LDA_setup_negative(instruction);
LDA_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LDA_INDIRECT_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LDA_INDIRECT_X");

	addressing_INDIRECT_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   ac<=data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
LDA_setup_negative(instruction);
LDA_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LDA_INDIRECT_Y   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LDA_INDIRECT_Y");

	addressing_INDIRECT_Y   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   ac<=data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
LDA_setup_negative(instruction);
LDA_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LDA_ZERO_PAGE_X  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LDA_ZERO_PAGE_X");

	addressing_ZERO_PAGE_X  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   ac<=data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
LDA_setup_negative(instruction);
LDA_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LDX_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LDX_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   x<=data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
LDX_setup_negative(instruction);
LDX_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LDX_ABSOLUTE_Y   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LDX_ABSOLUTE_Y");

	addressing_ABSOLUTE_Y   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   x<=data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
LDX_setup_negative(instruction);
LDX_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LDX_IMMEDIATE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LDX_IMMEDIATE");

	addressing_IMMEDIATE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   x<=data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
LDX_setup_negative(instruction);
LDX_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LDX_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LDX_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   x<=data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
LDX_setup_negative(instruction);
LDX_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LDX_ZERO_PAGE_Y  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LDX_ZERO_PAGE_Y");

	addressing_ZERO_PAGE_Y  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    rd<=LO;\n   x<=data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
LDX_setup_negative(instruction);
LDX_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LDY_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LDY_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"  rd<=LO;\n   y<=data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
LDY_setup_negative(instruction);
LDY_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LDY_ABSOLUTE_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LDY_ABSOLUTE_X");

	addressing_ABSOLUTE_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"  rd<=LO;\n   y<=data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
LDY_setup_negative(instruction);
LDY_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LDY_IMMEDIATE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LDY_IMMEDIATE");

	addressing_IMMEDIATE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"  rd<=LO;\n   y<=data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
LDY_setup_negative(instruction);
LDY_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LDY_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LDY_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"  rd<=LO;\n   y<=data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
LDY_setup_negative(instruction);
LDY_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LDY_ZERO_PAGE_X  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LDY_ZERO_PAGE_X");

	addressing_ZERO_PAGE_X  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"  rd<=LO;\n   y<=data;\n");
fprintf(stdout,"\n-- end  start from strings--\n");
LDY_setup_negative(instruction);
LDY_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LSR_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LSR_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
LSR_setup_carry(instruction);
LSR_setup_negative(instruction);
LSR_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LSR_ABSOLUTE_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LSR_ABSOLUTE_X");

	addressing_ABSOLUTE_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
LSR_setup_carry(instruction);
LSR_setup_negative(instruction);
LSR_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LSR_ACCUMULATOR  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LSR_ACCUMULATOR");

	addressing_ACCUMULATOR  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
LSR_setup_carry(instruction);
LSR_setup_negative(instruction);
LSR_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LSR_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LSR_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
LSR_setup_carry(instruction);
LSR_setup_negative(instruction);
LSR_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_LSR_ZERO_PAGE_X  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "LSR_ZERO_PAGE_X");

	addressing_ZERO_PAGE_X  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
LSR_setup_carry(instruction);
LSR_setup_negative(instruction);
LSR_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_NOP_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "NOP_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;fprintf(stdout,"\n-- start from strings--\n");
fprintf(stdout,"    --- do nothing\n");
fprintf(stdout,"\n-- end  start from strings--\n");
	to_next_instruction(instruction);

}





void perform_ORA_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ORA_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ORA_setup_negative(instruction);
ORA_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ORA_ABSOLUTE_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ORA_ABSOLUTE_X");

	addressing_ABSOLUTE_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ORA_setup_negative(instruction);
ORA_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ORA_ABSOLUTE_Y   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ORA_ABSOLUTE_Y");

	addressing_ABSOLUTE_Y   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ORA_setup_negative(instruction);
ORA_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ORA_IMMEDIATE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ORA_IMMEDIATE");

	addressing_IMMEDIATE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ORA_setup_negative(instruction);
ORA_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ORA_INDIRECT_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ORA_INDIRECT_X");

	addressing_INDIRECT_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ORA_setup_negative(instruction);
ORA_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ORA_INDIRECT_Y   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ORA_INDIRECT_Y");

	addressing_INDIRECT_Y   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ORA_setup_negative(instruction);
ORA_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ORA_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ORA_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ORA_setup_negative(instruction);
ORA_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ORA_ZERO_PAGE_X  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ORA_ZERO_PAGE_X");

	addressing_ZERO_PAGE_X  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ORA_setup_negative(instruction);
ORA_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_PHA_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "PHA_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_PHP_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "PHP_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_PLA_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "PLA_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
PLA_setup_negative(instruction);
PLA_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_PLP_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "PLP_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
PLP_setup_carry(instruction);
PLP_setup_overflow(instruction);
PLP_setup_negative(instruction);
PLP_setup_zero(instruction);
PLP_setup_brk(instruction);
PLP_setup_irq(instruction);
PLP_setup_decimal(instruction);
	to_next_instruction(instruction);

}





void perform_RESET_INTERNAL     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "RESET_INTERNAL");

	addressing_INTERNAL     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
RESET_setup_irq(instruction);
	to_next_instruction(instruction);

}





void perform_ROL_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ROL_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ROL_setup_carry(instruction);
ROL_setup_negative(instruction);
ROL_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ROL_ABSOLUTE_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ROL_ABSOLUTE_X");

	addressing_ABSOLUTE_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ROL_setup_carry(instruction);
ROL_setup_negative(instruction);
ROL_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ROL_ACCUMULATOR  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ROL_ACCUMULATOR");

	addressing_ACCUMULATOR  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ROL_setup_carry(instruction);
ROL_setup_negative(instruction);
ROL_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ROL_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ROL_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ROL_setup_carry(instruction);
ROL_setup_negative(instruction);
ROL_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ROL_ZERO_PAGE_X  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ROL_ZERO_PAGE_X");

	addressing_ZERO_PAGE_X  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ROL_setup_carry(instruction);
ROL_setup_negative(instruction);
ROL_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ROR_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ROR_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ROR_setup_carry(instruction);
ROR_setup_negative(instruction);
ROR_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ROR_ABSOLUTE_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ROR_ABSOLUTE_X");

	addressing_ABSOLUTE_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ROR_setup_carry(instruction);
ROR_setup_negative(instruction);
ROR_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ROR_ACCUMULATOR  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ROR_ACCUMULATOR");

	addressing_ACCUMULATOR  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ROR_setup_carry(instruction);
ROR_setup_negative(instruction);
ROR_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ROR_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ROR_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ROR_setup_carry(instruction);
ROR_setup_negative(instruction);
ROR_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_ROR_ZERO_PAGE_X  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "ROR_ZERO_PAGE_X");

	addressing_ZERO_PAGE_X  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
ROR_setup_carry(instruction);
ROR_setup_negative(instruction);
ROR_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_RTI_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "RTI_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
RTI_setup_carry(instruction);
RTI_setup_overflow(instruction);
RTI_setup_negative(instruction);
RTI_setup_zero(instruction);
RTI_setup_brk(instruction);
RTI_setup_irq(instruction);
RTI_setup_decimal(instruction);
	to_next_instruction(instruction);

}





void perform_RTS_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "RTS_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_SBC_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "SBC_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
SBC_setup_carry(instruction);
SBC_setup_overflow(instruction);
SBC_setup_negative(instruction);
SBC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_SBC_ABSOLUTE_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "SBC_ABSOLUTE_X");

	addressing_ABSOLUTE_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
SBC_setup_carry(instruction);
SBC_setup_overflow(instruction);
SBC_setup_negative(instruction);
SBC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_SBC_ABSOLUTE_Y   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "SBC_ABSOLUTE_Y");

	addressing_ABSOLUTE_Y   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
SBC_setup_carry(instruction);
SBC_setup_overflow(instruction);
SBC_setup_negative(instruction);
SBC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_SBC_IMMEDIATE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "SBC_IMMEDIATE");

	addressing_IMMEDIATE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_SBC_INDIRECT_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "SBC_INDIRECT_X");

	addressing_INDIRECT_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
SBC_setup_carry(instruction);
SBC_setup_overflow(instruction);
SBC_setup_negative(instruction);
SBC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_SBC_INDIRECT_Y   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "SBC_INDIRECT_Y");

	addressing_INDIRECT_Y   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
SBC_setup_carry(instruction);
SBC_setup_overflow(instruction);
SBC_setup_negative(instruction);
SBC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_SBC_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "SBC_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
SBC_setup_carry(instruction);
SBC_setup_overflow(instruction);
SBC_setup_negative(instruction);
SBC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_SBC_ZERO_PAGE_X  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "SBC_ZERO_PAGE_X");

	addressing_ZERO_PAGE_X  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
SBC_setup_carry(instruction);
SBC_setup_overflow(instruction);
SBC_setup_negative(instruction);
SBC_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_SEC_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "SEC_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
SEC_setup_carry(instruction);
	to_next_instruction(instruction);

}





void perform_SED_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "SED_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
SED_setup_decimal(instruction);
	to_next_instruction(instruction);

}





void perform_SEI_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "SEI_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
SEI_setup_irq(instruction);
	to_next_instruction(instruction);

}





void perform_STA_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "STA_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_STA_ABSOLUTE_Y   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "STA_ABSOLUTE_Y");

	addressing_ABSOLUTE_Y   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_STA_INDIRECT_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "STA_INDIRECT_X");

	addressing_INDIRECT_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_STA_INDIRECT_Y   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "STA_INDIRECT_Y");

	addressing_INDIRECT_Y   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_STA_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "STA_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_STA_ZERO_PAGE_X  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "STA_ZERO_PAGE_X");

	addressing_ZERO_PAGE_X  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_STA_ABSOLUTE_X   (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "STA_ABSOLUTE_X");

	addressing_ABSOLUTE_X   (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_S_IRQ_INTERNAL     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "S_IRQ_INTERNAL");

	addressing_INTERNAL     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
S_IRQ_setup_irq(instruction);
	to_next_instruction(instruction);

}





void perform_S_NMI_INTERNAL     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "S_NMI_INTERNAL");

	addressing_INTERNAL     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
S_NMI_setup_irq(instruction);
	to_next_instruction(instruction);

}





void perform_STX_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "STX_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_STX_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "STX_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_STX_ZERO_PAGE_Y  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "STX_ZERO_PAGE_Y");

	addressing_ZERO_PAGE_Y  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_STY_ABSOLUTE     (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "STY_ABSOLUTE");

	addressing_ABSOLUTE     (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_STY_ZERO_PAGE    (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "STY_ZERO_PAGE");

	addressing_ZERO_PAGE    (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_STY_ZERO_PAGE_X  (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "STY_ZERO_PAGE_X");

	addressing_ZERO_PAGE_X  (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}





void perform_TAX_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "TAX_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
TAX_setup_negative(instruction);
TAX_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_TAY_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "TAY_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
TAY_setup_negative(instruction);
TAY_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_TSX_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "TSX_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
TSX_setup_negative(instruction);
TSX_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_TXA_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "TXA_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
TXA_setup_negative(instruction);
TXA_setup_zero(instruction);
	to_next_instruction(instruction);

}





void perform_TXS_IMPLIED      (INS *instruction) {
instruction->cycle=0;
strcpy(da_full_name, "TXS_IMPLIED");

	addressing_IMPLIED      (instruction);
fprintf(stdout, "when %s_STATE_%d=> --- OPERATION\n", da_full_name,  instruction->cycle);
;
	not_implemented(instruction); /*PERFORM THE OPERATION HERE */
	to_next_instruction(instruction);

}




