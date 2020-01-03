#include <iostream>
#include <string>
#include <ctype.h>
#include <stdlib.h>
#include "usbprogrammer.h"
#include "devicemanager.h"
#include "flash.h"
#include "logging.h"
#include "disass.h"

using namespace std;

void usage(char* prog)
{
    cout << "Usage: " << prog << " <action> <filename> first last loglevel" << endl;
    cout << "Action can be:" << endl;
    cout << " dump - dump firmware from device (NO WARRANTY)" << endl;
    cout << " pschk - Check persistent store settings in semi lucid format (NO WARRANTY)" << endl;
    cout << " psdump - As pschk but also dump persistent store settings in machine readable form (NO WARRANTY)" << endl;
    cout << " psmod - Force off-chip HCI mode, virtual machine off, 115200 baud (CAUTION)" << endl;
    cout << " flash - flash new firmware to device (DANGEROUS)" << endl;
    cout << " erase - brick the device (DANGEROUS)" << endl;
    cout << " disass - Display a representation of the programming algorithm (HARMLESS)" << endl;
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

    if (action == "disass") {
      string dis = stem+".dis";
      disass(dis.c_str());
      return 0;
    } else
      {
	char envcheck[99];
	char *ptr = envcheck;
	const char *src = action.c_str();
	while (*src)
	  *ptr++ = toupper((unsigned char)(*src++));
	*ptr = 0;
	
	if (!getenv(envcheck) || !atoi(getenv(envcheck)))
	  {
	    cout << "Some actions are dangerous. Read the documentation and/or source code and confirm below" << endl;
	    cout << "Are you sure you want this action? If so rerun after typing export " << envcheck << "=1" << endl;
	    return 1;
	  }

	if(!UsbProgrammer::getProgrammer()->IsInitialized()) {
	  cout << "Cannot connect to programmer!" << endl;
	  return 1;
	}

	manager.wakeup();
	
	if(!manager.IsSupported()) {
	  cout << "Device is NOT supported!" << endl;
	  return 1;
	}

      }
    
    if (action == "dump") {
      cout << "first: " << first << " last: " << last << endl;

      if (!flash.dump(stem+".xdv", stem+".xpv", first, last)) {
            cout << "Dumping failed!" << endl;
            return 1;
        }
    } else if (action == "psdump") {
      if (!flash.psdump(stem)) {
            cout << "Dumping failed!" << endl;
            return 1;
        }
    } else if (action == "pschk") {
      if (!flash.pschk(stem)) {
            cout << " PSchk failed!" << endl;
            return 1;
        }
    } else if (action == "psmod") {
      if (!flash.psmod(stem)) {
            cout << " PSmod failed!" << endl;
            return 1;
        }
    } else if (action == "flash") {
      if (!flash.downloadall(stem+".xdv", stem+".xpv", first, last)) {
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
