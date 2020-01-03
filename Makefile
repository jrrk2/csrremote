CFLAGS = -g -m32
CXXFLAGS = -g -m32
O = devicemanager.o flash.o main.o stopwatch.o usbprogrammer.o basics.o logging.o spi.o pskey.o erase.o download.o disass.o
CsrUsbProg: $O
	$(CXX) $(CXXFLAGS) -o $@ $O -lusb-1.0 -lftdi

