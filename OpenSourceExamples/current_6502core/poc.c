/***********************************************************
 * nov 2003 
 * Parse OpCodes (poc.c) - 6502 opcodes
 * parse opcodes    
 *
 * Usage: 
   a) poc ops   # ops is the html file that contains the instructions
 *
 * b) poc ops -v  # dumps all sort of info
 ***********************************************************/

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAIN
#include "defs.h"

#define stderr_out  fprintf
 
struct INSTRUCTION_S instruction_array[MAX_INSTRUCTION];

#define TARGET_SIZE (256)
unsigned int targets[TARGET_SIZE];
int debug_op =0;

void dump_states();
int never();
char token_string[MAX_TOKEN_SIZE];
void dump_strings(int );
void fill_with_full_names();
void init_targets_with_values();
void dump_defines(int );
void dump_strat(int);
extern void dump_instructions(int );
int line_count = 1;
int current_instruction=0;
extern int debug_op;
FILE *ns_file=0;
FILE *fp =0; 
char *full_names[TARGET_SIZE];
void take_care_of_flag(struct INSTRUCTION_S *ip);
int never()
{
	return 0;
}
void add_mode(struct INSTRUCTION_S *instruction_ptr, unsigned int mode)
{
if (debug_op) fprintf(stdout, "add_mode..%u\n", mode);

instruction_ptr->mode=mode;
}

void add_flags(struct INSTRUCTION_S *ip, char *flags)
{
	int i;
	int len;
	ip->flags = 0;

	if (strcmp(flags, "all")==0) {
	ip->flags |= CARRY_FLAG;
	ip->flags |= OVERFLOW_FLAG;
	ip->flags |= NEGATIVE_FLAG;
	ip->flags |= ZERO_FLAG;
	ip->flags |= BRK_FLAG;
	ip->flags |= IRQ_FLAG;
	ip->flags |= DECIMAL_FLAG;
	return;
	}

	len = strlen(flags);
	for (i = 0; i<len; i++)
	{
	char c=flags[i];
	if      (c=='C') ip->flags |= CARRY_FLAG;
	else if (c=='V') ip->flags |= OVERFLOW_FLAG;
	else if (c=='N') ip->flags |= NEGATIVE_FLAG;
	else if (c=='Z') ip->flags |= ZERO_FLAG;
	else if (c=='B') ip->flags |= BRK_FLAG;
	else if (c=='I') ip->flags |= IRQ_FLAG;
	else if (c=='D') ip->flags |= DECIMAL_FLAG;
	else {
		fprintf(stderr, "UNHANDLED FLAG (%c, %s)\n", c, flags);
		exit(0);
	}
	}
}

void add_opcode(struct INSTRUCTION_S *instruction_ptr, unsigned int opcode)
{
if (debug_op) fprintf(stdout, "add_opcode...\n");
instruction_ptr->opcode=opcode;
}

void add_mnemonic(struct INSTRUCTION_S *instruction_ptr, char *mnemonic)
{
if (debug_op) fprintf(stdout, "add_mnemonic...\n");
strcpy(instruction_ptr->mnemonic, mnemonic);
}

int do_ungetc(FILE *fp, int c)
{
	ungetc(c, fp);
	return c;
}

int do_getc(FILE *fp)
{
	int c = getc(fp);
	if (c=='\n')
		line_count++;
	if (c==EOF)
		exit(0);
	
	return c;
}

int get_token(FILE *fp)
{
	int j = 0;
	int i=0;
	int c;

	memset(token_string, 0, sizeof token_string);
	while ((c =do_getc(fp))) {
		if (!isspace(c))
			break;
	}
	i=0;
	token_string[i++]=c;
	if (c=='<') {
		while ((c=do_getc(fp))!='>' && i< sizeof token_string)
			token_string[i++]=c;
		if (i>=sizeof token_string){
			stderr_out(stderr, "ERROR: string too long at line ...%d\r\n", line_count);
			exit(0);
		}
	}
	else
	while (!isspace(c=do_getc(fp))){
		if (c=='<') {
			do_ungetc(fp, c);
			break;
		}
		token_string[i++]=c;
	}
	token_string[i] = 0;
	for (j = 0; j < sizeof  my_tokens/sizeof my_tokens[0]; j++)
		if (memcmp(token_string, my_tokens[j]. token_string, 
			strlen(my_tokens[j].token_string))==0)
				return my_tokens[j].token;

	return USER_STRING_TOKEN;
		
}


int expect(int token)
{
int new_token =get_token(fp);
if (new_token!=token) {
stderr_out(stderr, "ERROR: Unexpected token...at line %d (%s)\r\n", line_count, token_string);fflush(stdout);
}
return new_token;

}

