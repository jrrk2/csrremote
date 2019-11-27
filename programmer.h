#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include <stdint.h>

class Programmer
{
public:
    static bool Read(uint16_t addr, uint16_t *data);
    static bool Write(uint16_t addr, uint16_t data);
    static ~Programmer() {}

    //pure static
    static bool ReadBlock(uint16_t addr, int size, uint16_t buffer[]) = 0;
    static bool WriteBlock(uint16_t addr, int size, uint16_t buffer[]) = 0;
    static bool SetTransferSpeed(uint16_t speedkhz) = 0;
    static bool IsXAPStopped(void) = 0;
    static bool IsConnected(void) = 0;
};

#endif // PROGRAMMER_H
