#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "disasm.h"
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

extern uint16_t newboot[], newxdv[];

int main()
{
  int i, prefix = 0;
  int indent = 0;
  memset(hex, ' ', sizeof(hex));
  pc = org;
  for (i = 0; i < sizeof(boot_prog_data)/sizeof(*boot_prog_data); i++)
    {
      if (newxdv[i] != boot_prog_data[i])
        abort();
    }
  for (i = 0; i < sizeof(boot_prog_code)/sizeof(*boot_prog_code); i++)
    {
      int op0 = boot_prog_code[i];
      int op = op0 & 0xFC;
      int prefix_used = 0;
      char fmt[6];
      if (newboot[i] != op0)
        abort();
      sprintf(fmt, "%.4X ", op0);
      strncpy(hex+indent, fmt, 5);
      switch(op0)
        {
        case OP_ST_F     : printf("%sOP_ST_F     \n", hc()); break;
        case OP_LD_F     : printf("%sOP_LD_F     \n", hc()); break;
        case OP_MODIF_U  : printf("%sOP_MODIF_U  \n", hc()); break;
        case OP_MODIF_S  : printf("%sOP_MODIF_S  \n", hc()); break;
        case OP_BC       : printf("%sOP_BC       \n", hc()); break;
        case OP_BRXL     : printf("%sOP_BRXL     \n", hc()); break;
        case OP_ST_UX    : printf("%sOP_ST_UX    \n", hc()); break;
        case OP_LD_UX    : printf("%sOP_LD_UX    \n", hc()); break;
        case OP_ST_XH    : printf("%sOP_ST_XH    \n", hc()); break;
        case OP_LD_XH    : printf("%sOP_LD_XH    \n", hc()); break;
        case OP_ST_UY    : printf("%sOP_ST_UY    \n", hc()); break;
        case OP_LD_UY    : printf("%sOP_LD_UY    \n", hc()); break;
        default: switch(op)
            {
            case OP_PREFIX   : prefix = (prefix << 8) + (((int16_t)op0) >> 8); prefix_used = 1; break;
            case OP_BRK      : printf("%sOP_BRK      \n", hc()); break;
            case OP_SLEEP    : printf("%sOP_SLEEP    \n", hc()); break;
            case OP_SIF      : printf("%sOP_SIF      \n", hc()); break;
            case OP_MULT     : printf("%sOP_MULT     %s\n", hc(), addr(prefix, op0)); break;
            case OP_DIV      : printf("%sOP_DIV      %s\n", hc(), addr(prefix, op0)); break;
            case OP_TST      : printf("%sOP_TST      %s\n", hc(), addr(prefix, op0)); break;
            case OP_BSR      : printf("%sOP_BSR      %s\n", hc(), baddr(prefix, op0)); break;
            case OP_BRA      : printf("%sOP_BRA      %s\n", hc(), baddr(prefix, op0)); break;
            case OP_BLT      : printf("%sOP_BLT      %s\n", hc(), baddr(prefix, op0)); break;
            case OP_BPL      : printf("%sOP_BPL      %s\n", hc(), baddr(prefix, op0)); break;
            case OP_BMI      : printf("%sOP_BMI      %s\n", hc(), baddr(prefix, op0)); break;
            case OP_BNE      : printf("%sOP_BNE      %s\n", hc(), baddr(prefix, op0)); break;
            case OP_BEQ      : printf("%sOP_BEQ      %s\n", hc(), baddr(prefix, op0)); break;
            case OP_BCC      : printf("%sOP_BCC      %s\n", hc(), baddr(prefix, op0)); break;
            case OP_BCS      : printf("%sOP_BCS      %s\n", hc(), baddr(prefix, op0)); break;
            case OP_SAL      : printf("%sOP_SAL      %s\n", hc(), saddr(prefix, op0)); break;
            case OP_SAR      : printf("%sOP_SAR      %s\n", hc(), saddr(prefix, op0)); break;
            case OP_SCL      : printf("%sOP_SCL      %s\n", hc(), saddr(prefix, op0)); break;
            case OP_SCR      : printf("%sOP_SCR      %s\n", hc(), saddr(prefix, op0)); break;
            default :
              printf("%s", hc());
              switch (op & 0xF0)
                {
                case OP_LD       : printf("OP_LD       %s\n", addr(prefix, op0)); break;
                case OP_ST       : printf("OP_ST       %s\n", addr(prefix, op0)); break;
                case OP_ADD      : printf("OP_ADD      %s\n", addr(prefix, op0)); break;
                case OP_ADDC     : printf("OP_ADDC     %s\n", addr(prefix, op0)); break;
                case OP_SUB      : printf("OP_SUB      %s\n", addr(prefix, op0)); break;
                case OP_SUBC     : printf("OP_SUBC     %s\n", addr(prefix, op0)); break;
                case OP_NADD     : printf("OP_NADD     %s\n", addr(prefix, op0)); break;
                case OP_CMP      : printf("OP_CMP      %s\n", addr(prefix, op0)); break;
                case OP_OR       : printf("OP_OR       %s\n", addr(prefix, op0)); break;
                case OP_AND      : printf("OP_AND      %s\n", addr(prefix, op0)); break;
                case OP_XOR      : printf("OP_XOR      %s\n", addr(prefix, op0)); break;	      
                default: printf("OP_%.04X\n", op);
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
