#include "init.h"
#include "errormsg.h"
#include "pipeline.h"

#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

int initWiringPi() {
    if (wiringPiSetup () == -1)
    {
        fprintf (stderr, "%c%d", WIRINGPI_INIT_FAILED, errno);
        return -1;
    }  
    
}

void registerSignals() {
    signal(SIGINT, processSigint);
    signal(SIGPIPE, processSigpipe);
}

void processSigint(int signum) {
    if (closeLoggerPipe < 0) {
        exit(EXIT_FAILURE);
    }   
}

void processSigpipe(int signum) {
    fprintf (stderr, "%c%d", LOGGER_PIPE_BROKEN, errno);
    exit(EXIT_FAILURE);
}