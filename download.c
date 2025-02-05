#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "bc_def.h"
#include "spi.h"
#include "download.h"

static uint16_t tmp107[107], readback_code[3798], readback_data[589], tmp80[80], ones128[128], crc256[256];

static bool (*readblock)(uint16_t, int, uint16_t *);
static bool (*readword)(uint16_t addr, uint16_t *data);
static bool (*writeblock)(uint16_t addr, int size, uint16_t buffer[]);
static bool (*writeword)(uint16_t addr, uint16_t data);
static bool (*isxapstopped)(void);

static int read16_1(int addr)
{
  uint16_t data;
  readword(addr, &data);
  return data;
}

static int read16(int addr, int cnt, uint16_t *buf)
{
  return readblock(addr, cnt, buf);
}

static int write16_1(int addr, int value)
{
  writeword(addr, value);
}

static int write16(int addr, int cnt, uint16_t *buf)
{
  return writeblock(addr, cnt, buf);
}

static bool wait_xap_stopped(void)
{
  while (!isxapstopped())
    usleep(1000);
  fprintf(stderr, "Stopped\n");
  return 1;
}

static void progiter1(void)
{
 wait_xap_stopped();
 read16_1(0xc000); /* returned */
 read16_1(0xc000); /* returned*/
 read16_1(0xc00a); /* returned*/
 read16_1(0xc00a); /* returned*/
 read16_1(0xc00b); /* returned*/
 read16_1(0xc00b); /* returned*/
}

