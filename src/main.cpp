#include "main.h"
#include "init.h"
#include "serial.h"
#include "errormsg.h"
#include "pipeline.h"
//#include "signals.h"
#include <stdio.h>

int main() {
    void registerSignals();
	if (initWiringPi() > -1) {
        if(openLoggerPipe() > -1) {
		    if (openSerial("/dev/ttyUSB0")> -1) {
			    readSerial();
		    } else return SERIAL_OPENING_FAILED;
        } else return LOGGER_PIPE_OPENING_FAILED;
	} else return WIRINGPI_INIT_FAILED;
	return 0;
}