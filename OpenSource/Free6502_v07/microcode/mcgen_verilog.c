//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//--  The Free IP Project
//--  The Free-6502 Core
//--  (c) 1999, The Free IP Project and David Kessner
//--
//--
//--  FREE IP GENERAL PUBLIC LICENSE
//--  TERMS AND CONDITIONS FOR USE, COPYING, DISTRIBUTION, AND MODIFICATION
//--
//--  1.  You may copy and distribute verbatim copies of this core, as long
//--      as this file, and the other associated files, remain intact and
//--      unmodified.  Modifications are outlined below.  Also, see the
//--      import/export warning above for further restrictions on
//--      distribution.
//--  2.  You may use this core in any way, be it academic, commercial, or
//--      military.  Modified or not.
//--  3.  Distribution of this core must be free of charge.  Charging is
//--      allowed only for value added services.  Value added services
//--      would include copying fees, modifications, customizations, and
//--      inclusion in other products.
//--  4.  If a modified source code is distributed, the original unmodified
//--      source code must also be included (or a link to the Free IP web
//--      site).  In the modified source code there must be clear
//--      identification of the modified version.
//--  5.  Visit the Free IP web site for additional information.
//--      http://www.free-ip.com
//--
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINELEN		(512)
#define MAXCELLS	(64)
#define MAX_OPS	 	(2048)
#define COL_OFFSET (14)


struct mcop
  {
    char line[LINELEN];
    char *cell[MAXCELLS];
  };

static struct mcop ops[MAX_OPS];
static int n_ops;

struct unique
  {
    int col;
    int num;
    char *list[MAXCELLS];
  };

#define MAX_UNIQUE	(32)
static struct unique unique[MAX_UNIQUE];
static int n_unique;