int parse_it(FILE *fp)
{
	
	char mnemonics[20];
	int op_code;
	int token;
	int k; 
	int found_mode=0;
	for (current_instruction=0; ; current_instruction++) {

		expect(TR_TOKEN);
		expect(TD_TOKEN);
		expect(COMMENT_TOKEN);
		expect(FONT_TOKEN);
		expect(FONT_TOKEN);
		expect(P_TOKEN);
		get_token(fp); /* instruction mnemonics */
		
		strcpy(mnemonics, token_string);

		if (debug_op) {
		fprintf(stdout, "\nthe token is [%s]\r\n", token_string);
		fflush(stdout);
		}
		add_mnemonic(&instruction_array[current_instruction], token_string);

		expect(END_FONT_TOKEN);
		expect(COMMENT_TOKEN);
		expect(END_FONT_TOKEN);
		expect(END_P_TOKEN);
		expect(END_TD_TOKEN);

		expect(TD_TOKEN);
		expect(COMMENT_TOKEN);
		expect(FONT_TOKEN);
		expect(FONT_TOKEN);
		expect(P_TOKEN);
		get_token(fp); /* addressing mode */
		if (debug_op) {
		fprintf(stdout, "\nthe token is [%s]\r\n", token_string);
		fflush(stdout);
		}
		found_mode=0;
		for (k =0; k < sizeof modes/ sizeof modes[0]; k++)
			if (
			strlen(modes[k].addressing_mode_string) == strlen(token_string) &&
			memcmp(modes[k].addressing_mode_string, token_string, strlen(modes[k].addressing_mode_string))==0)
			{
			found_mode=1;
		add_mode(&instruction_array[current_instruction], modes[k].addressing_mode);
			break;
			}
		if (found_mode==0)
		{
			stderr_out(stderr, "ERROR: Unable to find mode (%s)\r\n", token_string);
		}

		expect(END_FONT_TOKEN);
		expect(COMMENT_TOKEN);
		expect(END_FONT_TOKEN);
		expect(END_P_TOKEN);
		expect(END_TD_TOKEN);

		expect(TD_TOKEN);
		expect(COMMENT_TOKEN);
		expect(FONT_TOKEN);
		expect(FONT_TOKEN);
		expect(P_TOKEN);
		get_token(fp); /* hex opcode */
		sscanf(token_string, "%x", &op_code);
		if (debug_op) {
		fprintf(stdout, "\nthe token is [%s]\r\n", token_string);
		fflush(stdout);
		}
		add_opcode(&instruction_array[current_instruction], op_code);
		/** current_instruction++;***/
		expect(END_FONT_TOKEN);
		expect(COMMENT_TOKEN);
		expect(END_FONT_TOKEN);
		expect(END_P_TOKEN);
		expect(END_TD_TOKEN);

		expect(TD_TOKEN);
		expect(COMMENT_TOKEN);
		expect(FONT_TOKEN);
		expect(FONT_TOKEN);
		expect(P_TOKEN);
		get_token(fp); /* original clocks */
		if (debug_op) {
		fprintf(stdout, "\nthe token is [%s]\r\n", token_string);
		fflush(stdout);
		}
		expect(END_FONT_TOKEN);
		expect(COMMENT_TOKEN);
		expect(END_FONT_TOKEN);
		expect(END_P_TOKEN);
		expect(END_TD_TOKEN);

		expect(TD_TOKEN);
		expect(COMMENT_TOKEN);
		expect(FONT_TOKEN);
		expect(FONT_TOKEN);
		expect(P_TOKEN);
		get_token(fp); /* free 6502 clocks */
		if (debug_op) {
		fprintf(stdout, "\nthe token is [%s]\r\n", token_string);
		fflush(stdout);
		}
		expect(END_FONT_TOKEN);
		expect(COMMENT_TOKEN);
		expect(END_FONT_TOKEN);
		expect(END_P_TOKEN);
		expect(END_TD_TOKEN);

		expect(TD_TOKEN);
		expect(COMMENT_TOKEN);
		expect(FONT_TOKEN);
		token=get_token(fp);
		if(token==FONT_TOKEN)
		{/* 2 fonts in a row */
		expect(P_TOKEN);
		get_token(fp);/* Flags */
		add_flags(&instruction_array[current_instruction],token_string);
		if (debug_op) {
		fprintf(stdout, "\nthe token is flags=[%s]\r\n", token_string);
		fflush(stdout);
		}
		expect(END_FONT_TOKEN);
		expect(COMMENT_TOKEN);
		expect(END_FONT_TOKEN);
		expect(END_P_TOKEN);
		expect(END_TD_TOKEN);


		expect(END_TR_TOKEN);
		}
		else if (token==P_TOKEN) /* instruction like BCC */
		{
		expect(END_P_TOKEN);
		expect(COMMENT_TOKEN);
		expect(END_FONT_TOKEN);
		expect(END_TD_TOKEN);
		expect(END_TR_TOKEN);
		}
		/* last instruction in the table (alphabetically) */
		if (strcmp(mnemonics, "TYA")==0 && op_code==0x98)
			return 0; /*  exit(0);*/
	}
}


int main(int argc, char *argv[])
{
	int c, i;

	for (i = 0; i< TARGET_SIZE; i++)
		targets[i]=TARGET_IS_NONE;
	init_targets_with_values();
	init_vhdl_code();

	fill_with_full_names();
	if (argc!=2 && argc!=3) {
		stderr_out(stderr, "ERROR: Need a filename...\r\n");
		exit(0);
	}
	if (argc==3) debug_op++;
	fp=fopen(argv[1], "r");
	if (fp==0) {
		stderr_out(stderr, "ERROR: Unable to open file for reading\r\n");
		exit(0);
	}
	
	parse_it(fp);
	
	if(debug_op)fprintf(stdout, "\r\n\r\n\r\nINSTRUCTIONS LISTING...\n");
		dump_instructions(BAD_MODE); /* get everyting */
	if(debug_op)fprintf(stdout, "\r\n\r\n\r\nEND INSTRUCTIONS LISTING...\n");


		/* now get instructions grouped by addressing mode */

		if(debug_op)fprintf(stdout, "\n\n\n-------\nABSOLUTE ONLY\n");dump_instructions(ABSOLUTE);
	if(debug_op)fprintf(stdout, "ABSOLUTE_X ONLY\n");dump_instructions(ABSOLUTE_X);
	if(debug_op)fprintf(stdout, "ABSOLUTE_Y ONLY\n");dump_instructions(ABSOLUTE_Y);
	if(debug_op)fprintf(stdout, "IMMEDIATE ONLY\n");dump_instructions(IMMEDIATE);
	if(debug_op)fprintf(stdout, "INDIRECT_X ONLY\n");dump_instructions(INDIRECT_X);
	if(debug_op)fprintf(stdout, "INDIRECT_Y ONLY\n");dump_instructions(INDIRECT_Y);
	if(debug_op)fprintf(stdout, "ZERO_PAGE ONLY\n");dump_instructions(ZERO_PAGE);
	if(debug_op)fprintf(stdout, "ZERO_PAGE_X ONLY\n");dump_instructions(ZERO_PAGE_X);
	if(debug_op)fprintf(stdout, "ZERO_PAGE_Y ONLY\n");dump_instructions(ZERO_PAGE_Y);
	if(debug_op)fprintf(stdout, "RELATIVE ONLY\n");dump_instructions(RELATIVE);
	if(debug_op)fprintf(stdout, "IMPLIED ONLY\n");dump_instructions(IMPLIED);
	if(debug_op)fprintf(stdout, "ACCUMULATOR ONLY\n");dump_instructions(ACCUMULATOR);
	if(debug_op)fprintf(stdout, "INDIRECT ONLY\n");dump_instructions(INDIRECT);
	if(debug_op)fprintf(stdout, "INTERNAL ONLY\n");dump_instructions(INTERNAL);


	/* now dump the #defines and C code that will produce the core */

	ns_file=fopen("ns.c", "w");
	if (ns_file==0)
	{
	fprintf(stderr, "Can't open ns.c for writing...\n");
	exit(0);
	}
	fprintf(ns_file,"\n/* AUTOMATICALLY GENERATED, DO NOT MODIFY */\n\n");
	fprintf(ns_file, "#include <stdio.h>\n");
	fprintf(ns_file, "#include <stdlib.h>\n");
	fprintf(ns_file, "#include \"defs.h\"\n");
	fprintf(ns_file, "#define INS struct INSTRUCTION_S\n");
	fprintf(ns_file, "\n\n\n\n");
	dump_defines(BAD_MODE);
	dump_strat(BAD_MODE);
	/*** fprintf(ns_file, "\n\nmain() {}\n\n");***/
	dump_strings(BAD_MODE);
	dump_states();
}

