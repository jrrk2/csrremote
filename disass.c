#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "disasm.h"
#include "disass.h"
#include "bc_def.h"

static char hex[99];
static int pc;

const char *regspace(signed short combined)
{
  static char op2[99];
  switch(combined & 0xFFFF)
    {
    case XAP_AH                          : sprintf(op2, "$XAP_AH                          "); break;
    case XAP_AL                          : sprintf(op2, "$XAP_AL                          "); break;
    case XAP_UXH                         : sprintf(op2, "$XAP_UXH                         "); break;
    case XAP_UXL                         : sprintf(op2, "$XAP_UXL                         "); break;
    case XAP_UY                          : sprintf(op2, "$XAP_UY                          "); break;
    case XAP_IXH                         : sprintf(op2, "$XAP_IXH                         "); break;
    case XAP_IXL                         : sprintf(op2, "$XAP_IXL                         "); break;
    case XAP_IY                          : sprintf(op2, "$XAP_IY                          "); break;
    case XAP_FLAGS                       : sprintf(op2, "$XAP_FLAGS                       "); break;
    case XAP_PCH                         : sprintf(op2, "$XAP_PCH                         "); break;
    case XAP_PCL                         : sprintf(op2, "$XAP_PCL                         "); break;
    default: sprintf(op2, "0x%X", combined); break;
    }
  return op2;
}

const char *addr(int prefix, int op)
{
  static char op1[99];
  int combined = (prefix << 8) + (((int16_t)op) >> 8);
  switch ((op>>2)&3)
    {
    case 0: sprintf(op1, "AH"); break;
    case 1: sprintf(op1, "AL"); break;
    case 2: sprintf(op1, "X"); break;
    case 3: sprintf(op1, "Y"); break;
    }
  switch (op&3)
    {
    case 0: sprintf(op1+strlen(op1), ", #0x%X", combined); break;
    case 1: sprintf(op1+strlen(op1), ", @%s", regspace(combined)); break;
    case 2: sprintf(op1+strlen(op1), ", @(0x%X,X)", combined); break;
    case 3: sprintf(op1+strlen(op1), ", @(0x%X,Y)", combined); break;
    }
  return op1;
}

const char *baddr(int prefix, int op)
{
  static char op1[99];
  int combined = (prefix << 8) + (((int16_t)op) >> 8);
  switch (op&3)
    {
    case 0: sprintf(op1, "0x%.6X", pc+combined+(prefix?2:1)); break;
    case 1: sprintf(op1, "@%s", regspace(combined)); break;
    case 2: sprintf(op1, "0x%X,X", combined); break;
    case 3: sprintf(op1, "@(0x%X,Y)", combined); break;
    }
  return op1;
}

const char *saddr(int prefix, int op)
{
  static char op1[99];
  int combined = (prefix << 8) + (((int16_t)op) >> 8);
  switch (op&3)
    {
    case 0: sprintf(op1, "#0x%X", combined); break;
    case 1: sprintf(op1, "@%s", regspace(combined)); break;
    case 2: sprintf(op1, "@(0x%X,X)", combined); break;
    case 3: sprintf(op1, "@(0x%X,Y)", combined); break;
    }
  return op1;
}

const char *hc(void)
{
  static char fmt[99];
  hex[20] = 0;
  sprintf(fmt, "0x%.6X: %s", pc, hex);
  return fmt;
}

enum {org = (boot_addr-0xA000)+0x140000};

