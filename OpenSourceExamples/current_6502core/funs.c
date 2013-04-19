/* NOT generated */
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "externs.h"

char da_full_name[100];


void to_next_instruction( INS *ip)
{
fprintf(stdout, "    next_state<=NEW_INSTRUCTION;\n");

}

void not_implementedI(INS *ip)
{
fprintf(stdout, "---- NOT IMPLEMENTED \n");
}

void clear_carry(INS *ip)
{
fprintf(stdout, "\ncarry<='0';\n");
}

void clear_overflow(INS *ip)
{
	fprintf(stdout, "\noverflow<='0';\n");
}
void clear_decimal(INS *ip)
{
	fprintf(stdout, "\ndecimal<='0';\n");
}

void set_decimal(INS *ip)
{
	fprintf(stdout, "\ndecimal<='1';\n");
}
void set_carry(INS *ip)
{
	fprintf(stdout, "\ncarry<='1';\n");
}

void not_implemented(INS *ip)
{
	fprintf(stdout, "----- NOT IMPLEMENTED (no string)\n");
}

/* THE PRIORITY */

void addressing_ABSOLUTE(struct INSTRUCTION_S *instruction){

	fprintf(stdout, "\nwhen %s_STATE_0=>\n", da_full_name);
	fprintf(stdout, "       mem_addr<=pc_r;\n");
	fprintf(stdout, "       next_state<=%s_STATE_1;\n", da_full_name);

fprintf(stdout, "\nwhen %s_STATE_1=>\n", da_full_name);
		fprintf(stdout, "    rd<=LO;\n");
		fprintf(stdout, "    addr_lo<=data;\n");
		fprintf(stdout, "    next_state<=%s_STATE_2;\n", da_full_name);

fprintf(stdout, "\nwhen %s_STATE_2=>\n", da_full_name);
		fprintf(stdout, "     mem_addr<=mem_addr_r+1;\n");
		fprintf(stdout, "     next_state<=%s_STATE_3;\n", da_full_name);

fprintf(stdout, "\nwhen %s_STATE_3=>\n", da_full_name);
		fprintf(stdout, "    rd<=LO;\n");
		fprintf(stdout, "      addr_hi<=data;\n");
		fprintf(stdout, "      next_state<=%s_STATE_4;\n", da_full_name);

fprintf(stdout, "\nwhen %s_STATE_4=>\n", da_full_name);
		fprintf(stdout, "     mem_addr<=addr_hi_r&addr_lo_r;\n");
		fprintf(stdout, "     pc<=pc_r+2;\n");
		fprintf(stdout, "     next_state<=%s_STATE_5;\n", da_full_name);
		fprintf(stdout, "\n");
	instruction->cycle =5;
}


void addressing_IMMEDIATE(struct INSTRUCTION_S *instruction){ 
	fprintf(stdout, "\nwhen %s_STATE_0=>\n", da_full_name);
	fprintf(stdout, "       mem_addr<=pc_r;\n");
	fprintf(stdout, "       pc<=pc_r+1;\n");
	fprintf(stdout, "       next_state<=%s_STATE_1;\n", da_full_name);

	instruction->cycle=1;
	return;
}


void addressing_ZERO_PAGE(struct INSTRUCTION_S *instruction){ 
	fprintf(stdout, "\nwhen %s_STATE_0=>\n", da_full_name);
	fprintf(stdout, "       mem_addr<=pc_r;\n");
	fprintf(stdout, "       next_state<=%s_STATE_1;\n", da_full_name);

fprintf(stdout, "\nwhen %s_STATE_1=>\n", da_full_name);
		fprintf(stdout, "    rd<=LO;\n");
		fprintf(stdout, "    addr_lo<=data;\n");
		fprintf(stdout, "    next_state<=%s_STATE_2;\n", da_full_name);


fprintf(stdout, "\nwhen %s_STATE_2=>\n", da_full_name);
		fprintf(stdout, "     mem_addr<=\"00000000\" & addr_lo_r;\n");
		fprintf(stdout, "     pc<=pc_r+1;\n");
		fprintf(stdout, "     next_state<=%s_STATE_3;\n", da_full_name);
		fprintf(stdout, "\n");
	instruction->cycle =3;

}

void addressing_ABSOLUTE_X(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- absolute_x NOT IMPLEMENTED ----\n");}
void addressing_ABSOLUTE_Y(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- absolute_y NOT IMPLEMENTED ----\n");}
void addressing_INDIRECT_X(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- indirect_x NOT IMPLEMENTED ----\n");}
void addressing_INDIRECT_Y(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- indirect_y NOT IMPLEMENTED ----\n");}
void addressing_ZERO_PAGE_X(struct INSTRUCTION_S *instruction){ fprintf(stdout, "---zeropagex NOT IMPLEMENTED ----\n");}
void addressing_ACCUMULATOR(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- accumulator NOT IMPLEMENTED ----\n");}
void addressing_RELATIVE(struct INSTRUCTION_S *instruction){ fprintf(stdout, "---  relative NOT IMPLEMENTED ----\n");}
void addressing_IMPLIED(struct INSTRUCTION_S *instruction){ fprintf(stdout, "---  implied NOT IMPLEMENTED ----\n");}
void addressing_INDIRECT(struct INSTRUCTION_S *instruction){ fprintf(stdout, "---indirect NOT IMPLEMENTED ----\n");}
void addressing_ZERO_PAGE_Y(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- zeropage_y NOT IMPLEMENTED ----\n");}
void addressing_INTERNAL(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- internal NOT IMPLEMENTED ----\n");}


void DEC_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void DEC_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void DEX_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void DEX_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void DEY_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void DEY_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void LDA_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void LDA_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}



void ADC_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void ADC_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void ADC_setup_overflow(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void ADC_setup_carry(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}




void AND_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void AND_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void ASL_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void ASL_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void ASL_setup_carry(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}


void BIT_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void BIT_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void BIT_setup_overflow(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void BRK_setup_brk(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void CLC_setup_carry(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void CLD_setup_decimal(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void CLI_setup_irq(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void CLV_setup_overflow(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void CMP_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void CMP_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void CMP_setup_carry(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void CPX_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void CPX_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void CPX_setup_carry(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void CPY_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void CPY_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void CPY_setup_carry(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void EOR_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void EOR_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void INC_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void INC_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void INX_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void INX_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void INY_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void INY_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}



void LDX_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void LDX_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void LDY_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void LDY_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void LSR_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void LSR_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void LSR_setup_carry(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void ORA_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void ORA_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void PLA_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void PLA_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void PLP_setup_decimal(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void PLP_setup_irq(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void PLP_setup_brk(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void PLP_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void PLP_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void PLP_setup_overflow(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void PLP_setup_carry(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void RESET_setup_irq(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void ROL_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void ROL_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void ROL_setup_carry(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void ROR_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void ROR_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void ROR_setup_carry(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void RTI_setup_decimal(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void RTI_setup_irq(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void RTI_setup_brk(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void RTI_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void RTI_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void RTI_setup_overflow(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void RTI_setup_carry(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void SBC_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void SBC_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void SBC_setup_overflow(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void SBC_setup_carry(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void SEC_setup_carry(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void SED_setup_decimal(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void SEI_setup_irq(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void S_IRQ_setup_irq(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void S_NMI_setup_irq(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void TAX_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void TAX_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void TAY_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void TAY_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void TSX_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void TSX_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void TXA_setup_zero(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
void TXA_setup_negative(struct INSTRUCTION_S *instruction){ fprintf(stdout, "--- NOT IMPLEMENTED ----\n");}