int download(  bool (*_readblock)(uint16_t, int, uint16_t *),
               bool (*_read)(uint16_t addr, uint16_t *data),
               bool (*_writeblock)(uint16_t addr, int size, uint16_t buffer[]),
               bool (*_write)(uint16_t addr, uint16_t data),
               bool (*_IsXAPStopped)(void),
               uint16_t writebuf[], int first, int last)
{
  int i, sector = 0;
  int first_done = 0;
  readblock = _readblock;
  readword = _read;
  writeblock = _writeblock;
  writeword = _write;
  isxapstopped = _IsXAPStopped;
  memset(tmp107, 0, 107*sizeof(uint16_t));
  tmp107[106] = 2;
  
spi_set_clock(1000); /**/
spi_set_clock(20); /**/
read16_1(0xff9a); /* returned 0x4826
*/
read16_1(0xff9a); /* returned 0x4826
*/
spi_set_clock(1000); /*Stopped
*/
spi_set_clock(20); /**/
write16_1(0xf9c0, 0x0009); /*
*/
write16_1(0xf9c0, 0x0009); /*
*/
write16_1(0xf9c0, 0x0000); /*
*/
write16_1(0xf9c0, 0x0000); /*
*/
write16_1(0xf9c0, 0x0000); /*
*/
spi_set_clock(1000); /**/
spi_set_clock(20); /**/
write16_1(0x006a, 0x0003); /*
*/
spi_set_clock(20); /**/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
spi_set_clock(1000); /**/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
spi_set_clock(666); /**/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
spi_set_clock(444); /**/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
spi_set_clock(296); /**/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
spi_set_clock(197); /**/
write16_1(0xa000, 0x0000); /*
*/
read16_1(0xa000); /* returned 0x0000
*/
write16_1(0xa001, 0x0000); /*
*/
read16_1(0xa001); /* returned 0x0000
*/
write16_1(0xa002, 0x00e0); /*
*/
read16_1(0xa002); /* returned 0x00e0
*/
read16_1(0xffe9); /* returned 0x0000
*/
read16_1(0xffe9); /* returned 0x0000
*/
write16_1(0xffe9, 0x0054); /*
*/
read16_1(0xffe9); /* returned 0x0054
*/
write16_1(0xffea, 0x0000); /*
*/
read16_1(0xffea); /* returned 0x0000
*/
read16_1(0xff7e); /* returned 0x0000
*/
read16_1(0xff7e); /* returned 0x0000
*/
write16_1(0xff7e, 0x0000); /*
*/
read16_1(0xff7e); /* returned 0x0000
*/
write16_1(0xffde, 0x0000); /*
*/
read16_1(0xffde); /* returned 0x0000
*/
read16_1(0xffe8); /* returned 0x0000
*/
read16_1(0xffe8); /* returned 0x0000
*/
write16_1(0xffe8, 0x0000); /*
*/
read16_1(0xffe8); /* returned 0x0000
*/
write16_1(0x0076, 0x0002); /*
*/
read16_1(0x0076); /* returned 0x0002
*/
write16_1(0xff91, 0x0005); /*
*/
write16_1(0x0077, 0x0001); /*
*/
read16_1(0x0077); /* returned 0x0001
*/
write16_1(0x006a, 0x0000); /*
*/
read16_1(0x006a); /* returned 0x0000
*/
read16_1(0xff91); /* returned 0xffff
*/
read16_1(0xff91); /* returned 0x0000
*/
read16_1(0xff91); /* returned 0x0000
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16(0x0000, 107, tmp107); /* { zeros, followed by 2 }
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
read16_1(0xffeb); /* returned 0x00ff
*/
read16_1(0xffeb); /* returned 0x00ff
*/
read16_1(0xffec); /* returned 0xffff
*/
read16_1(0xffec); /* returned 0xffff
*/
write16(0xffe0, 16, tmp107); /* { zeros }
*/
write16_1(0xffeb, 0x00ff); /*
*/
read16_1(0xffeb); /* returned 0x00ff
*/
write16_1(0xffec, 0xffff); /*
*/
read16_1(0xffec); /* returned 0xffff
*/
write16_1(0xff52, 0x0000); /*
*/
read16_1(0xff52); /* returned 0x0000
*/
write16(0xc400, 589, boot_prog_data); /* {}
*/
read16(0xc400, 589, readback_data); /* returned {}
*/
write16(0xc670, 3798, boot_prog_code); /* {}
*/
read16(0xc670, 3798, readback_code); /* returned {}
*/
write16_1(0xc670, 0x6f10); /*
*/
read16_1(0xc670); /* returned 0x6f10
*/
write16_1(0xc672, 0x0e10); /*
*/
read16_1(0xc672); /* returned 0x0e10
*/
write16_1(0xffe9, 0x0014); /*
*/
read16_1(0xffe9); /* returned 0x0014
*/
write16_1(0xffea, 0x2670); /*
*/
read16_1(0xffea); /* returned 0x2670
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0001); /*
Running
                           */
 wait_xap_stopped();
read16_1(0xc000); /* returned 0x0000
*/
read16_1(0xc000); /* returned 0x0000
*/
write16_1(0xc003, 0x0000); /*
*/
write16_1(0xc000, 0x0001); /*
*/
read16_1(0xc000); /* returned 0x0001
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0001); /*
Running
                           */
 wait_xap_stopped();
read16_1(0xc000); /* returned 0x0000
*/
read16_1(0xc000); /* returned 0x0000
*/
read16_1(0xc00d); /* returned 0x0014
*/
read16_1(0xc00d); /* returned 0x0014
*/
read16_1(0xc010); /* returned 0x0080
*/
read16_1(0xc010); /* returned 0x0080
*/
read16_1(0xc001); /* returned 0x0001
*/
read16_1(0xc001); /* returned 0x0001
*/
read16_1(0xa000); /* returned 0x0001
*/
read16_1(0xa000); /* returned 0x0001
*/
read16_1(0xa001); /* returned 0x225b
*/
read16_1(0xa001); /* returned 0x225b
*/
read16_1(0xc006); /* returned 0x1000
*/
read16_1(0xc006); /* returned 0x1000
*/
read16_1(0xc002); /* returned 0x0080
*/
read16_1(0xc002); /* returned 0x0080
*/
read16(0xa000, 80, tmp80); /* returned { flash CFI information}
*/
read16(0xa000, 80, tmp80); /* returned { ditto }
*/
read16_1(0xff9a); /* returned 0x4826
*/
read16_1(0xff9a); /* returned 0x4826
*/
spi_set_clock(20); /**/
write16_1(0x006a, 0x0003); /*
*/
spi_set_clock(20); /**/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
spi_set_clock(1000); /**/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
spi_set_clock(666); /**/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
spi_set_clock(444); /**/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
spi_set_clock(296); /**/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
read16_1(0xa000); /* returned 0x0000
*/
write16_1(0xa001, 0x0000); /*
*/
write16_1(0xa001, 0x0000); /*
*/
write16_1(0xa001, 0x0000); /*
*/
write16_1(0xa001, 0x0000); /*
*/
write16_1(0xa001, 0x0000); /*
*/
write16_1(0xa001, 0x0000); /*
*/
write16_1(0xa001, 0x0000); /*
*/
write16_1(0xa001, 0x0000); /*
*/
spi_set_clock(197); /**/
write16_1(0xa001, 0x0000); /*
*/
read16_1(0xa001); /* returned 0x0000
*/
write16_1(0xa002, 0x00e0); /*
*/
read16_1(0xa002); /* returned 0x00e0
*/
read16_1(0xffe9); /* returned 0x0014
*/
read16_1(0xffe9); /* returned 0x0014
*/
write16_1(0xffe9, 0x0054); /*
*/
read16_1(0xffe9); /* returned 0x0054
*/
write16_1(0xffea, 0x0000); /*
*/
read16_1(0xffea); /* returned 0x0000
*/
read16_1(0xff7e); /* returned 0x0000
*/
read16_1(0xff7e); /* returned 0x0000
*/
write16_1(0xff7e, 0x0000); /*
*/
read16_1(0xff7e); /* returned 0x0000
*/
write16_1(0xffde, 0x0000); /*
*/
read16_1(0xffde); /* returned 0x0000
*/
read16_1(0xffe8); /* returned 0x0015
*/
read16_1(0xffe8); /* returned 0x0015
*/
write16_1(0xffe8, 0x0000); /*
*/
read16_1(0xffe8); /* returned 0x0000
*/
write16_1(0x0076, 0x0002); /*
*/
read16_1(0x0076); /* returned 0x0002
*/
write16_1(0xff91, 0x0005); /*
*/
write16_1(0x0077, 0x0001); /*
*/
read16_1(0x0077); /* returned 0x0001
*/
write16_1(0x006a, 0x0000); /*
*/
read16_1(0x006a); /* returned 0x0000
*/
read16_1(0xff91); /* returned 0x0001
*/
read16_1(0xff91); /* returned 0x0000
*/
read16_1(0xff91); /* returned 0x0000
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16(0x0000, 107, tmp107); /* { eros , follwoed by 2}
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
read16_1(0xffeb); /* returned 0x00ff
*/
read16_1(0xffeb); /* returned 0x00ff
*/
read16_1(0xffec); /* returned 0xffff
*/
read16_1(0xffec); /* returned 0xffff
*/
write16(0xffe0, 16, tmp107); /* { zeros }
*/
write16_1(0xffeb, 0x00ff); /*
*/
read16_1(0xffeb); /* returned 0x00ff
*/
write16_1(0xffec, 0xffff); /*
*/
read16_1(0xffec); /* returned 0xffff
*/
write16_1(0xff52, 0x0000); /*
*/
read16_1(0xff52); /* returned 0x0000
*/
write16(0xc400, 589, boot_prog_data); /* {}
*/
read16(0xc400, 589, readback_data); /* returned {}
*/
write16(0xc670, 3798, boot_prog_code); /* {}
*/
read16(0xc670, 3798, readback_code); /* returned {}
*/
write16_1(0xc670, 0x6f10); /*
*/
read16_1(0xc670); /* returned 0x6f10
*/
write16_1(0xc672, 0x0e10); /*
*/
read16_1(0xc672); /* returned 0x0e10
*/
write16_1(0xffe9, 0x0014); /*
*/
read16_1(0xffe9); /* returned 0x0014
*/
write16_1(0xffea, 0x2670); /*
*/
read16_1(0xffea); /* returned 0x2670
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0001); /*
Running
                           */
 wait_xap_stopped();
read16_1(0xc000); /* returned 0x0000
*/
read16_1(0xc000); /* returned 0x0000
*/
write16_1(0xc003, 0x0000); /*
*/
write16_1(0xc000, 0x0001); /*
*/
read16_1(0xc000); /* returned 0x0001
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0001); /*
Running
                           */
 wait_xap_stopped();
read16_1(0xc000); /* returned 0x0000
*/
read16_1(0xc000); /* returned 0x0000
*/
read16_1(0xc00d); /* returned 0x0014
*/
read16_1(0xc00d); /* returned 0x0014
*/
read16_1(0xc010); /* returned 0x0080
*/
read16_1(0xc010); /* returned 0x0080
*/
read16_1(0xc001); /* returned 0x0001
*/
read16_1(0xc001); /* returned 0x0001
*/
read16_1(0xa000); /* returned 0x0001
*/
read16_1(0xa000); /* returned 0x0001
*/
read16_1(0xa001); /* returned 0x225b
*/
read16_1(0xa001); /* returned 0x225b
*/
read16_1(0xc006); /* returned 0x1000
*/
read16_1(0xc006); /* returned 0x1000
*/
read16_1(0xc002); /* returned 0x0080
*/
read16_1(0xc002); /* returned 0x0080
*/
 read16(0xa000, 80, tmp80); /* returned { CFI information}
*/
 read16(0xa000, 80, tmp80); /* returned { ditto }
*/
read16_1(0xff9a); /* returned 0x4826
*/
read16_1(0xff9a); /* returned 0x4826
*/
 for (sector = first; sector <= last; sector++)
   {
     write16_1(0xc008, sector >> 4); /**/
     write16_1(0xc009, sector << 12); /**/
     write16_1(0xc000, 0x0008); /**/
     read16_1(0xc000); /* returned */
     write16_1(0x006a, 0x0002); /**/
     write16_1(0x006a, 0x0003); /**/
     write16_1(0x006a, 0x0002); /**/
     write16_1(0x006a, 0x0001); /**/
     progiter1();
   }
spi_set_clock(20); /**/
write16_1(0xf9c0, 0x0009); /*
*/
write16_1(0xf9c0, 0x0009); /*
*/
write16_1(0xf9c0, 0x0000); /*
*/
write16_1(0xf9c0, 0x0000); /*
*/
write16_1(0xf9c0, 0x0000); /*
*/
spi_set_clock(197); /**/
spi_set_clock(20); /**/
write16_1(0x006a, 0x0003); /*
*/
spi_set_clock(20); /**/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0003); /*
*/
spi_set_clock(1000); /**/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
spi_set_clock(666); /**/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
spi_set_clock(444); /**/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
spi_set_clock(296); /**/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
spi_set_clock(197); /**/
write16_1(0xa000, 0x0000); /*
*/
read16_1(0xa000); /* returned 0x0000
*/
write16_1(0xa001, 0x0000); /*
*/
read16_1(0xa001); /* returned 0x0000
*/
write16_1(0xa002, 0x00e0); /*
*/
read16_1(0xa002); /* returned 0x00e0
*/
read16_1(0xffe9); /* returned 0x0014
*/
read16_1(0xffe9); /* returned 0x0014
*/
write16_1(0xffe9, 0x0054); /*
*/
read16_1(0xffe9); /* returned 0x0054
*/
write16_1(0xffea, 0x0000); /*
*/
read16_1(0xffea); /* returned 0x0000
*/
read16_1(0xff7e); /* returned 0x0000
*/
read16_1(0xff7e); /* returned 0x0000
*/
write16_1(0xff7e, 0x0000); /*
*/
read16_1(0xff7e); /* returned 0x0000
*/
write16_1(0xffde, 0x0000); /*
*/
read16_1(0xffde); /* returned 0x0000
*/
read16_1(0xffe8); /* returned 0x0015
*/
read16_1(0xffe8); /* returned 0x0015
*/
write16_1(0xffe8, 0x0000); /*
*/
read16_1(0xffe8); /* returned 0x0000
*/
write16_1(0x0076, 0x0002); /*
*/
read16_1(0x0076); /* returned 0x0002
*/
write16_1(0xff91, 0x0005); /*
*/
write16_1(0x0077, 0x0001); /*
*/
read16_1(0x0077); /* returned 0x0001
*/
write16_1(0x006a, 0x0000); /*
*/
read16_1(0x006a); /* returned 0x0000
*/
read16_1(0xff91); /* returned 0x0001
*/
read16_1(0xff91); /* returned 0x0000
*/
read16_1(0xff91); /* returned 0x0000
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
 write16(0x0000, 107, tmp107); /* { zeros, followed by 2 }
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
read16_1(0xffeb); /* returned 0x00ff
*/
read16_1(0xffeb); /* returned 0x00ff
*/
read16_1(0xffec); /* returned 0xffff
*/
read16_1(0xffec); /* returned 0xffff
*/
 write16(0xffe0, 16, tmp107); /* { zeros }
*/
write16_1(0xffeb, 0x00ff); /*
*/
read16_1(0xffeb); /* returned 0x00ff
*/
write16_1(0xffec, 0xffff); /*
*/
read16_1(0xffec); /* returned 0xffff
*/
write16_1(0xff52, 0x0000); /*
*/
read16_1(0xff52); /* returned 0x0000
*/
write16(0xc400, 589, boot_prog_data); /* {}
*/
read16(0xc400, 589, readback_data); /* returned {}
*/
write16(0xc670, 3798, boot_prog_code); /* {}
*/
read16(0xc670, 3798, readback_code); /* returned {}
*/
write16_1(0xc670, 0x6f10); /*
*/
read16_1(0xc670); /* returned 0x6f10
*/
write16_1(0xc672, 0x0e10); /*
*/
read16_1(0xc672); /* returned 0x0e10
*/
write16_1(0xffe9, 0x0014); /*
*/
read16_1(0xffe9); /* returned 0x0014
*/
write16_1(0xffea, 0x2670); /*
*/
read16_1(0xffea); /* returned 0x2670
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0001); /*
Running
                           */
 wait_xap_stopped();