void get_opcode_bin(int opcode, char *s)
{
	if (opcode&(1u<<7))  *s='1'; s++;
	if (opcode&(1u<<6))  *s='1'; s++;
	if (opcode&(1u<<5))  *s='1'; s++;
	if (opcode&(1u<<4))  *s='1'; s++;

	if (opcode&(1u<<3))  *s='1'; s++;
	if (opcode&(1u<<2))  *s='1'; s++;
	if (opcode&(1u<<1))  *s='1'; s++;
	if (opcode&(1u<<0))  *s='1'; s++;
}



void dump_instructions(int target_mode)
{
	int i;
	char bin_string[8+1];

	bin_string[8]=0;
	for (i = 0; i < current_instruction; i++)
	{
	if ((target_mode== ABSOLUTE ||
	target_mode==ABSOLUTE_X ||
	target_mode==ABSOLUTE_Y ||
	target_mode==IMMEDIATE ||
	target_mode==INDIRECT_X ||
	target_mode==INDIRECT_Y ||
	target_mode==ZERO_PAGE ||
	target_mode==ZERO_PAGE_X ||
	target_mode==ZERO_PAGE_Y ||
	target_mode==RELATIVE ||
	target_mode==IMPLIED ||
	target_mode==ACCUMULATOR ||
	target_mode==INDIRECT ||
	target_mode==INTERNAL)
	&& target_mode!=instruction_array[i].mode)
		continue;

	memset(bin_string, '0', sizeof bin_string-1);
	if(debug_op)fprintf(stdout, "{\"%s\",  ",  instruction_array[i].mnemonic);

	switch(instruction_array[i].mode) {
	case ABSOLUTE   :if(debug_op)fprintf(stdout, "ABSOLUTE     "); break;
	case ABSOLUTE_X :if(debug_op)fprintf(stdout, "ABSOLUTE_X   "); break;
	case ABSOLUTE_Y :if(debug_op)fprintf(stdout, "ABSOLUTE_Y   "); break;
	case IMMEDIATE  :if(debug_op)fprintf(stdout, "IMMEDIATE    "); break;
	case INDIRECT_X :if(debug_op)fprintf(stdout, "INDIRECT_X   "); break;
	case INDIRECT_Y :if(debug_op)fprintf(stdout, "INDIRECT_Y   "); break;
	case ZERO_PAGE  :if(debug_op)fprintf(stdout, "ZERO_PAGE    "); break;
	case ZERO_PAGE_X:if(debug_op)fprintf(stdout, "ZERO_PAGE_X  "); break;
	case ZERO_PAGE_Y:if(debug_op)fprintf(stdout, "ZERO_PAGE_Y  "); break;
	case RELATIVE :  if(debug_op)fprintf(stdout, "RELATIVE     "); break;
	case IMPLIED :   if(debug_op)fprintf(stdout, "IMPLIED      "); break;
	case ACCUMULATOR:if(debug_op)fprintf(stdout, "ACCUMULATOR  "); break;
	case INDIRECT :  if(debug_op)fprintf(stdout, "INDIRECT     "); break;
	case INTERNAL :  if(debug_op)fprintf(stdout, "INTERNAL     "); break;
	default: if(debug_op)fprintf(stdout,         "UNKNOWN MODE "); break;
	}

	if(debug_op)fprintf(stdout, ", 0x%02x},  # ", instruction_array[i].opcode, bin_string);
	get_opcode_bin(instruction_array[i].opcode, bin_string);

	if(debug_op)fprintf(stdout, " ^constant %s_",  instruction_array[i].mnemonic);
	switch(instruction_array[i].mode) {
	case ABSOLUTE   :if(debug_op)fprintf(stdout, "ABSOLUTE     "); break;
	case ABSOLUTE_X :if(debug_op)fprintf(stdout, "ABSOLUTE_X   "); break;
	case ABSOLUTE_Y :if(debug_op)fprintf(stdout, "ABSOLUTE_Y   "); break;
	case IMMEDIATE  :if(debug_op)fprintf(stdout, "IMMEDIATE    "); break;
	case INDIRECT_X :if(debug_op)fprintf(stdout, "INDIRECT_X   "); break;
	case INDIRECT_Y :if(debug_op)fprintf(stdout, "INDIRECT_Y   "); break;
	case ZERO_PAGE  :if(debug_op)fprintf(stdout, "ZERO_PAGE    "); break;
	case ZERO_PAGE_X:if(debug_op)fprintf(stdout, "ZERO_PAGE_X  "); break;
	case ZERO_PAGE_Y:if(debug_op)fprintf(stdout, "ZERO_PAGE_Y  "); break;
	case RELATIVE :  if(debug_op)fprintf(stdout, "RELATIVE     "); break;
	case IMPLIED :   if(debug_op)fprintf(stdout, "IMPLIED      "); break;
	case ACCUMULATOR:if(debug_op)fprintf(stdout, "ACCUMULATOR  "); break;
	case INDIRECT :  if(debug_op)fprintf(stdout, "INDIRECT     "); break;
	case INTERNAL :  if(debug_op)fprintf(stdout, "INTERNAL     "); break;
	default: if(debug_op)fprintf(stdout,         "UNKNOWN MODE "); break;
	}
	if(debug_op)fprintf(stdout, ": std_logic_vector (7 downto 0):=");
	if(debug_op)fprintf(stdout, ",  \"%s\";\n",  bin_string);
	}
}

