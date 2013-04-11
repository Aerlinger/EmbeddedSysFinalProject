#define CARRY_FLAG      0x01
#define OVERFLOW_FLAG   0x02
#define NEGATIVE_FLAG   0x04
#define ZERO_FLAG       0x08
#define BRK_FLAG        0x10
#define DECIMAL_FLAG    0x20
#define IRQ_FLAG        0x40

enum addressing_modes {
	ABSOLUTE,
	ABSOLUTE_X,
	ABSOLUTE_Y,
	IMMEDIATE,
	INDIRECT_X,
	INDIRECT_Y,
	ZERO_PAGE,
	ZERO_PAGE_X,
	ZERO_PAGE_Y,
	RELATIVE,
	IMPLIED,
	ACCUMULATOR,
	INDIRECT,
	INTERNAL,

	BAD_MODE
};

struct addressing_mode_s {
	char *addressing_mode_string;
	int addressing_mode;
};

enum token_type {
	FONT_TOKEN,
	END_FONT_TOKEN,
	END_TD_TOKEN,
	END_TR_TOKEN,
	END_P_TOKEN,
	P_TOKEN,
	TR_TOKEN,
	TD_TOKEN,
	COMMENT_TOKEN,
	END_COMMENT_TOKEN,
	USER_STRING_TOKEN
};

struct string_token {
	char *token_string;
	int token;
};


#ifndef MAIN
extern struct addressing_mode_s modes[];
#else
struct addressing_mode_s modes[] ={
	{"ABS",    ABSOLUTE},
	{"ABS,X",  ABSOLUTE_X},
	{"ABS,Y",  ABSOLUTE_Y},
	{"IMM",    IMMEDIATE},
	{"(IND,X)",    INDIRECT_X},
	{"(IND),Y",    INDIRECT_Y},
	{"Z-PAGE",   ZERO_PAGE},
	{"Z-PAGE,X",   ZERO_PAGE_X},
	{"Z-PAGE,Y",   ZERO_PAGE_Y},
	{"REL",        RELATIVE},
	{"IMP",        IMPLIED},
	{"ACC",       ACCUMULATOR},
	{"(IND)",       INDIRECT},
	{"INTERNAL",       INTERNAL},
};
#endif
	
#ifndef MAIN
extern struct string_token my_tokens[]  ;
#else
struct string_token my_tokens[]  =
{
	{"<FONT", FONT_TOKEN},
	{"</FONT", END_FONT_TOKEN},
	{"</TD", END_TD_TOKEN},
	{"</TR", END_TR_TOKEN},
	{"</P" , END_P_TOKEN},
	{"<TR",  TR_TOKEN},
	{"<!--" , COMMENT_TOKEN},
	{"<P" , P_TOKEN},
	{"<TD", TD_TOKEN},
};
#endif

#define MAX_TOKEN_SIZE (256)

#define TARGET_IS_NONE        0
#define TARGET_IS_ACCUMULATOR 1
#define TARGET_IS_X           2
#define TARGET_IS_Y           3
#define TARGET_IS_MEMORY      4


struct INSTRUCTION_S  {
	char mnemonic[16];
	unsigned int mode;
	unsigned int opcode;
	/**unsigned int target;***/
	
	unsigned int flags; /*flags changed by instruction: negative, zero, carry, decimal */
	unsigned int  operation_target; /*  ACC, X, Y, MEMORY, NONE */
	unsigned short cycle;
};

#define MAX_INSTRUCTION (1000)
/*
 * automatically generated  by poc.c itself
 */

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


