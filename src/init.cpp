#include "init.h"
#include "errormsg.h"

#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void initWiringPi() {
    if (wiringPiSetup () == -1)
    {
        fprintf (stderr, "%c%d", WIRINGPI_INIT_FAILED, errno);
        return -1;
    }  
    
}