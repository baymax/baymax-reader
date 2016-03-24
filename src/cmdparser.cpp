#include "cmdparser.h"
#include "pipeline.h"

void parseCmd(unsigned char cmd, unsigned char data) {
    sendToLogger(cmd, data);
}