/******* EMBEDDED TABLE OF INSTRUCTIONS (from the 6502 free core)**********

          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ADC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6D</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NVZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ADC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7D</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NVZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ADC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,Y</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>79</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NVZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ADC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMM</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>69</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NVZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ADC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>(IND,X)</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>61</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NVZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ADC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>(IND),Y</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>71</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NVZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ADC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>65</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NVZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ADC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>75</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NVZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>AND</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2D</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>AND</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3D</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>AND</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,Y</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>39</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>AND</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMM</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>29</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>AND</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>(IND,X)</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>21</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>AND</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>(IND),Y</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>31</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>AND</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>25</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>AND</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>35</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ASL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>0E</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ASL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>1E</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ASL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ACC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>0A</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ASL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ASL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>16</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>BCC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>REL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>90</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>BCS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>REL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>B0</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>BEQ</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>REL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>F0</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>BIT</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2C</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZV</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>BIT</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>24</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZV</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>BMI</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>REL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>30</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>BNE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>REL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>D0</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>BPL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>REL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>10</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>BRK</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>0</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>B</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>BVC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>REL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>50</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>BVS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>REL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>70</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>CLC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>18</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>C</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>CLD</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>D8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>D</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>CLI</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>58</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>I</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>CLV</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>B8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>V</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>CMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>CD</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>CMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>DD</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>CMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,Y</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>D9</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>CMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMM</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>C9</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>CMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>(IND,X)</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>C1</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>CMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>(IND),Y</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>D1</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>CMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>C5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>CMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>D5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>CPX</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>EC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>CPX</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMM</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>E0</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>CPX</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>E4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>CPY</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>CC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>CPY</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMM</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>C0</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>CPY</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>C4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>DEC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>CE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>DEC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>DE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>DEC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>C6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>DEC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>D6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>DEX</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>CA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>DEY</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>88</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>EOR</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4D</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>EOR</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5D</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>EOR</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,Y</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>59</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>EOR</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMM</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>49</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>EOR</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>(IND,X)</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>41</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>EOR</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>(IND),Y</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>51</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>EOR</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>45</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>EOR</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>55</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>INC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>EE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>INC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>FE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>INC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>E6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>INC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>F6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>INX</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>E8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>INY</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>C8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>JMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4C</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>JMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>(IND)</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6C</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>JSR</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>20</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LDA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>AD</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LDA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>BD</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LDA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,Y</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>B9</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LDA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMM</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>A9</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LDA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>A5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LDA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>(IND,X)</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>A1</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LDA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>(IND),Y</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>B1</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LDA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>B5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LDX</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>AE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LDX</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,Y</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>BE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LDX</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMM</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>A2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LDX</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>A6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LDX</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE,Y</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>B6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LDY</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>AC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LDY</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>BC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LDY</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMM</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>A0</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LDY</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>A4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LDY</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>B4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LSR</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4E</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LSR</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5E</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LSR</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ACC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4A</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LSR</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>46</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>LSR</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>56</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>NOP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>EA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ORA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>0D</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ORA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>1D</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ORA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,Y</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>19</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ORA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMM</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>9</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ORA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>(IND,X)</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>1</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ORA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>(IND),Y</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>11</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ORA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ORA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>15</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>PHA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>48</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>PHP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>PLA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>68</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>PLP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>28</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>all</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>RESET</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>INTERNAL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>0</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>I</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ROL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2E</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ROL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3E</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ROL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ACC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2A</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ROL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>26</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ROL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>36</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ROR</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6E</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ROR</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7E</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ROR</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ACC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6A</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ROR</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>66</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ROR</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>76</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>RTI</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>40</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>all</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>RTS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>60</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>SBC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>ED</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NVZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>SBC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>FD</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NVZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>SBC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,Y</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>F9</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NVZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>SBC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMM</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>E9</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>SBC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>(IND,X)</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>E1</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NVZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>SBC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>(IND),Y</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>F1</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NVZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>SBC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>E5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NVZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>SBC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>F5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NVZC</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>SEC</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>38</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>C</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>SED</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>F8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>D</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>SEI</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>78</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>I</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>STA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8D</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>STA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,Y</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>99</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>STA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>(IND,X)</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>81</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>STA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>(IND),Y</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>91</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>6</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>7</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>STA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>85</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>STA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>95</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>STA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>9D</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>S_IRQ</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>INTERNAL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>43</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>0</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>I</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>S_NMI</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>INTERNAL</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>33</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>0</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>I</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>STX</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8E</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>STX</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>86</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>STX</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE,Y</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>96</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>STY</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>ABS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8C</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>5</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>STY</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>84</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>STY</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>Z-PAGE,X</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>94</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>4</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>TAX</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>AA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>TAY</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>A8</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>TSX</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>BA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>TXA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>8A</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>TXS</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>9A</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times">
              <P></P><!--mstheme--></FONT></TD></TR>
          <TR>
            <TD width=67 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>TYA</FONT><!--mstheme--></FONT></P></TD>
            <TD width=71 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=left>IMP</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>98</FONT><!--mstheme--></FONT></P></TD>
            <TD width=82 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>2</FONT><!--mstheme--></FONT></P></TD>
            <TD width=91 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P align=center>3</FONT><!--mstheme--></FONT></P></TD>
            <TD width=59 height=16><!--mstheme--><FONT 
              face="Book Antiqua, Times New Roman, Times"><FONT face=Arial 
              color=#000000 size=2>
              <P 
        align=center>NZ</FONT><!--mstheme--></FONT></P></TD></TR></TBODY></TABLE><!--mstheme--><FONT 
        face="Book Antiqua, Times New Roman, Times"></BLOCKQUOTE>
      <P>&nbsp;</P><!--mstheme--></FONT><!--msnavigation--></TD></TR><!--msnavigation--></TBODY></TABLE><!--msnavigation-->
<TABLE cellSpacing=0 cellPadding=0 width="100%" border=0>
  <TBODY>
  <TR>
    <TD><!--mstheme--><FONT face="Book Antiqua, Times New Roman, Times"><!--msthemeseparator-->
      <P align=center><IMG height=10 src="free_6502_opcode_files/exphorsa.gif" 
      width=600></P>
      <H6><!--mstheme--><FONT color=#666600>© 1999-2000, <A 
      href="http://www.free-ip.com/">The Free-IP Project</A>.&nbsp; This page 
      was last updated on February 15, 2000 11:39 PM.<!--mstheme--></FONT></H6><!--mstheme--></FONT></TD></TR><!--msnavigation--></TBODY></TABLE></BODY></HTML>

******END OF EMBEDDED TABLE ****/


/***
absolute_index_0(this_instruction)
{
if(debug_op)fprintf(stdout,  "ar<=ar_r+1;\n");
if(debug_op)fprintf(stdout,  "rd<=READ_FROM_MEM;\n");

}


absolute_index(this_instruction)
{
absolute_index_0();
absolute_index_1();
absolute_index_2();
}
***/