read16_1(0xc000); /* returned 0x0000
*/
read16_1(0xc000); /* returned 0x0000
*/
write16_1(0xc003, 0x0000); /*
*/
write16_1(0xc000, 0x0001); /*
*/
read16_1(0xc000); /* returned 0x0001
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0001); /*
Running
                           */
 wait_xap_stopped();
read16_1(0xc000); /* returned 0x0000
*/
read16_1(0xc000); /* returned 0x0000
*/
read16_1(0xc00d); /* returned 0x0014
*/
read16_1(0xc00d); /* returned 0x0014
*/
read16_1(0xc010); /* returned 0x0080
*/
read16_1(0xc010); /* returned 0x0080
*/
read16_1(0xc001); /* returned 0x0001
*/
read16_1(0xc001); /* returned 0x0001
*/
read16_1(0xa000); /* returned 0x0001
*/
read16_1(0xa000); /* returned 0x0001
*/
read16_1(0xa001); /* returned 0x225b
*/
read16_1(0xa001); /* returned 0x225b
*/
read16_1(0xc006); /* returned 0x1000
*/
read16_1(0xc006); /* returned 0x1000
*/
read16_1(0xc002); /* returned 0x0080
*/
read16_1(0xc002); /* returned 0x0080
*/
 read16(0xa000, 80, tmp80); /* returned { CFI information }
*/
 read16(0xa000, 80, tmp80); /* returned { ditto }
*/
read16_1(0xff9a); /* returned 0x4826
*/
read16_1(0xff9a); /* returned 0x4826
*/
 memset(ones128, 0, sizeof(ones128));
 for (i = first; i <= last; i++) ones128[i] = 1;
 write16(0xa000, 128, ones128); /* { all ones }
*/
write16_1(0xc000, 0x0003); /*
*/
read16_1(0xc000); /* returned 0x0003
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0003); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0001); /* Running */
 progiter1();

 read16(0xa000, 256, crc256); /* returned { 128 x 32-bit CRC }
*/
 read16(0xa000, 256, crc256); /* returned { 128 x 32-bit CRC }
*/
read16_1(0xff9a); /* returned 0x4826
*/
read16_1(0xff9a); /* returned 0x4826
*/
 for (sector = first; sector <= last; sector++)
   {
     if (sector%2 == 0)
       {
         write16(0xa000, 4096, writebuf+(sector<<12));
         if (first_done) progiter1();
         write16_1(0xc008, sector >> 4); /**/
         write16_1(0xc009, sector << 12); /**/
         write16_1(0xc000, 0x0006); /* write from 0xa000 */
       }
     else
       {
         write16(0xb000, 4096, writebuf+(sector<<12));
         progiter1();
         write16_1(0xc008, sector >> 4); /**/
         write16_1(0xc009, sector << 12); /**/
         write16_1(0xc000, 0x0007); /* write from 0xb000 */
       }
     read16_1(0xc000); /* returned */
     write16_1(0x006a, 0x0002); /**/
     write16_1(0x006a, 0x0003); /**/
     write16_1(0x006a, 0x0002); /**/
     write16_1(0x006a, 0x0001); /**/
     first_done = 1;
   }
 progiter1();
 spi_set_clock(20); /**/
