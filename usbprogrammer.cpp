#include "usbprogrammer.h"
#include "compat.h"
#include "spifns.h"
#include "spi.h"
#include "logging.h"

#define convertEndianess(A) ((((uint16_t)(A) & 0xff00) >> 8) | \
                             (((uint16_t)(A) & 0x00ff) << 8))

#define arr unsigned char[]

#define __packed __attribute__((__packed__))

UsbProgrammer *UsbProgrammer::programmer = NULL;

UsbProgrammer::UsbProgrammer()
{
  //    log_set_options(LOG_LEVEL_DEBUG);
    spi_set_pinout(SPI_PINOUT_NEXYS4DDR);
    spifns_init();
    spi_set_interface("B");
    spi_open(0);
    spi_set_clock(100);
    IsInitialized();
}

bool UsbProgrammer::ReadBlock(uint16_t addr, int size, uint16_t buffer[])
{
    if(!IsInitialized()) return false;

    if (spifns_sequence_read(addr, size, buffer))
          return false;

    LOG(INFO, "read16(addr=%s, len16=%d)\n", ioregname(addr), size);

    return true;
}

bool UsbProgrammer::Read(uint16_t addr, uint16_t *data)
{
    if(!IsInitialized()) return false;

    if (spifns_sequence_read(addr, 1, data))
          return false;

    LOG(INFO, "read16(addr=%s, rslt=%04x)\n", ioregname(addr), *data);

    return true;
}

bool UsbProgrammer::WriteBlock(uint16_t addr, int size, uint16_t buffer[])
{
    if(!IsInitialized()) return false;

    if (spifns_sequence_write(addr, size, buffer)) return false;

    LOG(INFO, "write16(addr=%s, len16=%d)\n", ioregname(addr), size);

    return true;
}

bool UsbProgrammer::Write(uint16_t addr, uint16_t data)
{
    if(!IsInitialized()) return false;

    if (spifns_sequence_write(addr, 1, &data)) return false;

    LOG(INFO, "write16(addr=%s data=0x%.04x)\n", ioregname(addr), data);

    return true;
}

bool UsbProgrammer::SetTransferSpeed(uint16_t speed)
{
    spi_set_clock(speed);
    LOG(INFO, "spi_set_clock(speed=%d)\n", speed);
    return true;
}

bool UsbProgrammer::IsXAPStopped(void)
{
    bool retval;
    if(!IsInitialized()) retval = false;

    switch(spifns_bluecore_xap_stopped())
      {
      case SPIFNS_XAP_RUNNING: retval = false; break;
      case SPIFNS_XAP_STOPPED: retval = true; break;
      case SPIFNS_XAP_NO_REPLY: retval = false; break;
      default: retval = false; break;
      }
    LOG(INFO, "spifns_bluecore_xap_stopped() returned %d\n", retval);
    return retval;
}

bool UsbProgrammer::IsInitialized(void)
{
    return true;
}

bool UsbProgrammer::SetMode(bool spi)
{
    return true;
}

bool UsbProgrammer::ClearCmdBits()
{
    return true;
}

UsbProgrammer* UsbProgrammer::getProgrammer()
{
    if (programmer == NULL)
        programmer = new UsbProgrammer();

    return programmer;
}
