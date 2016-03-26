#include "serial.h"
#include "cmdparser.h"
#include "errormsg.h"
#include "cmdconst.h"
#include "pipeline.h"

#include <wiringPi.h>
#include <wiringSerial.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int fd;

int openSerial(const char* device) {
if ((fd = serialOpen (device, 9600)) < 0)
  {
	fprintf (stderr, "%c%d", SERIAL_OPENING_FAILED, errno);
	return -1 ;
  }    
}

void readSerial() {
  unsigned char c;
  for (;;)
  {
	c = serialGetchar(fd);
	if (c == 2) {
		c = serialGetchar(fd);
		if (c == TEMPERATURE) {
			unsigned char tempId;
			char temp[4];
			float tempF;
			tempId = serialGetchar(fd);
			temp[0] = serialGetchar(fd);
			temp[1] = serialGetchar(fd);
			temp[2] = serialGetchar(fd);
			temp[3] = serialGetchar(fd);
			tempF = strtof(temp, NULL);
			printf("%fc\n", tempF);
			fflush(stdout);
			sendTemp(tempId, tempF);
		} else if (c == BATTERY_VOLTAGE_CHANGED) {
			char val[2];
			int voltageVal;
			val[0] = serialGetchar(fd);
			val[1] = serialGetchar(fd);
			voltageVal = strtod(val, NULL);
			printf("Jannite %d\n", voltageVal);
			send2Bytes(c, val);
		} else if (c == BATTERY_CURRENT_CHANGED) {
			char val[2];
			int currentVal;
			val[0] = serialGetchar(fd);
			val[1] = serialGetchar(fd);
			currentVal = strtod(val,NULL);
			printf("Current %d\n", currentVal);
			send2Bytes(c, val);
		} else {
  			unsigned char value;
			value = serialGetchar(fd);
			printf("Komento %d arvolla %d\n", c, value);
			sendNormalCommand(c, value);
		}
		c = serialGetchar(fd);
		if (c == 3) {
		}
	}
  }   
}
