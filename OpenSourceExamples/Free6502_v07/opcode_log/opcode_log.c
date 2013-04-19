#include <stdio.h>
#include <stdlib.h>

struct opcode_list
  {
    char *name;
    int  value;
  };
 
static struct opcode_list opcode_list[] =
  {
    {"ADC ABS",0x6D},      {"ADC ABS,X",0x7D},    {"ADC ABS,Y",0x79}, {"ADC IMM",0x69},
    {"ADC (IND,X)",0x61},  {"ADC (IND),Y",0x71},  {"ADC Z-PAGE",0x65}, {"ADC Z-PAGE,X",0x75},
    {"AND ABS",0x2D},      {"AND ABS,X",0x3D},    {"AND ABS,Y",0x39}, {"AND IMM",0x29},
    {"AND (IND,X)",0x21},  {"AND (IND),Y",0x31},  {"AND Z-PAGE",0x25}, {"AND Z-PAGE,X",0x35},
    {"ASL ABS",0x0E},      {"ASL ABS,X",0x1E},    {"ASL ACC",0x0A}, {"ASL Z-PAGE",0x06},
    {"ASL Z-PAGE,X",0x16}, {"BCC REL",0x90},      {"BCS REL",0xB0}, {"BEQ REL",0xF0},
    {"BIT ABS",0x2C},      {"BIT Z-PAGE",0x24},   {"BMI REL",0x30}, {"BNE REL",0xD0},
    {"BPL REL",0x10},      {"BRK IMP",0x00},      {"BVC REL",0x50}, {"BVS REL",0x70},
    {"CLC IMP",0x18},      {"CLD IMP",0xD8},      {"CLI IMP",0x58}, {"CLV IMP",0xB8},
    {"CMP ABS",0xCD},      {"CMP ABS,X",0xDD},    {"CMP ABS,Y",0xD9}, {"CMP IMM",0xC9},
    {"CMP (IND,X)",0xC1},  {"CMP (IND),Y",0xD1},  {"CMP Z-PAGE",0xC5}, {"CMP Z-PAGE,X",0xD5},
    {"CPX ABS",0xEC},      {"CPX IMM",0xE0},      {"CPX Z-PAGE",0xE4}, {"CPY ABS",0xCC},
    {"CPY IMM",0xC0},      {"CPY Z-PAGE",0xC4},   {"DEC ABS",0xCE}, {"DEC ABS,X",0xDE},
    {"DEC Z-PAGE",0xC6},   {"DEC Z-PAGE,X",0xD6}, {"DEX IMP",0xCA}, {"DEY IMP",0x88},
    {"EOR ABS",0x4D},      {"EOR ABS,X",0x5D},    {"EOR ABS,Y",0x59}, {"EOR IMM",0x49},
    {"EOR (IND,X)",0x41},  {"EOR (IND),Y",0x51},  {"EOR Z-PAGE",0x45}, {"EOR Z-PAGE,X",0x55},
    {"INC ABS",0xEE},      {"INC ABS,X",0xFE},    {"INC Z-PAGE",0xE6}, {"INC Z-PAGE,X",0xF6},
    {"INX IMP",0xE8},      {"INY IMP",0xC8},      {"JMP ABS",0x4C}, {"JMP (IND)",0x6C},
    {"JSR ABS",0x20},      {"LDA ABS",0xAD},      {"LDA ABS,X",0xBD}, {"LDA ABS,Y",0xB9},
    {"LDA IMM",0xA9},      {"LDA Z-PAGE",0xA5},   {"LDA (IND,X)",0xA1}, {"LDA (IND),Y",0xB1},
    {"LDA Z-PAGE,X",0xB5}, {"LDX ABS",0xAE},      {"LDX ABS,Y",0xBE}, {"LDX IMM",0xA2},
    {"LDX Z-PAGE",0xA6},   {"LDX Z-PAGE,Y",0xB6}, {"LDY ABS",0xAC}, {"LDY ABS,X",0xBC},
    {"LDY IMM",0xA0},      {"LDY Z-PAGE",0xA4},   {"LDY Z-PAGE,X",0xB4}, {"LSR ABS",0x4E},
    {"LSR ABS,X",0x5E},    {"LSR ACC",0x4A},      {"LSR Z-PAGE",0x46}, {"LSR Z-PAGE,X",0x56},
    {"NOP IMP",0xEA},      {"ORA ABS",0x0D},      {"ORA ABS,X",0x1D}, {"ORA ABS,Y",0x19},
    {"ORA IMM",0x09},      {"ORA (IND,X)",0x01},  {"ORA (IND),Y",0x11}, {"ORA Z-PAGE",0x05},
    {"ORA Z-PAGE,X",0x15}, {"PHA IMP",0x48},      {"PHP IMP",0x08}, {"PLA IMP",0x68},
    {"PLP IMP",0x28},      {"ROL ABS",0x2E},      {"ROL ABS,X",0x3E}, {"ROL ACC",0x2A},
    {"ROL Z-PAGE",0x26},   {"ROL Z-PAGE,X",0x36}, {"ROR ABS",0x6E}, {"ROR ABS,X",0x7E},
    {"ROR ACC",0x6A},      {"ROR Z-PAGE",0x66},   {"ROR Z-PAGE,X",0x76}, {"RTI IMP",0x40},
    {"RTS IMP",0x60},      {"SBC ABS",0xED},      {"SBC ABS,X",0xFD}, {"SBC ABS,Y",0xF9},
    {"SBC IMM",0xE9},      {"SBC (IND,X)",0xE1},  {"SBC (IND),Y",0xF1}, {"SBC Z-PAGE",0xE5},
    {"SBC Z-PAGE,X",0xF5}, {"SEC IMP",0x38},      {"SED IMP",0xF8}, {"SEI IMP",0x78},
    {"STA ABS",0x8D},      {"STA ABS,Y",0x99},    {"STA (IND,X)",0x81}, {"STA (IND),Y",0x91},
    {"STA Z-PAGE",0x85},   {"STA Z-PAGE,X",0x95}, {"STA ABS,X",0x9D}, {"STX ABS",0x8E},
    {"STX Z-PAGE",0x86},   {"STX Z-PAGE,Y",0x96}, {"STY ABS",0x8C}, {"STY Z-PAGE",0x84},
    {"STY Z-PAGE,X",0x94}, {"TAX IMP",0xAA},      {"TAY IMP",0xA8}, {"TSX IMP",0xBA},
    {"TXA IMP",0x8A},      {"TXS IMP",0x9A},      {"TYA IMP",0x98}
  };

