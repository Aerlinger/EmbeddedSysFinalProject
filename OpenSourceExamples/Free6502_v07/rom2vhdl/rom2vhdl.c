//  ROM2VHDL  --  Converts a raw binary ROM image into VHDL source
//                code.
//  (c) 1999, Peak Audio, Inc.
//  Written by David Kessner
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int dump_rom (char *rom_filename, FILE *fout, char *indent);
void itob (unsigned long i, int bits, char *s);
void strip (char *s);


static int addrbits, databits, big_endian, rom_flag;
static char varname[128];


int
main (int argc, char *argv[])
{
  FILE *fin, *ftmp, *fout;
  char s[256], s2[256], *t;
  char indent[256];
  int i;


  if (argc<3 || argc>4)
    {
      printf ("Usage:\n");
      printf ("    rom2vhdl  <rom file> <vhdl template>  [<vhdl output>]\n");
      return (0);
    }


  addrbits=16;
  databits=32;
  big_endian=1;
  rom_flag = 0;
  strcpy (varname, "data");


  fin = fopen (argv[2], "rb");
  if (fin==NULL)
    {
      printf ("Error opening '%s'.\n", argv[2]);
      return (1);
    }


  ftmp = tmpfile();
  if (ftmp==NULL)
    {
      printf ("Error opening temp file.\n");
      fclose (fin);
      return (1);
    }


  while (fgets (s, sizeof(s), fin)!=NULL)
    {
      strip (s);
      strcpy (s2, s);

      t = strtok (s2, " \t\x0A\x0D");
      if (t!=NULL)
        {
          if (stricmp(t, "--addrbits")==0)
            {
              t = strtok (NULL, " \t\x0A\x0D");
              addrbits = atoi (t);
            }
          else if (stricmp(t, "--databits")==0)
            {
              t = strtok (NULL, " \t\x0A\x0D");
              databits = atoi (t);
            }
          else if (stricmp(t, "--varname")==0)
            {
              t = strtok (NULL, " \t\x0A\x0D");
              strcpy (varname, t);
            }
          else if (stricmp(t, "--big-endian")==0)
            {
              big_endian=1;
            }
          else if (stricmp(t, "--little-endian")==0)
            {
              big_endian=0;
            }
          else if (stricmp(t, "--start_of_rom")==0)
            {
              rom_flag = 1;
              fputs (s, ftmp);
              strcpy (indent, s);
              for (t=indent; *t!='\0' && isspace(*t); t++)
                /* just search */;

              *t = '\0';

              if (dump_rom (argv[1], ftmp, indent))
                {
                  fclose (fin);
                  fclose (ftmp);
                  return (1);
                }
            }
          else if (stricmp(t, "--end_of_rom")==0)
            {
              rom_flag = 0;
            }
        }

      // Copy the input file to the tmp file, except for
      // what's in the rom section
      if (rom_flag==0)
        fprintf (ftmp, "%s\n", s);
    }

  // close the input file
  fclose (fin);

  // Open the output file, and copy the contents of
  // ftmp to the output file.
  fout = fopen (argv[argc-1], "w");
  if (fout==NULL)
    {
      printf ("Error opening '%s'.\n", argv[argc-1]);
      fclose (ftmp);
      return (1);
    }

  rewind (ftmp);
  while (!feof(ftmp))
    {
      i = fread (s, sizeof(s[0]), sizeof(s)/sizeof(s[0]), ftmp);
      fwrite (s, sizeof(s[0]), i, fout);
    }


  fclose (ftmp);
  fclose (fout);

  return (0);
}



///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
int
dump_rom (char *rom_filename, FILE *fout, char *indent)
{
  FILE *fin;
  time_t t;
  unsigned long addr, addr2;
  unsigned char c[4];
  char s1[64], s2[64];
  unsigned long data;
  int i;

  if (addrbits<2 || addrbits>32)
    {
      printf ("Error:  addrbits is out of range (%d).\n", addrbits);
      return (1);
    }

  if (databits!=8 && databits!=16 && databits!=24 && databits!=32)
    {
      printf ("Error:  databits is out of range.\n");
      return (1);
    }

  fin = fopen (rom_filename, "rb");
  if (fin==NULL)
    {
      printf ("Error:  Can't open '%s'.\n", rom_filename);
      return (1);
    }

  time(&t);
  fprintf (fout, "%s-- rom2vhdl output.  %s", indent, ctime(&t));

  addr = 0;
  while (!feof(fin))
    {
      itob (addr, addrbits, s1);

      if (big_endian==1)
        {
          switch (databits)
            {
              case 8:  i=fread (c, sizeof(c[0]), 1, fin);
                       data = c[0];
                       addr2 = addr;
                       break;

              case 16: i=fread (c, sizeof(c[0]), 2, fin);
                       data = (c[0]<<8) | c[1];
                       addr2 = addr * 2;
                       break;

              case 24: i=fread (c, sizeof(c[0]), 3, fin);
                       data = (c[0]<<16) | (c[1]<<8) | c[2];
                       addr2 = addr * 3;
                       break;

              case 32: i=fread (c, sizeof(c[0]), 4, fin);
                       data = (c[0]<<24) | (c[1]<<16) | (c[2]<<8) | c[3];
                       addr2 = addr * 4;
                       break;
            }
        }
      else  // Little endian
        {
          switch (databits)
            {
              case 8:  i=fread (c, sizeof(c[0]), 1, fin);
                       data = c[0];
                       addr2 = addr;
                       break;

              case 16: i=fread (c, sizeof(c[0]), 2, fin);
                       data = (c[1]<<8) | c[0];
                       addr2 = addr * 2;
                       break;

              case 24: i=fread (c, sizeof(c[0]), 3, fin);
                       data = (c[2]<<16) | (c[1]<<8) | c[0];
                       addr2 = addr * 3;
                       break;

              case 32: i=fread (c, sizeof(c[0]), 4, fin);
                       data = (c[3]<<24) | (c[2]<<16) | (c[1]<<8) | c[0];
                       addr2 = addr * 4;
                       break;
            }
        }

      if (i>0)
        {
          itob (data, databits, s2);
          fprintf (fout, "%swhen \"%s\" =>  %s <= \"%s\";  -- %X = %X\n", indent, s1, varname, s2, addr2, data);
          addr++;
        }
    }

  fclose (fin);

  return (0);
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
void
itob (unsigned long i, int bits, char *s)
{
  int j;

  for (j=bits-1; j>=0; j--, s++)
    *s = ((char) (((1UL<<j)&i)!=0)?'1':'0');

  *s='\0';
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
void
strip (char *s)
{
  char *t;

  for (t=s; *t!='\0'; t++)
    /* do nothing */;

  for (t--; t>=s; t--)
    if (!isspace(*t))
      break;

  t++;
  *t = '\0';
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