int disass(const char *nam)
{
  int i, prefix = 0;
  int indent = 0;
  FILE *outf = fopen(nam, "w");
  fprintf(outf, "/* This file is illustrative only, and not processor accurate */\n\n");
  memset(hex, ' ', sizeof(hex));
  pc = org;
  for (i = 0; i < sizeof(boot_prog_code)/sizeof(*boot_prog_code); i++)
    {
      int op0 = boot_prog_code[i];
      int op = op0 & 0xFC;
      int prefix_used = 0;
      char fmt[6];
      sprintf(fmt, "%.4X ", op0);
      strncpy(hex+indent, fmt, 5);
      switch(op0)
        {
        case OP_ST_F     : fprintf(outf, "%sOP_ST_F     \n", hc()); break;
        case OP_LD_F     : fprintf(outf, "%sOP_LD_F     \n", hc()); break;
        case OP_MODIF_U  : fprintf(outf, "%sOP_MODIF_U  \n", hc()); break;
        case OP_MODIF_S  : fprintf(outf, "%sOP_MODIF_S  \n", hc()); break;
        case OP_BC       : fprintf(outf, "%sOP_BC       \n", hc()); break;
        case OP_BRXL     : fprintf(outf, "%sOP_BRXL     \n", hc()); break;
        case OP_ST_UX    : fprintf(outf, "%sOP_ST_UX    \n", hc()); break;
        case OP_LD_UX    : fprintf(outf, "%sOP_LD_UX    \n", hc()); break;
        case OP_ST_XH    : fprintf(outf, "%sOP_ST_XH    \n", hc()); break;
        case OP_LD_XH    : fprintf(outf, "%sOP_LD_XH    \n", hc()); break;
        case OP_ST_UY    : fprintf(outf, "%sOP_ST_UY    \n", hc()); break;
        case OP_LD_UY    : fprintf(outf, "%sOP_LD_UY    \n", hc()); break;
        default: switch(op)
            {
            case OP_PREFIX   : prefix = (prefix << 8) + (((int16_t)op0) >> 8); prefix_used = 1; break;
            case OP_BRK      : fprintf(outf, "%sOP_BRK      \n", hc()); break;
            case OP_SLEEP    : fprintf(outf, "%sOP_SLEEP    \n", hc()); break;
            case OP_SIF      : fprintf(outf, "%sOP_SIF      \n", hc()); break;
            case OP_MULT     : fprintf(outf, "%sOP_MULT     %s\n", hc(), addr(prefix, op0)); break;
            case OP_DIV      : fprintf(outf, "%sOP_DIV      %s\n", hc(), addr(prefix, op0)); break;
            case OP_TST      : fprintf(outf, "%sOP_TST      %s\n", hc(), addr(prefix, op0)); break;
            case OP_BSR      : fprintf(outf, "%sOP_BSR      %s\n", hc(), baddr(prefix, op0)); break;
            case OP_BRA      : fprintf(outf, "%sOP_BRA      %s\n", hc(), baddr(prefix, op0)); break;
            case OP_BLT      : fprintf(outf, "%sOP_BLT      %s\n", hc(), baddr(prefix, op0)); break;
            case OP_BPL      : fprintf(outf, "%sOP_BPL      %s\n", hc(), baddr(prefix, op0)); break;
            case OP_BMI      : fprintf(outf, "%sOP_BMI      %s\n", hc(), baddr(prefix, op0)); break;
            case OP_BNE      : fprintf(outf, "%sOP_BNE      %s\n", hc(), baddr(prefix, op0)); break;
            case OP_BEQ      : fprintf(outf, "%sOP_BEQ      %s\n", hc(), baddr(prefix, op0)); break;
            case OP_BCC      : fprintf(outf, "%sOP_BCC      %s\n", hc(), baddr(prefix, op0)); break;
            case OP_BCS      : fprintf(outf, "%sOP_BCS      %s\n", hc(), baddr(prefix, op0)); break;
            case OP_SAL      : fprintf(outf, "%sOP_SAL      %s\n", hc(), saddr(prefix, op0)); break;
            case OP_SAR      : fprintf(outf, "%sOP_SAR      %s\n", hc(), saddr(prefix, op0)); break;
            case OP_SCL      : fprintf(outf, "%sOP_SCL      %s\n", hc(), saddr(prefix, op0)); break;
            case OP_SCR      : fprintf(outf, "%sOP_SCR      %s\n", hc(), saddr(prefix, op0)); break;
            default :
              fprintf(outf, "%s", hc());
              switch (op & 0xF0)
                {
                case OP_LD       : fprintf(outf, "OP_LD       %s\n", addr(prefix, op0)); break;
                case OP_ST       : fprintf(outf, "OP_ST       %s\n", addr(prefix, op0)); break;
                case OP_ADD      : fprintf(outf, "OP_ADD      %s\n", addr(prefix, op0)); break;
                case OP_ADDC     : fprintf(outf, "OP_ADDC     %s\n", addr(prefix, op0)); break;
                case OP_SUB      : fprintf(outf, "OP_SUB      %s\n", addr(prefix, op0)); break;
                case OP_SUBC     : fprintf(outf, "OP_SUBC     %s\n", addr(prefix, op0)); break;
                case OP_NADD     : fprintf(outf, "OP_NADD     %s\n", addr(prefix, op0)); break;
                case OP_CMP      : fprintf(outf, "OP_CMP      %s\n", addr(prefix, op0)); break;
                case OP_OR       : fprintf(outf, "OP_OR       %s\n", addr(prefix, op0)); break;
                case OP_AND      : fprintf(outf, "OP_AND      %s\n", addr(prefix, op0)); break;
                case OP_XOR      : fprintf(outf, "OP_XOR      %s\n", addr(prefix, op0)); break;	      
                default: fprintf(outf, "OP_%.04X\n", op);
                }
            }
        }
        if (prefix_used)
          {
          indent += 5;
          }
        else
          {
          prefix = 0;
          indent = 0;
          memset(hex, ' ', sizeof(hex));
          pc = org+i;
          }
        
    }
}