#define N_OPCODES  (sizeof(opcode_list)/sizeof(opcode_list[0]))


struct opcode_freq
  {
    struct opcode_list *opcode;
    int value;
    long count;
  };

static struct opcode_freq freq[256];
static long count=0;


int  comp_freq (const void *a, const void *b);


int
main (int argc, char *argv[])
{
  int i, j, k;
  FILE *file;


  if (argc!=2)
    {
      printf ("Usage:  opcode_log <filename>\n");
      return (1);
    }

  // Initalize the frequency table
  for (i=0; i<256; i++)
    {
      freq[i].opcode = NULL;
      freq[i].count = 0;
      freq[i].value = i;
    }

  // Link valid opcodes to the opcode list
  for (i=0; i<N_OPCODES; i++)
    freq[opcode_list[i].value].opcode=opcode_list+i;
    	

  // Read in the file and generate the frequency lists.
  file = fopen (argv[1], "rb");
  if (file==NULL)
    {
      printf ("Error opening %s.\n", argv[1]);
      return (1);
    }

  count = 0;
  
  while (!feof(file))
    {
      fread (&i, sizeof(i), 1, file);

      i = i & 0x000000FF; // Mask out the address portion
      freq[i].count++;
      count++;
    }

  fclose (file);

  if (count==0)
    {
      printf ("Error:  No instructions to count.\n");
      return (1);
    }

  qsort (freq, 256, sizeof(freq[0]), comp_freq);

  // Output the top used instructions
  for (i=0; i<256; i++)
    {
      if (freq[i].count > 0)
        {
          if (freq[i].opcode!=NULL)
            printf ("%-12s %8.4f\n", freq[i].opcode->name, 100.0*((double)freq[i].count)/((double)count));
          else
            printf ("0x%02X         %8.4f\n", freq[i].value, 100.0*((double)freq[i].count)/((double)count));
        }
      else
        {
          if (freq[i].opcode!=NULL)
            printf ("%-12s ---\n", freq[i].opcode->name);
        }
    }

  return (0);
}




//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
int
comp_freq (const void *a, const void *b)
{
  const struct opcode_freq *a1, *b1;
  
  a1 = (const struct opcode_freq *)a;
  b1 = (const struct opcode_freq *)b;

  if      (a1->count > b1->count)  return (-1);
  else if (a1->count < b1->count)  return ( 1);
  else return (0);
}


//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

