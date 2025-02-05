#ifndef FLASH_H
#define FLASH_H

#include <string>
#include <stdint.h>
#include "usbprogrammer.h"
#include "devicemanager.h"
#include "download.h"
#include "erase.h"

/* This file servers as flash.dll */

using namespace std;

class Flash
{
public:
    Flash();
    bool dump(string xdvfilename, string xpvfilename, int first, int last);
    bool psdump(string psfilename);
    bool pschk(string psfilename);
    bool psmod(string psfilename);
    void readhex(string psfilename, uint16_t buffer[], size_t len, size_t off);
    void cfi();
    bool chiperase();
    void unprotect();
    bool downloadall(string xdvfilename, string xpvfilename, int first, int last);

private:
    uint32_t calc_crc(uint16_t *buffer, uint32_t length);
    bool wait_to_stop(int timeout);
    bool bootprog_load_and_run();
    bool bootprog_run();
    int read_flash_size();
    uint32_t read_flashcrc();
    void setsector(uint32_t sector);
    void dumpblock(uint16_t buffer[], int x);
    void sendblock(uint16_t buffer[], int x);

private:
    UsbProgrammer *programmer;
    DeviceManager manager;
};

#endif // FLASH_H
