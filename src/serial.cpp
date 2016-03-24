#include "serial.h"
#include "cmdparser.h"
#include "errormsg.h"

#include <wiringPi.h>
#include <wiringSerial.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>

int fd;

int openSerial(const char* device) {
if ((fd = serialOpen ("/dev/ttyUSB1", 9600)) < 0)
  {
    fprintf (stderr, "%c%d", SERIAL_OPENING_FAILED, errno);
    return -1 ;
  }    
}

void readSerial() {
  unsigned char cmd;
  unsigned char value;
  unsigned char c;
  for (;;)
  {
    c = serialGetchar(fd);
    //printf("Luoettiin numero %c\n", c);
    if (c == 2) {
        cmd = serialGetchar(fd);
        value = serialGetchar(fd);
        c = serialGetchar(fd);
        if (c == 3) {
            printf("Vastaan otettiin komento %d arvolla %d\n", cmd, value);
            parseCmd(cmd, value);
        }
    }
  }   
}
