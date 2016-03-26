#ifndef PIPELINE_H
#define PIPELINE_H

int openLoggerPipe();
int closeLoggerPipe();

int openGtkPipe();
int closeGtkPipe();

int sendTemp(unsigned char tempId, float temp);
int sendNormalCommand(unsigned char cmd, unsigned char data);
int send2Bytes(unsigned char cmd, char *val);
int writeToPipes(const char* buff);

void sendToLogger(unsigned char cmd, unsigned char data);

#endif // PIPELINE_H