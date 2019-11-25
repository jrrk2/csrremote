#include "devicemanager.h"
#include "stopwatch.h"
#include "usbprogrammer.h"
#include "bc_def.h"
#include <cstring>

DeviceManager::DeviceManager()
{
    programmer = UsbProgrammer::getProgrammer();
}

bool DeviceManager::IsSupported()
{
    uint16_t id;
    programmer->SetTransferSpeed(1);
    if(!programmer->Read(GBL_CHIP_VERSION, &id)) return false;
    programmer->SetTransferSpeed(16);
    //    XapStop();
    return id == 0x4826;
}

#if 0
bool DeviceManager::XapResetAndGo()
{
    if(!IsSupported()) return false;

    int reset_count = 0;
    StopWatch timer;
    uint16_t tmp;

    programmer->SetTransferSpeed(4);
    programmer->Write(SPI_EMU_CMD, SPI_EMU_CMD_XAP_RUN_B_MASK);
    timer.start();
    while (timer.elapsedmsec() < 16 )
      programmer->Write(SPI_EMU_CMD, SPI_EMU_CMD_XAP_RUN_B_MASK);

    programmer->SetTransferSpeed(4);
    for(int i=0;i<100;i++)
    {
      if ( !programmer->Read(MMU_FLASH_BANK_SELECT, &tmp) )
      {
        if ( tmp >= 0x200 )
          programmer->Write(MMU_FLASH_BANK_SELECT, 0);
        if(++reset_count >= 10)
            break;
      }
    }

    /* write instructions - endless loop and execute it */
    uint32_t xx = 0x540000;
    uint32_t address = 0xa000 + xx - 0x140000;
    programmer->Write(address,   0x0000); //nop
    programmer->Write(address+1, 0x0000); //nop
    programmer->Write(address+2, 0x00E0); //x: bra x
    programmer->Write(XAP_PCH, xx >> 16);
    programmer->Write(XAP_PCL, xx);

    programmer->Read(ANA_CONFIG2, &tmp);
    tmp &= 0xEFFF;
    programmer->Write(ANA_CONFIG2, tmp);
    programmer->Write(GBL_CLK_RATE, 0);
    programmer->Read(XAP_FLAGS, &tmp);
    tmp &= 0x20;
    programmer->Write(XAP_FLAGS, tmp);
    programmer->Write(RSTGEN_WATCHDOG_DELAY, 2);
    programmer->Write(GBL_RST_ENABLES, RST_WATCHDOG_EN_MASK |
                                       RST_FULL_CHIP_RESET);
    programmer->Write(RSTGEN_WATCHDOG_KICK, 1);
    programmer->Write(SPI_EMU_CMD, 0);

    return true;
}
#endif

bool DeviceManager::XapResetAndStop()
{
    if(!IsSupported()) return false;

    int status, elapsed;
    uint16_t tmp;
    StopWatch timer;

    programmer->Write(RSTGEN_WATCHDOG_DELAY, 2);
    programmer->Write(GBL_RST_ENABLES, RST_WATCHDOG_EN_MASK |
                                       RST_FULL_CHIP_RESET);
    programmer->Write(RSTGEN_WATCHDOG_KICK, 1);
    programmer->Write(SPI_EMU_CMD, 0);

    timer.start();
    do
    {
        programmer->Read(GBL_RST_ENABLES, &tmp);
        if ( tmp )
            status = 0;
        else
            ++status;
        elapsed = timer.elapsedmsec();
    }
    while ( status < 3 && elapsed < 10 );

    if(status < 2)
        return false;

    return XapStop();
}

bool DeviceManager::XapGo()
{
    if(!IsSupported()) return false;

    programmer->Write(SPI_EMU_CMD,SPI_EMU_CMD_XAP_RUN_B_MASK);
    programmer->Write(SPI_EMU_CMD,SPI_EMU_CMD_XAP_STEP_MASK |
                                  SPI_EMU_CMD_XAP_RUN_B_MASK);
    programmer->Write(SPI_EMU_CMD,SPI_EMU_CMD_XAP_RUN_B_MASK);
    programmer->Write(SPI_EMU_CMD,SPI_EMU_CMD_XAP_STEP_MASK);

    return true;
}

bool DeviceManager::XapStop()
{
    if(!IsSupported()) return false;

    uint16_t data[SPI_USER_CMD];
    memset(data, 0, sizeof(data));
    
    for (int i = 0; i < 20; ++i )
        programmer->Write(SPI_EMU_CMD, SPI_EMU_CMD_XAP_RUN_B_MASK);

    memset(data, 0, sizeof(data));
    data[SPI_EMU_CMD] = SPI_EMU_CMD_XAP_RUN_B_MASK;

    programmer->WriteBlock(0, SPI_USER_CMD, data);
    programmer->Write(SPI_EMU_CMD, SPI_EMU_CMD_XAP_RUN_B_MASK);
    programmer->Write(SPI_EMU_CMD, SPI_EMU_CMD_XAP_RUN_B_MASK);

    /* reset all register to their default values */
    programmer->WriteBlock(XAP_AH, 16, data);
    programmer->Write(XAP_BRK_REGH, 0xff);
    programmer->Write(XAP_BRK_REGL, 0xffff);

    return true;
}
