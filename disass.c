#include <stdio.h>
#include "disasm.h"
#include "bc_def.h"

int main()
{
  int i;
  for (i = 0; i < sizeof(boot_prog_code)/sizeof(*boot_prog_code); i++)
    {
      int op = boot_prog_code[i] & 0xFC;
      switch(op)
	{
	case OP_PREFIX   : puts("OP_PREFIX   "); break;
	case OP_BRK      : puts("OP_BRK      "); break;
	case OP_SLEEP    : puts("OP_SLEEP    "); break;
	case OP_SIF      : puts("OP_SIF      "); break;
	case OP_MULT     : puts("OP_MULT     "); break;
	case OP_DIV      : puts("OP_DIV      "); break;
	case OP_TST      : puts("OP_TST      "); break;
	case OP_BSR      : puts("OP_BSR      "); break;
	case OP_BRA      : puts("OP_BRA      "); break;
	case OP_BLT      : puts("OP_BLT      "); break;
	case OP_BPL      : puts("OP_BPL      "); break;
	case OP_BMI      : puts("OP_BMI      "); break;
	case OP_BNE      : puts("OP_BNE      "); break;
	case OP_BEQ      : puts("OP_BEQ      "); break;
	case OP_BCC      : puts("OP_BCC      "); break;
	case OP_BCS      : puts("OP_BCS      "); break;


	case OP_SAL      : puts("OP_SAL      "); break;
	case OP_SAR      : puts("OP_SAR      "); break;
	case OP_SCL      : puts("OP_SCL      "); break;
	case OP_SCR      : puts("OP_SCR      "); break;
	default : switch (op & 0xF0)
	    {
	    case OP_LD       : puts("OP_LD       "); break;
	    case OP_ST       : puts("OP_ST       "); break;
	    case OP_ADD      : puts("OP_ADD      "); break;
	    case OP_ADDC     : puts("OP_ADDC     "); break;
	    case OP_SUB      : puts("OP_SUB      "); break;
	    case OP_SUBC     : puts("OP_SUBC     "); break;
	    case OP_NADD     : puts("OP_NADD     "); break;
	    case OP_CMP      : puts("OP_CMP      "); break;
	    case OP_OR       : puts("OP_OR       "); break;
	    case OP_AND      : puts("OP_AND      "); break;
	    case OP_XOR      : puts("OP_XOR      "); break;	      
	    default: printf("OP_%.04X\n", op);
	    }
	}
    }
}
