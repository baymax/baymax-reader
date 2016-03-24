#include "main.h"
#include "init.h"
#include "serial.h"
#include <stdio.h>

int main() {
	if (initWiringPi() > -1) {
		openLoggerPipe();
		if (openSerial("/dev/ttyUSB0")> -1) {
			readSerial();
		} else {
			printf("Opening serial connection failed");		
		}
	} else return 1;
	return 0;
}