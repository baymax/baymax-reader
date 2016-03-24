#ifndef INIT_H
#define INIT_H

int initWiringPi();

void processSigint(int signum);
void processSigpipe(int signum);
void registerSignals();


#endif // INIT_H