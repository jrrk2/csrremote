# csrremote
CSR USB-SPI tunneled over UART programmer for Linux.

Based on an original idea described [here](http://jernej87.blogspot.com/2012/10/dumping-bluecore4-firmware-on-linux.html)

Tested with BlueCore4-EXT encapsulated within Digilent PMODBT2 module, running on Nexys4-DDR module.

This can then be used as the mouse and keyboard interface for RISCV Linux running on the Nexys4-DDR and Genesys2 modules.

![screenshot](IMG_1717.png "PMOD-BT2 connection diagram")

This package, when compiled under Ubuntu-16.04/18.04, requires

sudo apt install libusb-1.0-0-dev:i386 libftdi-dev:i386

This is mutually exclusive with the 64-bit version. I don't think anything bad will happen if this software
is compiled for 64-bits, but if you have access to CSR BlueSuite running under WINE, it will require the
32-bit packages. Of course, if you have that software, you don't really need this one.

Action can be:
 dump - dump firmware from device (NO WARRANTY)
 pschk - Check and write persistent store settings in semi lucid format (NO WARRANTY)
 psdump - As pschk but also dump persistent store settings in machine readable (NO WARRANTY)
 psmod - Force off-chip HCI mode, virtual machine off, 115200 baud (CAUTION)
 flash - flash new firmware to device (DANGEROUS)
 erase - erase a.k.a. brick the device (DANGEROUS)
 disass - Display a representation of the programming algorithm (HARMLESS)
