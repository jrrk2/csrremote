#ifndef PSKEY_H
#define PSKEY_H

#include <string>
#include <stdint.h>
#include "pskey_defs.h"

using namespace std;

class Pskey
{
public:
    Pskey();
    enum {buffer_size = 0x1000};
    enum {pskey_max = 0x3000};
    static const char *nam(int pskey);
    static void cnv(uint16_t buffer[], int bias, string dumpstr);
    static void detect(uint16_t buffer[], string dumpstr, void (&funcptr)(uint16_t*, int, string));
    static void modify(uint16_t buffer[], int bias, string dumpstr);

 private:
};

#endif
