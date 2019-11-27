#ifndef USBPROGRAMMER_H
#define USBPROGRAMMER_H

#include "stdio.h"
#include "stdint.h"

/* This file servers as usbspi.dll programmer interface
 * and partially as pttransport.dll transport layer
 */

class UsbProgrammer
{
public:
    static UsbProgrammer* getProgrammer();
    static bool ReadBlock(uint16_t addr, int size, uint16_t buffer[]);
    static bool Read(uint16_t addr, uint16_t *data);
    static bool WriteBlock(uint16_t addr, int size, uint16_t buffer[]);
    static bool Write(uint16_t addr, uint16_t data);
    bool SetTransferSpeed(uint16_t speed);
    static bool IsXAPStopped(void);
    static bool IsInitialized(void);
    bool SetMode(bool spi);
    bool ClearCmdBits();

private:
    UsbProgrammer();

private:
    static UsbProgrammer *programmer;
    bool progInit;
};

#endif // USBPROGRAMMER_H
