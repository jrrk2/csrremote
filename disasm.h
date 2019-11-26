#define OP_PREFIX   0x00
#define OP_BRK      0x04
#define OP_SLEEP    0x08
#define OP_SIF      0x0c
#define OP_MULT     0x90
#define OP_DIV      0x94
#define OP_TST      0x98
#define OP_BSR      0x9c
#define OP_BRA      0xe0
#define OP_BLT      0xe4
#define OP_BPL      0xe8
#define OP_BMI      0xec
#define OP_BNE      0xf0
#define OP_BEQ      0xf4
#define OP_BCC      0xf8
#define OP_BCS      0xfc

#define OP_LD       0x10
#define OP_ST       0x20
#define OP_ADD      0x30
#define OP_ADDC     0x40
#define OP_SUB      0x50
#define OP_SUBC     0x60
#define OP_NADD     0x70
#define OP_CMP      0x80
#define OP_OR       0xb0
#define OP_AND      0xc0
#define OP_XOR      0xd0

#define OP_SAL      0xa0
#define OP_SAR      0xa4
#define OP_SCL      0xa8
#define OP_SCR      0xac

#define OP_ST_F     0x01
#define OP_LD_F     0x05
#define OP_MODIF_U  0x0009
#define OP_MODIF_S  0x0109
#define OP_BC       0xff09
#define OP_BRXL     0xfe09
#define OP_ST_UX    0x02
#define OP_LD_UX    0x06
#define OP_ST_XH    0x0a
#define OP_LD_XH    0x0e
#define OP_ST_UY    0x03
#define OP_LD_UY    0x07