void dump_defines(int target_mode)
{
	int i;
	char bin_string[8+1];

	bin_string[8]=0;
	for (i = 0; i < current_instruction; i++)
	{

	memset(bin_string, '0', sizeof bin_string-1);
	fprintf(ns_file, "#define %s_",  instruction_array[i].mnemonic);

	switch(instruction_array[i].mode) {
	case ABSOLUTE   :fprintf(ns_file, "ABSOLUTE     "); break;
	case ABSOLUTE_X :fprintf(ns_file, "ABSOLUTE_X   "); break;
	case ABSOLUTE_Y :fprintf(ns_file, "ABSOLUTE_Y   "); break;
	case IMMEDIATE  :fprintf(ns_file, "IMMEDIATE    "); break;
	case INDIRECT_X :fprintf(ns_file, "INDIRECT_X   "); break;
	case INDIRECT_Y :fprintf(ns_file, "INDIRECT_Y   "); break;
	case ZERO_PAGE  :fprintf(ns_file, "ZERO_PAGE    "); break;
	case ZERO_PAGE_X:fprintf(ns_file, "ZERO_PAGE_X  "); break;
	case ZERO_PAGE_Y:fprintf(ns_file, "ZERO_PAGE_Y  "); break;
	case RELATIVE :  fprintf(ns_file, "RELATIVE     "); break;
	case IMPLIED :   fprintf(ns_file, "IMPLIED      "); break;
	case ACCUMULATOR:fprintf(ns_file, "ACCUMULATOR  "); break;
	case INDIRECT :  fprintf(ns_file, "INDIRECT     "); break;
	case INTERNAL :  fprintf(ns_file, "INTERNAL     "); break;
	default: fprintf(ns_file,         "UNKNOWN MODE "); break;
	}

	fprintf(ns_file, "  0x%02x /* ", instruction_array[i].opcode);
	 if(instruction_array[i].flags &  CARRY_FLAG) fprintf(ns_file, "CARRY,");
	 if(instruction_array[i].flags &  OVERFLOW_FLAG) fprintf(ns_file, "OVERFLOW,");
	 if(instruction_array[i].flags &  NEGATIVE_FLAG) fprintf(ns_file, "NEGATIVE,");
	 if(instruction_array[i].flags &  ZERO_FLAG) fprintf(ns_file, "ZERO,");
	 if(instruction_array[i].flags &  BRK_FLAG) fprintf(ns_file, "BRK,");
	 if(instruction_array[i].flags &  IRQ_FLAG) fprintf(ns_file, "IRQ,");
	 if(instruction_array[i].flags &  DECIMAL_FLAG) fprintf(ns_file, "DECIMAL,");
	 fprintf(ns_file,  " */\n");
	}
}

void dump_strat(int target_mode)
{
	int i;
	char bin_string[8+1];
	int op;

	bin_string[8]=0;
	for (i = 0; i < current_instruction; i++)
	{

	op= instruction_array[i].opcode;

	memset(bin_string, '0', sizeof bin_string-1);
	fprintf(ns_file, "\nvoid perform_%s_",  instruction_array[i].mnemonic);

	switch(instruction_array[i].mode) {
	case ABSOLUTE   :fprintf(ns_file, "ABSOLUTE     "); break;
	case ABSOLUTE_X :fprintf(ns_file, "ABSOLUTE_X   "); break;
	case ABSOLUTE_Y :fprintf(ns_file, "ABSOLUTE_Y   "); break;
	case IMMEDIATE  :fprintf(ns_file, "IMMEDIATE    "); break;
	case INDIRECT_X :fprintf(ns_file, "INDIRECT_X   "); break;
	case INDIRECT_Y :fprintf(ns_file, "INDIRECT_Y   "); break;
	case ZERO_PAGE  :fprintf(ns_file, "ZERO_PAGE    "); break;
	case ZERO_PAGE_X:fprintf(ns_file, "ZERO_PAGE_X  "); break;
	case ZERO_PAGE_Y:fprintf(ns_file, "ZERO_PAGE_Y  "); break;
	case RELATIVE :  fprintf(ns_file, "RELATIVE     "); break;
	case IMPLIED :   fprintf(ns_file, "IMPLIED      "); break;
	case ACCUMULATOR:fprintf(ns_file, "ACCUMULATOR  "); break;
	case INDIRECT :  fprintf(ns_file, "INDIRECT     "); break;
	case INTERNAL :  fprintf(ns_file, "INTERNAL     "); break;
	default: fprintf(ns_file,         "UNKNOWN MODE "); break;
	}
	fprintf(ns_file,  "(INS *instruction) {\n");
	


	fprintf(ns_file, "instruction->cycle=0;\n");
	fprintf(ns_file, "strcpy(da_full_name, \"%s\");\n", full_names[instruction_array[i].opcode]); 
	switch(instruction_array[i].mode) {

	case ABSOLUTE   :fprintf(ns_file,  "\n\taddressing_ABSOLUTE     "); break;
	case ABSOLUTE_X :fprintf(ns_file,  "\n\taddressing_ABSOLUTE_X   "); break;
	case ABSOLUTE_Y :fprintf(ns_file,  "\n\taddressing_ABSOLUTE_Y   "); break;
	case IMMEDIATE  :fprintf(ns_file,  "\n\taddressing_IMMEDIATE    "); break;
	case INDIRECT_X :fprintf(ns_file,  "\n\taddressing_INDIRECT_X   "); break;
	case INDIRECT_Y :fprintf(ns_file,  "\n\taddressing_INDIRECT_Y   "); break;
	case ZERO_PAGE  :fprintf(ns_file,  "\n\taddressing_ZERO_PAGE    "); break;
	case ZERO_PAGE_X:fprintf(ns_file,  "\n\taddressing_ZERO_PAGE_X  "); break;
	case ZERO_PAGE_Y:fprintf(ns_file,  "\n\taddressing_ZERO_PAGE_Y  "); break;
	case RELATIVE :  fprintf(ns_file,  "\n\taddressing_RELATIVE     "); break;
	case IMPLIED :   fprintf(ns_file,  "\n\taddressing_IMPLIED      "); break;
	case ACCUMULATOR:fprintf(ns_file,  "\n\taddressing_ACCUMULATOR  "); break;
	case INDIRECT :  fprintf(ns_file,  "\n\taddressing_INDIRECT     "); break;
	case INTERNAL :  fprintf(ns_file,  "\n\taddressing_INTERNAL     "); break;
	default: fprintf(ns_file, "\n\taddressing_UNKNOWN MODE "); break;
	}
	fprintf(ns_file,  "(instruction);\n");

	fprintf(ns_file, "fprintf(stdout, \"when %%s_STATE_%%d=> --- OPERATION\\n\", da_full_name,  instruction->cycle);\n;");
	if (strings[op]) {
	fprintf(ns_file, "fprintf(stdout,\"\\n-- start from strings--\\n\");\n");
	fprintf(ns_file, "fprintf(stdout,");
	putc( '"', ns_file);
	fprintf( ns_file, strings[op]);
	putc( '"', ns_file);
	fprintf(ns_file, ");\n");
	fprintf(ns_file, "fprintf(stdout,\"\\n-- end  start from strings--\\n\");\n");
	}
	else
	fprintf(ns_file,  "\n\tnot_implemented(instruction); /*PERFORM THE OPERATION HERE */\n");
	take_care_of_flag(&instruction_array[i]);

	 fprintf(ns_file,  "\tto_next_instruction(instruction);\n");
	 
	 fprintf(ns_file,  "\n}\n\n\n\n\n");
	}
}

