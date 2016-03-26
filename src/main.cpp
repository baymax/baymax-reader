#include "main.h"
#include "init.h"
#include "serial.h"
#include "errormsg.h"
#include "pipeline.h"
//#include "signals.h"
#include <stdio.h>

int main() {
    //printf(getpid());
    fflush(stdout);
    void registerSignals();
    if (initWiringPi() < 0) return 1;
    if (openGtkPipe() < 0) return 1;
	if (openSerial("/dev/ttyUSB1")> -1) {
			    readSerial();
	} else return 1;
	return 0;
}