write16_1(0x006a, 0x0003); /**/
spi_set_clock(20); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
write16_1(0x006a, 0x0003); /**/
spi_set_clock(1000); /**/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
spi_set_clock(666); /**/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
spi_set_clock(444); /**/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
spi_set_clock(296); /**/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
write16_1(0xa000, 0x0000); /*
*/
spi_set_clock(197); /**/
write16_1(0xa000, 0x0000); /*
*/
read16_1(0xa000); /* returned 0x0000
*/
write16_1(0xa001, 0x0000); /*
*/
read16_1(0xa001); /* returned 0x0000
*/
write16_1(0xa002, 0x00e0); /*
*/
read16_1(0xa002); /* returned 0x00e0
*/
read16_1(0xffe9); /* returned 0x0014
*/
read16_1(0xffe9); /* returned 0x0014
*/
write16_1(0xffe9, 0x0054); /*
*/
read16_1(0xffe9); /* returned 0x0054
*/
write16_1(0xffea, 0x0000); /*
*/
read16_1(0xffea); /* returned 0x0000
*/
read16_1(0xff7e); /* returned 0x0000
*/
read16_1(0xff7e); /* returned 0x0000
*/
write16_1(0xff7e, 0x0000); /*
*/
read16_1(0xff7e); /* returned 0x0000
*/
write16_1(0xffde, 0x0000); /*
*/
read16_1(0xffde); /* returned 0x0000
*/
read16_1(0xffe8); /* returned 0x0015
*/
read16_1(0xffe8); /* returned 0x0015
*/
write16_1(0xffe8, 0x0000); /*
*/
read16_1(0xffe8); /* returned 0x0000
*/
write16_1(0x0076, 0x0002); /*
*/
read16_1(0x0076); /* returned 0x0002
*/
write16_1(0xff91, 0x0005); /*
*/
write16_1(0x0077, 0x0001); /*
*/
read16_1(0x0077); /* returned 0x0001
*/
write16_1(0x006a, 0x0000); /*
*/
read16_1(0x006a); /* returned 0x0000
*/
read16_1(0xff91); /* returned 0xffff
*/
read16_1(0xff91); /* returned 0x0000
*/
read16_1(0xff91); /* returned 0x0000
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
 write16(0x0000, 107, tmp107); /* { zeros followed by 2 }
*/
write16_1(0x006a, 0x0002); /*
*/
write16_1(0x006a, 0x0002); /*
*/
read16_1(0xffeb); /* returned 0x00ff
*/
read16_1(0xffeb); /* returned 0x00ff
*/
read16_1(0xffec); /* returned 0xffff
*/
read16_1(0xffec); /* returned 0xffff
*/
 write16(0xffe0, 16, tmp107); /* { zeros }
*/
write16_1(0xffeb, 0x00ff); /*
*/
read16_1(0xffeb); /* returned 0x00ff
*/
write16_1(0xffec, 0xffff); /*
*/
 read16_1(0xffec); /* returned 0xffff */
}