int load_file (char *filename);
int gen_unique (void);
char *parse (char *s);
char *strip (char *s);
char *itob (int i, int d);
int  xtoi(char *s);
int  n_bits (int i);

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
int
main (int argc, char *argv[])
{
  int i, j, k, last;
  char flags[160];


  if (argc!=2)
    {
      printf ("Usage:\n   mcgen <infile>\n");
      return (1);
    }

  if (load_file (argv[1]))
    return (1);

  if (gen_unique())
    return (1);


  printf ("//----------------------------------------------------------------------------\n");
  printf ("//----------------------------------------------------------------------------\n");
  printf ("//--  The Free IP Project\n");
  printf ("//--  Verilog Free-6502 Core\n");
  printf ("//--  (c) 1999, The Free IP Project and David Kessner\n");
  printf ("//--\n");
  printf ("//--\n");
  printf ("//--  FREE IP GENERAL PUBLIC LICENSE\n");
  printf ("//--  TERMS AND CONDITIONS FOR USE, COPYING, DISTRIBUTION, AND MODIFICATION\n");
  printf ("//--\n");
  printf ("//--  1.  You may copy and distribute verbatim copies of this core, as long\n");
  printf ("//--      as this file, and the other associated files, remain intact and\n");
  printf ("//--      unmodified.  Modifications are outlined below.  Also, see the\n");
  printf ("//--      import/export warning above for further restrictions on\n");
  printf ("//--      distribution.\n");
  printf ("//--  2.  You may use this core in any way, be it academic, commercial, or\n");
  printf ("//--      military.  Modified or not.  \n");
  printf ("//--  3.  Distribution of this core must be free of charge.  Charging is\n");
  printf ("//--      allowed only for value added services.  Value added services\n");
  printf ("//--      would include copying fees, modifications, customizations, and\n");
  printf ("//--      inclusion in other products.\n");
  printf ("//--  4.  If a modified source code is distributed, the original unmodified\n");
  printf ("//--      source code must also be included (or a link to the Free IP web\n");
  printf ("//--      site).  In the modified source code there must be clear\n");
  printf ("//--      identification of the modified version.\n");
  printf ("//--  5.  Visit the Free IP web site for additional information.\n");
  printf ("//--      http://www.free-ip.com\n");
  printf ("//--\n");
  printf ("//----------------------------------------------------------------------------\n");
  printf ("//----------------------------------------------------------------------------\n");
  printf ("//--\n");
  printf ("//----------------------------------------------------------------------------\n");
  printf ("//--  Microcode Verilog file for 6502 CPU.  Created by mcgen_verilog.exe\n");
  printf ("//----------------------------------------------------------------------------\n");
  printf ("\n");


  /////////////////////////////////////////////////////////////
  // Generate the package
#if 0
  printf ("library ieee;\n");
  printf ("use ieee.std_logic_1164.all;\n");
  printf ("use ieee.std_logic_arith.all;\n");
  printf ("use ieee.std_logic_unsigned.all;\n");
  printf ("library work;\n");
  printf ("\n");
  printf ("package microcode is\n");

  k=0;
  for (i=0; i<n_unique; i++)
    {
      printf ("  type MCT_%s is (MC_%s", ops[0].cell[COL_OFFSET+i], unique[i].list[0]);

      for (j=1; j<unique[i].num; j++)
        printf (", MC_%s", unique[i].list[j]);

      printf (");  -- %d types\n", unique[i].num);
      k += n_bits (unique[i].num);
    }
  printf ("\n  -- Microcode is approxamately %d bits wide.\n\n", k);

  printf ("\n");
  printf ("  component mc_rom\n");
  printf ("    port (opcode     :in std_logic_vector (7 downto 0);\n");
  printf ("          step       :in std_logic_vector (2 downto 0);\n");

  for (i=0; i<n_unique-1; i++)
      printf ("          %-10s :out MCT_%s;\n", ops[0].cell[COL_OFFSET+i], ops[0].cell[COL_OFFSET+i]);
  printf ("          %-10s :out MCT_%s\n", ops[0].cell[COL_OFFSET+i], ops[0].cell[COL_OFFSET+i]);

  printf ("         );\n");
  printf ("  end component;\n");
  printf ("\n");

  for (i=0; i<n_unique; i++)
    {
      printf ("  component %s_rom\n", ops[0].cell[COL_OFFSET+i]);
      printf ("    port (addr       :in std_logic_vector (10 downto 0);\n");
      printf ("          %-10s :out MCT_%s\n", ops[0].cell[COL_OFFSET+i], ops[0].cell[COL_OFFSET+i]);
      printf ("         );\n");
      printf ("  end component;\n");
      printf ("\n");
    }

  printf ("end microcode;\n");
  printf ("\n");
  printf ("package body microcode is\n");
  printf ("end microcode;\n");
  printf ("\n");
#endif
  // End generate the package


  /////////////////////////////////////////////////////////////
  // Generate the top level block
  printf ("//----------------------------------------------------------------------------\n");
  printf ("//----------------------------------------------------------------------------\n");
  printf ("// The top level rom\n");
  printf ("module mc_rom (opcode, step");

  for (i=0; i<n_unique; i++)
      printf (", %s", ops[0].cell[COL_OFFSET+i]);
  printf (");\n\n");

  printf ("    input   [ 7:0]  opcode;\n");
  printf ("    input   [ 2:0]  step;\n");

  for (i=0; i<n_unique; i++)
    {
      j = n_bits (unique[i].num);

      if (j>1)
        {
          printf ("    output  [%2d:0]  %s;\n", j-1, ops[0].cell[COL_OFFSET+i]);
          printf ("    wire    [%2d:0]  %s;\n", j-1, ops[0].cell[COL_OFFSET+i]);
        }
      else
        {
          printf ("    output          %s;\n", ops[0].cell[COL_OFFSET+i]);
          printf ("    wire            %s;\n", ops[0].cell[COL_OFFSET+i]);
        }
    }

  printf ("    wire    [10:0]  addr;\n");
  printf ("\n");
  printf ("  assign addr = {opcode, step} ;\n");
  printf ("\n");

  for (i=0; i<n_unique; i++)
    {
      //printf ("  %s_rom U%02d port map (addr, %s);\n",
      //        ops[0].cell[COL_OFFSET+i], i, ops[0].cell[COL_OFFSET+i]);
      printf ("  %s_rom U%02d (addr, %s);\n",
              ops[0].cell[COL_OFFSET+i], i, ops[0].cell[COL_OFFSET+i]);
    }

  printf ("\n");
  printf ("endmodule\n");
  printf ("\n");
  // End Generate the top level block
  /////////////////////////////////////////////////////////////


  // Generate all roms
  for (i=0; i<n_unique; i++)
    {
      printf ("//----------------------------------------------------------------------------\n");
      printf ("//----------------------------------------------------------------------------\n");
      printf ("module %s_rom (addr, %s);\n", ops[0].cell[COL_OFFSET+i], ops[0].cell[COL_OFFSET+i]);
      printf ("\n");
      printf ("input   [10:0]  addr;\n");

      j = n_bits (unique[i].num);
      if (j>1)
        {
          printf ("output  [%2d:0]  %s;\n", j-1, ops[0].cell[COL_OFFSET+i]);
          printf ("reg     [%2d:0]  %s;\n", j-1, ops[0].cell[COL_OFFSET+i]);
        }
      else
        {
          printf ("output          %s;\n", ops[0].cell[COL_OFFSET+i]);
          printf ("reg             %s;\n", ops[0].cell[COL_OFFSET+i]);
        }

      printf ("\n");

      for (j=0; j<unique[i].num; j++)
        printf ("parameter %s_MC_%-20s = 8'h%02X;\n", ops[0].cell[COL_OFFSET+i], unique[i].list[j], j);

      printf ("\n");
      printf ("always @ (addr)\n");
      printf ("  case (addr)\n");

      for (j=2; j<n_ops; j++)
        {
          if (ops[j].cell[0][0]!='\0')
            last = j;

          if (ops[j].cell[i+COL_OFFSET]!=NULL)
            {
              printf ("    11'b%s : ",
                  itob((xtoi(ops[last].cell[2])<<3) | atoi(ops[j].cell[13]), 8+3));

              printf ("%s <= %s_MC_%s;\n", ops[0].cell[i+COL_OFFSET], ops[0].cell[i+COL_OFFSET], ops[j].cell[i+COL_OFFSET]);
            }
        }

      printf ("    default         : %s <= %s_MC_%s;\n", ops[0].cell[i+COL_OFFSET], ops[0].cell[i+COL_OFFSET], ops[1].cell[i+COL_OFFSET]);
      printf ("  endcase\n");
      printf ("\n");
      printf ("endmodule\n");
      printf ("\n");
    }

  printf ("//----------------------------------------------------------------------------\n");
  printf ("//----------------------------------------------------------------------------\n");
  printf ("\n");

//////////////////////////

  printf ("//----------------------------------------------------------------------------\n");
  printf ("//----------------------------------------------------------------------------\n");
  printf ("//--,Free-6502 Opcode Summary\n");
  printf ("//--  \n");
  printf ("//--,Neumonic,Addr Mode,Opcode,Original Clks,Free-6502 Clks,Flags\n");

  for (i=2; i<n_ops; i++)
    {
      if (ops[i].cell[0][0]!='\0')
        {
          printf ("//--,%s,\"%s\",%s,%s", ops[i].cell[0], ops[i].cell[1],
                                              ops[i].cell[2], ops[i].cell[3]);

          if(ops[i].cell[30]!=NULL)
            strcpy (flags, ops[i].cell[30]);
          else
            flags[0]='\0';

          for (j=i+1; j<n_ops; j++)
            {
              if (ops[j].cell[0][0]!='\0')
                {
                  j--;
                  break;
                }
              else
                {
                  if(ops[j].cell[30]!=NULL)
                    if(ops[j].cell[30][0]!='\0')
                      strcpy (flags, ops[j].cell[30]);
                }
            }


          printf (",%d,%s", (j-i)+1, flags);

          printf ("\n");
        }

      i = j;
    }

  printf ("//--\n");
  printf ("//--\n");
  printf ("//----------------------------------------------------------------------------\n");
  printf ("//----------------------------------------------------------------------------\n");
  printf ("\n");
  printf ("\n");

  return (0);
}



