#ifndef PIPELINE_H
#define PIPELINE_H

int openLoggerPipe();
int closeLoggerPipe();
void sendToLogger(unsigned char cmd, unsigned char data);

#endif // PIPELINE_H