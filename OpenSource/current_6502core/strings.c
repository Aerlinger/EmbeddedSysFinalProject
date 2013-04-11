/* NOT GENERATED                            */
/* contains VHDL statements                 */

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

#define MAX_STRING (256)
char *strings[MAX_STRING];

void  init_vhdl_code(){
strings[ ADC_ABSOLUTE     ]="    rd<=LO;\\n   ac<=ac_r+data;\\n";
strings[ ADC_ABSOLUTE_X   ]="    rd<=LO;\\n   ac<=ac_r+data;\\n";
strings[ ADC_ABSOLUTE_Y   ]="    rd<=LO;\\n   ac<=ac_r+data;\\n";
strings[ ADC_IMMEDIATE    ]="    rd<=LO;\\n   ac<=ac_r+data;\\n"; 
strings[ ADC_INDIRECT_X   ]="    rd<=LO;\\n   ac<=ac_r+data;\\n"; 
strings[ ADC_INDIRECT_Y   ]="    rd<=LO;\\n   ac<=ac_r+data;\\n"; 
strings[ ADC_ZERO_PAGE    ]="    rd<=LO;\\n   ac<=ac_r+data;\\n";
strings[ ADC_ZERO_PAGE_X  ]="    rd<=LO;\\n   ac<=ac_r+data;\\n";


strings[ AND_ABSOLUTE     ]=0; 
strings[ AND_ABSOLUTE_X   ]=0; 
strings[ AND_ABSOLUTE_Y   ]=0; 
strings[ AND_IMMEDIATE    ]=0; 
strings[ AND_INDIRECT_X   ]=0; 
strings[ AND_INDIRECT_Y   ]=0; 
strings[ AND_ZERO_PAGE    ]=0; 
strings[ AND_ZERO_PAGE_X  ]=0; 
strings[ ASL_ABSOLUTE     ]=0; 
strings[ ASL_ABSOLUTE_X   ]=0; 
strings[ ASL_ACCUMULATOR  ]=0; 
strings[ ASL_ZERO_PAGE    ]=0; 
strings[ ASL_ZERO_PAGE_X  ]=0; 
strings[ BCC_RELATIVE     ]=0; 
strings[ BCS_RELATIVE     ]=0; 
strings[ BEQ_RELATIVE     ]=
"     if(offset_r>0) then \\n"
"     pc<=pc_r+offset_r; \\n"
"     else \\n"
"     pc<=pc_r-offset_r; \\n"
"     end if;\\n";


strings[ BIT_ABSOLUTE     ]=0; 
strings[ BIT_ZERO_PAGE    ]=0; 
strings[ BMI_RELATIVE     ]=0; 
strings[ BNE_RELATIVE     ]=0; 
strings[ BPL_RELATIVE     ]=0; 
strings[ BRK_IMPLIED      ]=0; 
strings[ BVC_RELATIVE     ]=0; 
strings[ BVS_RELATIVE     ]=0; 
strings[ CLC_IMPLIED      ]="--- DONE\\n"; 
strings[ CLD_IMPLIED      ]="--- DONE\\n";
strings[ CLI_IMPLIED      ]=0; 
strings[ CLV_IMPLIED      ]="--- DONE\\n";
strings[ CMP_ABSOLUTE     ]=0; 
strings[ CMP_ABSOLUTE_X   ]=0; 
strings[ CMP_ABSOLUTE_Y   ]=0; 
strings[ CMP_IMMEDIATE    ]=0; 
strings[ CMP_INDIRECT_X   ]=0; 
strings[ CMP_INDIRECT_Y   ]=0; 
strings[ CMP_ZERO_PAGE    ]=0; 
strings[ CMP_ZERO_PAGE_X  ]=0; 
strings[ CPX_ABSOLUTE     ]=0; 
strings[ CPX_IMMEDIATE    ]=0; 
strings[ CPX_ZERO_PAGE    ]=0; 
strings[ CPY_ABSOLUTE     ]=0; 
strings[ CPY_IMMEDIATE    ]=0; 
strings[ CPY_ZERO_PAGE    ]=0; 
strings[ DEC_ABSOLUTE     ]=0; 
strings[ DEC_ABSOLUTE_X   ]=0; 
strings[ DEC_ZERO_PAGE    ]=0; 
strings[ DEC_ZERO_PAGE_X  ]=0; 
strings[ DEX_IMPLIED      ]="   x<=x_r-1;\\n";
strings[ DEY_IMPLIED      ]="   y<=y_r-1;\\n";
strings[ EOR_ABSOLUTE     ]=0; 
strings[ EOR_ABSOLUTE_X   ]=0; 
strings[ EOR_ABSOLUTE_Y   ]=0; 
strings[ EOR_IMMEDIATE    ]=0; 
strings[ EOR_INDIRECT_X   ]=0; 
strings[ EOR_INDIRECT_Y   ]=0; 
strings[ EOR_ZERO_PAGE    ]=0; 
strings[ EOR_ZERO_PAGE_X  ]=0; 
strings[ INC_ABSOLUTE     ]=0; 
strings[ INC_ABSOLUTE_X   ]=0; 
strings[ INC_ZERO_PAGE    ]=0; 
strings[ INC_ZERO_PAGE_X  ]=0; 
strings[ INX_IMPLIED      ]=0; 
strings[ INY_IMPLIED      ]=0; 

strings[ JMP_ABSOLUTE     ]= "    pc<=addr_hi_r & addr_lo_r;\\n" ;

strings[ JMP_INDIRECT     ]=0; 

strings[ JSR_ABSOLUTE     ]=0; 

strings[ LDA_ABSOLUTE     ]="    rd<=LO;\\n   ac<=data;\\n";
strings[ LDA_ABSOLUTE_X   ]="    rd<=LO;\\n   ac<=data;\\n";
strings[ LDA_ABSOLUTE_Y   ]="    rd<=LO;\\n   ac<=data;\\n";
strings[ LDA_IMMEDIATE    ]="    rd<=LO;\\n   ac<=data;\\n";
strings[ LDA_ZERO_PAGE    ]="    rd<=LO;\\n   ac<=data;\\n";
strings[ LDA_INDIRECT_X   ]="    rd<=LO;\\n   ac<=data;\\n";
strings[ LDA_INDIRECT_Y   ]="    rd<=LO;\\n   ac<=data;\\n";
strings[ LDA_ZERO_PAGE_X  ]="    rd<=LO;\\n   ac<=data;\\n";

strings[ LDX_ABSOLUTE     ]="    rd<=LO;\\n   x<=data;\\n";
strings[ LDX_ABSOLUTE_Y   ]="    rd<=LO;\\n   x<=data;\\n";
strings[ LDX_IMMEDIATE    ]="    rd<=LO;\\n   x<=data;\\n";
strings[ LDX_ZERO_PAGE    ]="    rd<=LO;\\n   x<=data;\\n";
strings[ LDX_ZERO_PAGE_Y  ]="    rd<=LO;\\n   x<=data;\\n";

strings[ LDY_ABSOLUTE     ]="  rd<=LO;\\n   y<=data;\\n";
strings[ LDY_ABSOLUTE_X   ]="  rd<=LO;\\n   y<=data;\\n";
strings[ LDY_IMMEDIATE    ]="  rd<=LO;\\n   y<=data;\\n";
strings[ LDY_ZERO_PAGE    ]="  rd<=LO;\\n   y<=data;\\n";
strings[ LDY_ZERO_PAGE_X  ]="  rd<=LO;\\n   y<=data;\\n";


strings[ LSR_ABSOLUTE     ]=0; 
strings[ LSR_ABSOLUTE_X   ]=0; 
strings[ LSR_ACCUMULATOR  ]=0; 
strings[ LSR_ZERO_PAGE    ]=0; 
strings[ LSR_ZERO_PAGE_X  ]=0; 
strings[ NOP_IMPLIED      ]= "    --- do nothing\\n";
strings[ ORA_ABSOLUTE     ]=0; 
strings[ ORA_ABSOLUTE_X   ]=0;
strings[ ORA_ABSOLUTE_Y   ]=0; 
strings[ ORA_IMMEDIATE    ]=0; 
strings[ ORA_INDIRECT_X   ]=0; 
strings[ ORA_INDIRECT_Y   ]=0; 
strings[ ORA_ZERO_PAGE    ]=0; 
strings[ ORA_ZERO_PAGE_X  ]=0; 
strings[ PHA_IMPLIED      ]=0; 
strings[ PHP_IMPLIED      ]=0; 
strings[ PLA_IMPLIED      ]=0; 
strings[ PLP_IMPLIED      ]=0; 
strings[ RESET_INTERNAL   ]=0; 
strings[ ROL_ABSOLUTE     ]=0; 
strings[ ROL_ABSOLUTE_X   ]=0; 
strings[ ROL_ACCUMULATOR  ]=0; 
strings[ ROL_ZERO_PAGE    ]=0; 
strings[ ROL_ZERO_PAGE_X  ]=0; 
strings[ ROR_ABSOLUTE     ]=0; 
strings[ ROR_ABSOLUTE_X   ]=0; 
strings[ ROR_ACCUMULATOR  ]=0; 
strings[ ROR_ZERO_PAGE    ]=0; 
strings[ ROR_ZERO_PAGE_X  ]=0; 
strings[ RTI_IMPLIED      ]=0; 
strings[ RTS_IMPLIED      ]=0; 
strings[ SBC_ABSOLUTE     ]=0; 
strings[ SBC_ABSOLUTE_X   ]=0; 
strings[ SBC_ABSOLUTE_Y   ]=0; 
strings[ SBC_IMMEDIATE    ]=0; 
strings[ SBC_INDIRECT_X   ]=0; 
strings[ SBC_INDIRECT_Y   ]=0; 
strings[ SBC_ZERO_PAGE    ]=0; 
strings[ SBC_ZERO_PAGE_X  ]=0; 
strings[ SEC_IMPLIED      ]=0; 
strings[ SED_IMPLIED      ]=0; 
strings[ SEI_IMPLIED      ]=0; 
strings[ STA_ABSOLUTE     ]=0; 
strings[ STA_ABSOLUTE_Y   ]=0; 
strings[ STA_INDIRECT_X   ]=0; 
strings[ STA_INDIRECT_Y   ]=0; 
strings[ STA_ZERO_PAGE    ]=0; 
strings[ STA_ZERO_PAGE_X  ]=0; 
strings[ STA_ABSOLUTE_X   ]=0; 
strings[ S_IRQ_INTERNAL   ]=0; 
strings[ S_NMI_INTERNAL   ]=0; 
strings[ STX_ABSOLUTE     ]=0; 
strings[ STX_ZERO_PAGE    ]=0; 
strings[ STX_ZERO_PAGE_Y  ]=0; 
strings[ STY_ABSOLUTE     ]=0; 
strings[ STY_ZERO_PAGE    ]=0; 
strings[ STY_ZERO_PAGE_X  ]=0; 
strings[ TAX_IMPLIED      ]=0; 
strings[ TAY_IMPLIED      ]=0; 
strings[ TSX_IMPLIED      ]=0; 
strings[ TXA_IMPLIED      ]=0; 
strings[ TXS_IMPLIED      ]=0; 
}