///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
char *
parse (char *s)
{
  static char *last=NULL;

  if (s==NULL)
    {
      s = last;

      if (last==NULL)
        return (NULL);
    }
  else
    last=s;

  if (*s=='\"')
    {
      s++;
      for (last = s; *last!='\0' && *last!='\"'; last++)
       /* do nothing */;

      if (*last=='\0')
        last = NULL;
      else
        {
          *last = '\0';
          last++;

          if (*last==',')
            {
              last++;
              if (*last=='\0')
                last = NULL;
            }
        }
    }
  else
    {
      for (last = s; *last!=',' && *last!='\0'; last++)
        /* do nothing */;

      if (*last=='\0')
        last = NULL;
      else
        {
          *last = '\0';
          last++;
        }
    }

  strip (s);

  return (s);
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
int
load_file (char *filename)
{
  FILE *file;
  int i;

  n_ops = 0;

  file = fopen (filename, "r");
  if (file)
    {
      //fgets (ops[n_ops].line, LINELEN, file);
      //fgets (ops[n_ops].line, LINELEN, file);

      while (!feof (file))
        {
          fgets(ops[n_ops].line, LINELEN, file);
          strip (ops[n_ops].line);

          ops[n_ops].cell[0] = parse (ops[n_ops].line);

          if (stricmp (ops[n_ops].cell[0], "end")==0)
            break;

          for (i=1; i<MAXCELLS; i++)
            {
              ops[n_ops].cell[i] = parse (NULL);

              if (ops[n_ops].cell[i]==NULL)
                break;

              // Set default
              if (i>=14  && ops[n_ops].cell[i][0]=='\0')
                ops[n_ops].cell[i] = NULL;
                //ops[n_ops].cell[i] = ops[1].cell[i];
            }

          for (; i<MAXCELLS; i++)
            ops[n_ops].cell[i] = NULL;
            //ops[n_ops].cell[i] = ops[1].cell[i];


          n_ops++;
        }

      fclose (file);
      return (0);
    }
  else
    {
      printf ("Error opening file.\n");
      return (1);
    }
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
char *
strip (char *s)                   
{
  char *t;

  for (t=s; *t!='\0'; t++)
    *t = (char)toupper(*t);   // Look for end and convert to upper case

  for (t--; t>s; t--)
    if (!isspace(*t))
      break;

  if (t!=s)
    {
      t++;
      *t = '\0';
    }
  else
    {
      if (isspace(*t))
        *t = '\0';
      else
        *(t+1) = '\0';
    }

  return (s);
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
int
gen_unique (void)
{
  int r, c, i;

  for (i=0; i<MAX_UNIQUE; i++)
    {
      if (ops[0].cell[COL_OFFSET+i]==NULL)
        break;

      if (ops[0].cell[COL_OFFSET+i][0]=='\0')
        break;
    }

  n_unique = i;


  for (c=0; c<n_unique; c++)
    {
      unique[c].num=0;
      unique[c].col=COL_OFFSET;

      for (r=1; r<n_ops; r++)
        {
          if (ops[r].cell[COL_OFFSET+c]==NULL)
            continue;

          for (i=0; i<unique[c].num; i++)
            if (stricmp(unique[c].list[i], ops[r].cell[COL_OFFSET+c])==0)
              break;

          if (i==unique[c].num)
            {
              unique[c].list[i] = ops[r].cell[COL_OFFSET+c];
              unique[c].num++;

              if (unique[c].num >= MAXCELLS)
                {
                  printf ("Error:  gen_unique() MAXCELLS\n");
                  return (1);
                }
            }
        }
    }

  return (0);
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
char *
itob (int i, int d)
{
  int b;
  char *t;
  static char s[33];

  t = s;
  for (b=(1<<(d-1)); b!=0; b=b>>1)
    {
      if (b&i)
        *t='1';
      else
        *t='0';

      t++;
    }

  *t = '\0';

  return (s);
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
int
xtoi (char *s)
{
  int i;
  char t[2];

  while (*s!='\0' && !isxdigit(*s))
    s++;

  t[0] = (char)toupper(*s);
  t[1] = (char)toupper (*(s+1));

  if (t[0]>='A')
    i = 10+(t[0]-'A');
  else
    i = (t[0]-'0');

  if (t[1]>='A')
    i = (i<<4) | (10+(t[1]-'A'));
  else
    i = (i<<4) | (t[1]-'0');

  return (i);
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
int
n_bits (int i)
{
  int j;

  for (j=1; i > (1<<j) && j<32; j++)
    /* Do nothing */;

  return (j);
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