void init_vhdl_code();
extern char *strings[];
void ADC_setup_zero(struct INSTRUCTION_S *instruction);
void ADC_setup_negative(struct INSTRUCTION_S *instruction);
void ADC_setup_overflow(struct INSTRUCTION_S *instruction);
void ADC_setup_carry(struct INSTRUCTION_S *instruction);
void addressing_ABSOLUTE(struct INSTRUCTION_S *instruction);
void addressing_ABSOLUTE_X(struct INSTRUCTION_S *instruction);
void addressing_ABSOLUTE_Y(struct INSTRUCTION_S *instruction);
void addressing_IMMEDIATE(struct INSTRUCTION_S *instruction);
void addressing_INDIRECT_X(struct INSTRUCTION_S *instruction);
void addressing_INDIRECT_Y(struct INSTRUCTION_S *instruction);
void addressing_ZERO_PAGE(struct INSTRUCTION_S *instruction);
void addressing_ZERO_PAGE_X(struct INSTRUCTION_S *instruction);
void AND_setup_zero(struct INSTRUCTION_S *instruction);
void AND_setup_negative(struct INSTRUCTION_S *instruction);
void ASL_setup_zero(struct INSTRUCTION_S *instruction);
void ASL_setup_negative(struct INSTRUCTION_S *instruction);
void ASL_setup_carry(struct INSTRUCTION_S *instruction);
void addressing_ACCUMULATOR(struct INSTRUCTION_S *instruction);
void addressing_RELATIVE(struct INSTRUCTION_S *instruction);
void BIT_setup_zero(struct INSTRUCTION_S *instruction);
void BIT_setup_negative(struct INSTRUCTION_S *instruction);
void BIT_setup_overflow(struct INSTRUCTION_S *instruction);
void BRK_setup_brk(struct INSTRUCTION_S *instruction);
void addressing_IMPLIED(struct INSTRUCTION_S *instruction);
void CLC_setup_carry(struct INSTRUCTION_S *instruction);
void CLD_setup_decimal(struct INSTRUCTION_S *instruction);
void CLI_setup_irq(struct INSTRUCTION_S *instruction);
void CLV_setup_overflow(struct INSTRUCTION_S *instruction);
void CMP_setup_zero(struct INSTRUCTION_S *instruction);
void CMP_setup_negative(struct INSTRUCTION_S *instruction);
void CMP_setup_carry(struct INSTRUCTION_S *instruction);
void CPX_setup_zero(struct INSTRUCTION_S *instruction);
void CPX_setup_negative(struct INSTRUCTION_S *instruction);
void CPX_setup_carry(struct INSTRUCTION_S *instruction);
void CPY_setup_zero(struct INSTRUCTION_S *instruction);
void CPY_setup_negative(struct INSTRUCTION_S *instruction);
void CPY_setup_carry(struct INSTRUCTION_S *instruction);
void DEC_setup_zero(struct INSTRUCTION_S *instruction);
void DEC_setup_negative(struct INSTRUCTION_S *instruction);
void DEX_setup_zero(struct INSTRUCTION_S *instruction);
void DEX_setup_negative(struct INSTRUCTION_S *instruction);
void DEY_setup_zero(struct INSTRUCTION_S *instruction);
void DEY_setup_negative(struct INSTRUCTION_S *instruction);
void EOR_setup_zero(struct INSTRUCTION_S *instruction);
void EOR_setup_negative(struct INSTRUCTION_S *instruction);
void INC_setup_zero(struct INSTRUCTION_S *instruction);
void INC_setup_negative(struct INSTRUCTION_S *instruction);
void INX_setup_zero(struct INSTRUCTION_S *instruction);
void INX_setup_negative(struct INSTRUCTION_S *instruction);
void INY_setup_zero(struct INSTRUCTION_S *instruction);
void INY_setup_negative(struct INSTRUCTION_S *instruction);
void addressing_INDIRECT(struct INSTRUCTION_S *instruction);
void LDA_setup_zero(struct INSTRUCTION_S *instruction);
void LDA_setup_negative(struct INSTRUCTION_S *instruction);
void LDX_setup_zero(struct INSTRUCTION_S *instruction);
void LDX_setup_negative(struct INSTRUCTION_S *instruction);
void addressing_ZERO_PAGE_Y(struct INSTRUCTION_S *instruction);
void LDY_setup_zero(struct INSTRUCTION_S *instruction);
void LDY_setup_negative(struct INSTRUCTION_S *instruction);
void LSR_setup_zero(struct INSTRUCTION_S *instruction);
void LSR_setup_negative(struct INSTRUCTION_S *instruction);
void LSR_setup_carry(struct INSTRUCTION_S *instruction);
void ORA_setup_zero(struct INSTRUCTION_S *instruction);
void ORA_setup_negative(struct INSTRUCTION_S *instruction);
void PLA_setup_zero(struct INSTRUCTION_S *instruction);
void PLA_setup_negative(struct INSTRUCTION_S *instruction);
void PLP_setup_decimal(struct INSTRUCTION_S *instruction);
void PLP_setup_irq(struct INSTRUCTION_S *instruction);
void PLP_setup_brk(struct INSTRUCTION_S *instruction);
void PLP_setup_zero(struct INSTRUCTION_S *instruction);
void PLP_setup_negative(struct INSTRUCTION_S *instruction);
void PLP_setup_overflow(struct INSTRUCTION_S *instruction);
void PLP_setup_carry(struct INSTRUCTION_S *instruction);
void RESET_setup_irq(struct INSTRUCTION_S *instruction);
void addressing_INTERNAL(struct INSTRUCTION_S *instruction);
void ROL_setup_zero(struct INSTRUCTION_S *instruction);
void ROL_setup_negative(struct INSTRUCTION_S *instruction);
void ROL_setup_carry(struct INSTRUCTION_S *instruction);
void ROR_setup_zero(struct INSTRUCTION_S *instruction);
void ROR_setup_negative(struct INSTRUCTION_S *instruction);
void ROR_setup_carry(struct INSTRUCTION_S *instruction);
void RTI_setup_decimal(struct INSTRUCTION_S *instruction);
void RTI_setup_irq(struct INSTRUCTION_S *instruction);
void RTI_setup_brk(struct INSTRUCTION_S *instruction);
void RTI_setup_zero(struct INSTRUCTION_S *instruction);
void RTI_setup_negative(struct INSTRUCTION_S *instruction);
void RTI_setup_overflow(struct INSTRUCTION_S *instruction);
void RTI_setup_carry(struct INSTRUCTION_S *instruction);
void SBC_setup_zero(struct INSTRUCTION_S *instruction);
void SBC_setup_negative(struct INSTRUCTION_S *instruction);
void SBC_setup_overflow(struct INSTRUCTION_S *instruction);
void SBC_setup_carry(struct INSTRUCTION_S *instruction);
void SEC_setup_carry(struct INSTRUCTION_S *instruction);
void SED_setup_decimal(struct INSTRUCTION_S *instruction);
void SEI_setup_irq(struct INSTRUCTION_S *instruction);
void S_IRQ_setup_irq(struct INSTRUCTION_S *instruction);
void S_NMI_setup_irq(struct INSTRUCTION_S *instruction);
void TAX_setup_zero(struct INSTRUCTION_S *instruction);
void TAX_setup_negative(struct INSTRUCTION_S *instruction);
void TAY_setup_zero(struct INSTRUCTION_S *instruction);
void TAY_setup_negative(struct INSTRUCTION_S *instruction);
void TSX_setup_zero(struct INSTRUCTION_S *instruction);
void TSX_setup_negative(struct INSTRUCTION_S *instruction);
void TXA_setup_zero(struct INSTRUCTION_S *instruction);
void TXA_setup_negative(struct INSTRUCTION_S *instruction);
extern char da_full_name[];