void fill_with_full_names()
{
	int i;

	for (i = 0; i<TARGET_SIZE; i++) 
		if ((full_names[i] = malloc(128)) ==0) {
		fprintf(stderr, "malloc() failed...\n");
		exit(0);
		}



strcpy(full_names[0x6d],"ADC_ABSOLUTE");
strcpy(full_names[0x7d],"ADC_ABSOLUTE_X");
strcpy(full_names[0x79],"ADC_ABSOLUTE_Y");
strcpy(full_names[0x69],"ADC_IMMEDIATE");
strcpy(full_names[0x61],"ADC_INDIRECT_X");
strcpy(full_names[0x71],"ADC_INDIRECT_Y");
strcpy(full_names[0x65],"ADC_ZERO_PAGE");
strcpy(full_names[0x75],"ADC_ZERO_PAGE_X");
strcpy(full_names[0x2d],"AND_ABSOLUTE");
strcpy(full_names[0x3d],"AND_ABSOLUTE_X");
strcpy(full_names[0x39],"AND_ABSOLUTE_Y");
strcpy(full_names[0x29],"AND_IMMEDIATE");
strcpy(full_names[0x21],"AND_INDIRECT_X");
strcpy(full_names[0x31],"AND_INDIRECT_Y");
strcpy(full_names[0x25],"AND_ZERO_PAGE");
strcpy(full_names[0x35],"AND_ZERO_PAGE_X");
strcpy(full_names[0x0e],"ASL_ABSOLUTE");
strcpy(full_names[0x1e],"ASL_ABSOLUTE_X");
strcpy(full_names[0x0a],"ASL_ACCUMULATOR");
strcpy(full_names[0x06],"ASL_ZERO_PAGE");
strcpy(full_names[0x16],"ASL_ZERO_PAGE_X");
strcpy(full_names[0x90],"BCC_RELATIVE");
strcpy(full_names[0xb0],"BCS_RELATIVE");
strcpy(full_names[0xf0],"BEQ_RELATIVE");
strcpy(full_names[0x2c],"BIT_ABSOLUTE");
strcpy(full_names[0x24],"BIT_ZERO_PAGE");
strcpy(full_names[0x30],"BMI_RELATIVE");
strcpy(full_names[0xd0],"BNE_RELATIVE");
strcpy(full_names[0x10],"BPL_RELATIVE");
strcpy(full_names[0x00],"BRK_IMPLIED");
strcpy(full_names[0x50],"BVC_RELATIVE");
strcpy(full_names[0x70],"BVS_RELATIVE");
strcpy(full_names[0x18],"CLC_IMPLIED");
strcpy(full_names[0xd8],"CLD_IMPLIED");
strcpy(full_names[0x58],"CLI_IMPLIED");
strcpy(full_names[0xb8],"CLV_IMPLIED");
strcpy(full_names[0xcd],"CMP_ABSOLUTE");
strcpy(full_names[0xdd],"CMP_ABSOLUTE_X");
strcpy(full_names[0xd9],"CMP_ABSOLUTE_Y");
strcpy(full_names[0xc9],"CMP_IMMEDIATE");
strcpy(full_names[0xc1],"CMP_INDIRECT_X");
strcpy(full_names[0xd1],"CMP_INDIRECT_Y");
strcpy(full_names[0xc5],"CMP_ZERO_PAGE");
strcpy(full_names[0xd5],"CMP_ZERO_PAGE_X");
strcpy(full_names[0xec],"CPX_ABSOLUTE");
strcpy(full_names[0xe0],"CPX_IMMEDIATE");
strcpy(full_names[0xe4],"CPX_ZERO_PAGE");
strcpy(full_names[0xcc],"CPY_ABSOLUTE");
strcpy(full_names[0xc0],"CPY_IMMEDIATE");
strcpy(full_names[0xc4],"CPY_ZERO_PAGE");
strcpy(full_names[0xce],"DEC_ABSOLUTE");
strcpy(full_names[0xde],"DEC_ABSOLUTE_X");
strcpy(full_names[0xc6],"DEC_ZERO_PAGE");
strcpy(full_names[0xd6],"DEC_ZERO_PAGE_X");
strcpy(full_names[0xca],"DEX_IMPLIED");
strcpy(full_names[0x88],"DEY_IMPLIED");
strcpy(full_names[0x4d],"EOR_ABSOLUTE");
strcpy(full_names[0x5d],"EOR_ABSOLUTE_X");
strcpy(full_names[0x59],"EOR_ABSOLUTE_Y");
strcpy(full_names[0x49],"EOR_IMMEDIATE");
strcpy(full_names[0x41],"EOR_INDIRECT_X");
strcpy(full_names[0x51],"EOR_INDIRECT_Y");
strcpy(full_names[0x45],"EOR_ZERO_PAGE");
strcpy(full_names[0x55],"EOR_ZERO_PAGE_X");
strcpy(full_names[0xee],"INC_ABSOLUTE");
strcpy(full_names[0xfe],"INC_ABSOLUTE_X");
strcpy(full_names[0xe6],"INC_ZERO_PAGE");
strcpy(full_names[0xf6],"INC_ZERO_PAGE_X");
strcpy(full_names[0xe8],"INX_IMPLIED");
strcpy(full_names[0xc8],"INY_IMPLIED");
strcpy(full_names[0x4c],"JMP_ABSOLUTE");
strcpy(full_names[0x6c],"JMP_INDIRECT");
strcpy(full_names[0x20],"JSR_ABSOLUTE");
strcpy(full_names[0xad],"LDA_ABSOLUTE");
strcpy(full_names[0xbd],"LDA_ABSOLUTE_X");
strcpy(full_names[0xb9],"LDA_ABSOLUTE_Y");
strcpy(full_names[0xa9],"LDA_IMMEDIATE");
strcpy(full_names[0xa5],"LDA_ZERO_PAGE");
strcpy(full_names[0xa1],"LDA_INDIRECT_X");
strcpy(full_names[0xb1],"LDA_INDIRECT_Y");
strcpy(full_names[0xb5],"LDA_ZERO_PAGE_X");
strcpy(full_names[0xae],"LDX_ABSOLUTE");
strcpy(full_names[0xbe],"LDX_ABSOLUTE_Y");
strcpy(full_names[0xa2],"LDX_IMMEDIATE");
strcpy(full_names[0xa6],"LDX_ZERO_PAGE");
strcpy(full_names[0xb6],"LDX_ZERO_PAGE_Y");
strcpy(full_names[0xac],"LDY_ABSOLUTE");
strcpy(full_names[0xbc],"LDY_ABSOLUTE_X");
strcpy(full_names[0xa0],"LDY_IMMEDIATE");
strcpy(full_names[0xa4],"LDY_ZERO_PAGE");
strcpy(full_names[0xb4],"LDY_ZERO_PAGE_X");
strcpy(full_names[0x4e],"LSR_ABSOLUTE");
strcpy(full_names[0x5e],"LSR_ABSOLUTE_X");
strcpy(full_names[0x4a],"LSR_ACCUMULATOR");
strcpy(full_names[0x46],"LSR_ZERO_PAGE");
strcpy(full_names[0x56],"LSR_ZERO_PAGE_X");
strcpy(full_names[0xea],"NOP_IMPLIED");
strcpy(full_names[0x0d],"ORA_ABSOLUTE");
strcpy(full_names[0x1d],"ORA_ABSOLUTE_X");
strcpy(full_names[0x19],"ORA_ABSOLUTE_Y");
strcpy(full_names[0x09],"ORA_IMMEDIATE");
strcpy(full_names[0x01],"ORA_INDIRECT_X");
strcpy(full_names[0x11],"ORA_INDIRECT_Y");
strcpy(full_names[0x05],"ORA_ZERO_PAGE");
strcpy(full_names[0x15],"ORA_ZERO_PAGE_X");
strcpy(full_names[0x48],"PHA_IMPLIED");
strcpy(full_names[0x08],"PHP_IMPLIED");
strcpy(full_names[0x68],"PLA_IMPLIED");
strcpy(full_names[0x28],"PLP_IMPLIED");
strcpy(full_names[0x03],"RESET_INTERNAL");
strcpy(full_names[0x2e],"ROL_ABSOLUTE");
strcpy(full_names[0x3e],"ROL_ABSOLUTE_X");
strcpy(full_names[0x2a],"ROL_ACCUMULATOR");
strcpy(full_names[0x26],"ROL_ZERO_PAGE");
strcpy(full_names[0x36],"ROL_ZERO_PAGE_X");
strcpy(full_names[0x6e],"ROR_ABSOLUTE");
strcpy(full_names[0x7e],"ROR_ABSOLUTE_X");
strcpy(full_names[0x6a],"ROR_ACCUMULATOR");
strcpy(full_names[0x66],"ROR_ZERO_PAGE");
strcpy(full_names[0x76],"ROR_ZERO_PAGE_X");
strcpy(full_names[0x40],"RTI_IMPLIED");
strcpy(full_names[0x60],"RTS_IMPLIED");
strcpy(full_names[0xed],"SBC_ABSOLUTE");
strcpy(full_names[0xfd],"SBC_ABSOLUTE_X");
strcpy(full_names[0xf9],"SBC_ABSOLUTE_Y");
strcpy(full_names[0xe9],"SBC_IMMEDIATE");
strcpy(full_names[0xe1],"SBC_INDIRECT_X");
strcpy(full_names[0xf1],"SBC_INDIRECT_Y");
strcpy(full_names[0xe5],"SBC_ZERO_PAGE");
strcpy(full_names[0xf5],"SBC_ZERO_PAGE_X");
strcpy(full_names[0x38],"SEC_IMPLIED");
strcpy(full_names[0xf8],"SED_IMPLIED");
strcpy(full_names[0x78],"SEI_IMPLIED");
strcpy(full_names[0x8d],"STA_ABSOLUTE");
strcpy(full_names[0x99],"STA_ABSOLUTE_Y");
strcpy(full_names[0x81],"STA_INDIRECT_X");
strcpy(full_names[0x91],"STA_INDIRECT_Y");
strcpy(full_names[0x85],"STA_ZERO_PAGE");
strcpy(full_names[0x95],"STA_ZERO_PAGE_X");
strcpy(full_names[0x9d],"STA_ABSOLUTE_X");
strcpy(full_names[0x43],"S_IRQ_INTERNAL");
strcpy(full_names[0x33],"S_NMI_INTERNAL");
strcpy(full_names[0x8e],"STX_ABSOLUTE");
strcpy(full_names[0x86],"STX_ZERO_PAGE");
strcpy(full_names[0x96],"STX_ZERO_PAGE_Y");
strcpy(full_names[0x8c],"STY_ABSOLUTE");
strcpy(full_names[0x84],"STY_ZERO_PAGE");
strcpy(full_names[0x94],"STY_ZERO_PAGE_X");
strcpy(full_names[0xaa],"TAX_IMPLIED");
strcpy(full_names[0xa8],"TAY_IMPLIED");
strcpy(full_names[0xba],"TSX_IMPLIED");
strcpy(full_names[0x8a],"TXA_IMPLIED");
strcpy(full_names[0x9a],"TXS_IMPLIED");
}


