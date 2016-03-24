#ifndef PIPE_H
#define PIPE_H

void openLoggerPipe();

void sendToLoggerPipe(unsigned char cmd, unsigned char data);

#endif // PIPE_H