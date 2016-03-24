#include "pipeline.h"
#include "errormsg.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

const char *loggerPipePathInput = "/tmp/baymax-logger";

int loggerPipeFd;

int openLoggerPipe() {
    loggerPipeFd = open(loggerPipePathInput, O_WRONLY);
    if (loggerPipeFd < 0) {
        fprintf (stderr, "%c%d", LOGGER_PIPE_OPENING_FAILED, errno);
        return -1;
    } 
}

int closeLoggerPipe() {
    if (close(loggerPipeFd) < 0) {
        fprintf (stderr, "%c%d", LOGGER_PIPE_CLOSING_FAILED, errno);
        return -1;
    }
}

void sendToLogger(unsigned char cmd, unsigned char data) {
    char buff[10];
    snprintf(buff, 10, "%c%c", cmd, data);
    write(loggerPipeFd, buff, sizeof(buff));    
}