void init_targets_with_values()
{
targets[ADC_ABSOLUTE]=   TARGET_IS_ACCUMULATOR;
targets[ADC_ABSOLUTE_X]= TARGET_IS_ACCUMULATOR;
targets[ADC_ABSOLUTE_Y]= TARGET_IS_ACCUMULATOR;
targets[ADC_IMMEDIATE]=  TARGET_IS_ACCUMULATOR;
targets[ADC_INDIRECT_X]= TARGET_IS_ACCUMULATOR;
targets[ADC_INDIRECT_Y]= TARGET_IS_ACCUMULATOR;
targets[ADC_ZERO_PAGE]=  TARGET_IS_ACCUMULATOR;
targets[ADC_ZERO_PAGE_X]=  TARGET_IS_ACCUMULATOR;

targets[AND_ABSOLUTE]   =   TARGET_IS_ACCUMULATOR;
targets[AND_ABSOLUTE_X]   = TARGET_IS_ACCUMULATOR;
targets[AND_ABSOLUTE_Y]   = TARGET_IS_ACCUMULATOR;
targets[AND_IMMEDIATE]   =  TARGET_IS_ACCUMULATOR;
targets[AND_INDIRECT_X]   =  TARGET_IS_ACCUMULATOR;
targets[AND_INDIRECT_Y]   =  TARGET_IS_ACCUMULATOR;
targets[AND_ZERO_PAGE]   =  TARGET_IS_ACCUMULATOR;
targets[AND_ZERO_PAGE_X]   =  TARGET_IS_ACCUMULATOR;

targets[ASL_ABSOLUTE  ]=  TARGET_IS_MEMORY;
targets[ASL_ABSOLUTE_X]=  TARGET_IS_MEMORY;
targets[ASL_ACCUMULATOR]=  TARGET_IS_ACCUMULATOR;
targets[ASL_ZERO_PAGE]=  TARGET_IS_MEMORY;
targets[ASL_ZERO_PAGE_X]=  TARGET_IS_MEMORY;

 targets[LDA_ABSOLUTE  ]=TARGET_IS_ACCUMULATOR;
 targets[LDA_ABSOLUTE_X  ]=TARGET_IS_ACCUMULATOR;
 targets[LDA_ABSOLUTE_Y   ]=TARGET_IS_ACCUMULATOR;
 targets[LDA_IMMEDIATE    ]=TARGET_IS_ACCUMULATOR;
 targets[LDA_ZERO_PAGE    ]=TARGET_IS_ACCUMULATOR;
 targets[LDA_INDIRECT_X   ]=TARGET_IS_ACCUMULATOR;
 targets[LDA_INDIRECT_Y    ]=TARGET_IS_ACCUMULATOR;
 targets[LDA_ZERO_PAGE_X   ]=TARGET_IS_ACCUMULATOR;


}

