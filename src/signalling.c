#include "signals.h"
#include "pipeline.h"
#include "errormsg.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

void registerSignals() {
    signal(SIGINT, processSigint);
    signal(SIGPIPE, processSigpipe);
}

void processSigint(int signum) {
    if (closeGtkPipe < 0) {
        exit(EXIT_FAILURE);
    } if (closeLoggerPipe < 0) {
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

void processSigpipe(int signum) {
    fprintf (stderr, "%c%d", LOGGER_PIPE_BROKEN, errno);
    exit(EXIT_FAILURE);
}

