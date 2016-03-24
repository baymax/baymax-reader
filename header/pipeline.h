#ifndef PIPELINE_H
#define PIPELINE_H

int openLoggerPipe();
void sendToLogger(unsigned char cmd, unsigned char data);

#endif // PIPELINE_H