void dump_strings(int target_mode)
{
	FILE *string_file= 0;
	int i;
	char bin_string[8+1];
	string_file =  fopen("strings.temp", "w");


	if(string_file==0)
	{
	fprintf(stderr, "failed to open strings.tmp for writing..\n");
	exit(0);
	}


	bin_string[8]=0;
	for (i = 0; i < current_instruction; i++)
	{
	/***
	if ((target_mode== ABSOLUTE ||
	target_mode==ABSOLUTE_X ||
	target_mode==ABSOLUTE_Y ||
	target_mode==IMMEDIATE ||
	target_mode==INDIRECT_X ||
	target_mode==INDIRECT_Y ||
	target_mode==ZERO_PAGE ||
	target_mode==ZERO_PAGE_X ||
	target_mode==ZERO_PAGE_Y ||
	target_mode==RELATIVE ||
	target_mode==IMPLIED ||
	target_mode==ACCUMULATOR ||
	target_mode==INDIRECT ||
	target_mode==INTERNAL)
	&& target_mode!=instruction_array[i].mode)
		continue;
		***/

	memset(bin_string, '0', sizeof bin_string-1);
	fprintf(string_file, "strings[ %s_",  instruction_array[i].mnemonic);

	switch(instruction_array[i].mode) {
	case ABSOLUTE   :fprintf(string_file, "ABSOLUTE     "); break;
	case ABSOLUTE_X :fprintf(string_file, "ABSOLUTE_X   "); break;
	case ABSOLUTE_Y :fprintf(string_file, "ABSOLUTE_Y   "); break;
	case IMMEDIATE  :fprintf(string_file, "IMMEDIATE    "); break;
	case INDIRECT_X :fprintf(string_file, "INDIRECT_X   "); break;
	case INDIRECT_Y :fprintf(string_file, "INDIRECT_Y   "); break;
	case ZERO_PAGE  :fprintf(string_file, "ZERO_PAGE    "); break;
	case ZERO_PAGE_X:fprintf(string_file, "ZERO_PAGE_X  "); break;
	case ZERO_PAGE_Y:fprintf(string_file, "ZERO_PAGE_Y  "); break;
	case RELATIVE :  fprintf(string_file, "RELATIVE     "); break;
	case IMPLIED :   fprintf(string_file, "IMPLIED      "); break;
	case ACCUMULATOR:fprintf(string_file, "ACCUMULATOR  "); break;
	case INDIRECT :  fprintf(string_file, "INDIRECT     "); break;
	case INTERNAL :  fprintf(string_file, "INTERNAL     "); break;
	default: fprintf(string_file,         "UNKNOWN MODE "); break;
	}

	/**fprintf(string_file, "  0x%02x /* ", instruction_array[i].opcode);***/
	 fprintf(string_file,  "]=0; \n");
	}
}

void take_care_of_flag(struct INSTRUCTION_S *ip)
{
	if(ns_file==0){
	fprintf(stderr, "File ns.c not opened for writing...\n");
	exit(0);
	}
	if(ip->flags &  CARRY_FLAG) fprintf(ns_file, "%s_setup_carry(instruction);\n", ip->mnemonic);
	if(ip->flags &  OVERFLOW_FLAG) fprintf(ns_file, "%s_setup_overflow(instruction);\n", ip->mnemonic);
	if(ip->flags &  NEGATIVE_FLAG) fprintf(ns_file, "%s_setup_negative(instruction);\n", ip->mnemonic);
	if(ip->flags &  ZERO_FLAG) fprintf(ns_file, "%s_setup_zero(instruction);\n", ip->mnemonic);
	if(ip->flags &  BRK_FLAG) fprintf(ns_file, "%s_setup_brk(instruction);\n", ip->mnemonic);
	if(ip->flags &  IRQ_FLAG) fprintf(ns_file, "%s_setup_irq(instruction);\n", ip->mnemonic);
	if(ip->flags &  DECIMAL_FLAG) fprintf(ns_file, "%s_setup_decimal(instruction);\n", ip->mnemonic);
}


void dump_states()
{

	FILE *fp=fopen("states", "w");
	int i,  j;
	char bin_string[8+1];
	if (fp==0) {
	fprintf(stderr, "Unable to open states for writing...\n");
	exit(0);
	}

	bin_string[8]=0;
	for (i = 0; i < current_instruction; i++)
	{

	memset(bin_string, '0', sizeof bin_string-1);
	for (j = 0; j < 10; j++) {
	if(debug_op)fprintf(stdout, "%s_",    instruction_array[i].mnemonic);

	
	switch(instruction_array[i].mode) {
	case ABSOLUTE   :if(debug_op)fprintf(stdout, "ABSOLUTE"); break;
	case ABSOLUTE_X :if(debug_op)fprintf(stdout, "ABSOLUTE_X"); break;
	case ABSOLUTE_Y :if(debug_op)fprintf(stdout, "ABSOLUTE_Y"); break;
	case IMMEDIATE  :if(debug_op)fprintf(stdout, "IMMEDIATE"); break;
	case INDIRECT_X :if(debug_op)fprintf(stdout, "INDIRECT_X"); break;
	case INDIRECT_Y :if(debug_op)fprintf(stdout, "INDIRECT_Y"); break;
	case ZERO_PAGE  :if(debug_op)fprintf(stdout, "ZERO_PAGE"); break;
	case ZERO_PAGE_X:if(debug_op)fprintf(stdout, "ZERO_PAGE_X"); break;
	case ZERO_PAGE_Y:if(debug_op)fprintf(stdout, "ZERO_PAGE_Y"); break;
	case RELATIVE :  if(debug_op)fprintf(stdout, "RELATIVE"); break;
	case IMPLIED :   if(debug_op)fprintf(stdout, "IMPLIED"); break;
	case ACCUMULATOR:if(debug_op)fprintf(stdout, "ACCUMULATOR"); break;
	case INDIRECT :  if(debug_op)fprintf(stdout, "INDIRECT"); break;
	case INTERNAL :  if(debug_op)fprintf(stdout, "INTERNAL"); break;
	default: if(debug_op)fprintf(stdout,         "UNKNOWN MODE"); break;
	}
	if(debug_op)fprintf(stdout, "_STATE_%d,\n", j);
	}
	if(debug_op)fprintf(stdout, "\n\n");
	} 
}
