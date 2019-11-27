#include <iostream>
#include <string>
#include "usbprogrammer.h"
#include "devicemanager.h"
#include "flash.h"
#include "logging.h"

using namespace std;

void usage(char* prog)
{
    cout << "Usage: " << prog << " <action> <filename> first last loglevel" << endl;
    cout << "Action can be:" << endl;
    cout << " dump - dump firmware from device" << endl;
    cout << " flash - flash new firmware to device" << endl;
}

int main(int argc, char **argv) {
    DeviceManager manager;
    Flash flash;
    int first, last;
    string loglvl = "";
    
    switch(argc) {
    case 0:
    case 1:
    case 2:
        usage(argv[0]);
        return 0;
    case 6:
      loglvl = argv[5];
      if (loglvl == "DEBUG") log_set_options(LOG_LEVEL_DEBUG);
      else if (loglvl == "INFO") log_set_options(LOG_LEVEL_INFO);
      else if (loglvl == "WARN") log_set_options(LOG_LEVEL_WARN);
      else if (loglvl == "ERR") log_set_options(LOG_LEVEL_ERR);
      else if (loglvl == "ALL") log_set_options(LOG_LEVEL_ALL);
      else cout << "loglevel should be DEBUG, INFO, WARN, ERR or ALL" << endl;
      /* drop through deliberately */
    case 5:
      last = atoi(argv[4]);
      first = atoi(argv[3]);
      break;
    case 4:
      last = atoi(argv[3]);
      first = 0;
      break;
    case 3:
      last = 0;
      first = 0;
      break;
    }

    string action = argv[1];
    string stem = argv[2];

    if(!UsbProgrammer::getProgrammer()->IsInitialized()) {
        cout << "Cannot connect to programmer!" << endl;
        return 1;
    }

    if(!manager.IsSupported()) {
        cout << "Device is NOT supported!" << endl;
        return 1;
    }

    if (action == "dump") {
      cout << "first: " << first << " last: " << last << endl;

      if (!flash.dump(stem+".xdv", stem+".xpv", first, last)) {
            cout << "Dumping failed!" << endl;
            return 1;
        }
    } else if (action == "psdump") {
      if (!flash.psdump(stem+".ps")) {
            cout << "Dumping failed!" << endl;
            return 1;
        }
    } else if (action == "pschk") {
      if (!flash.pschk(stem+".xdv")) {
            cout << " PSchk failed!" << endl;
            return 1;
        }
    } else if (action == "psmod") {
      if (!flash.psmod(stem+".xdv")) {
            cout << " PSmod failed!" << endl;
            return 1;
        }
    } else if (action == "flash") {
      if (!flash.downloadall(stem+".xdv", stem+".xpv")) {
            cout << " Download failed!" << endl;
            return 1;
        }
    } else if (action == "erase") {
      if (!flash.chiperase()) {
            cout << " Erase failed!" << endl;
            return 1;
        }
    } else
      {
        cout << "Invalid action!" << endl;
        usage(argv[0]);
        return 0;
      }

    //    manager.XapResetAndGo();

    return 0;
}
