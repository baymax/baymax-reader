#ifndef SIGNALLING_H
#define SIGNALLING_H

void processSigint(int signum);
void processSigpipe(int signum);
void registerSignals();

#endif // SIGNALLING_H