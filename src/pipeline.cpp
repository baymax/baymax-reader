#include "pipeline.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

const char *loggerPipePathInput = "/tmp/baymax-logger";

int loggerPipeFd;

int openLoggerPipe() {
    loggerPipeFd = open(loggerPipePathInput, O_WRONLY);
    if (loggerPipeFd < 0) {
        return -1;
    } 
}

void sendToLogger(unsigned char cmd, unsigned char data) {
    char buff[10];
    snprintf(buff, 10, "%c%c", cmd, data);
    write(fd, buff, sizeof(buff));    
}