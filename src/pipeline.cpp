#include "pipeline.h"
#include "errormsg.h"
#include "cmdconst.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

const char *loggerPipePathInput = "/tmp/baymax-logger";
const char *gtkPipePathInput = "/tmp/baymax-gtk";

int loggerPipeFd;
int gtkPipeFd;

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

int openGtkPipe() {
	gtkPipeFd = open(gtkPipePathInput, O_WRONLY);
	if (gtkPipeFd < 0) {
		fprintf (stderr, "%c%d", GTK_PIPE_OPENING_FAILED, errno);
		return -1;
	}
}

int closeGtkPipe() {
	if (close(gtkPipeFd) < 0) {
		fprintf (stderr, "%c%d", GTK_PIPE_CLOSING_FAILED);
		return -1; 
	}    
}

int sendTemp(unsigned char tempId, float temp) {
	char buff[16];
	snprintf(buff, 16, "%c%c%f", TEMPERATURE, tempId, temp);
	writeToPipes(buff);
}

int sendNormalCommand(unsigned char cmd, unsigned char data) {
	char buff[16];
	snprintf(buff, 16, "%c%c", cmd, data); 
	writeToPipes(buff);  
}

int send2Bytes(unsigned char cmd, char *val) {
	char buff[16];
	snprintf(buff, 16, "%c%d", cmd, val); 
	writeToPipes(buff);
}

int writeToPipes(const char* buff) {
	int bytesWrite;
	bytesWrite = write(gtkPipeFd, buff, sizeof(buff));
	if (bytesWrite <= 0) {
		fprintf (stderr, "%c%d", GKT_PIPE_WRITE_FAILED, errno);
		return GKT_PIPE_WRITE_FAILED;
	}
	/*bytesWrite = write(loggerPipeFd, buff, sizeof(buff));
	if (bytesWrite <= 0) {
		fprintf (stderr, "%c%d", LOGGER_PIPE_WRITE_FAILED, errno);
		return LOGGER_PIPE_WRITE_FAILED;
	}    */ 
}

void sendToLogger(unsigned char cmd, unsigned char data) {
	char buff[16];
	snprintf(buff, 16, "%c%c%c", TEMPERATURE, cmd, data);
	write(loggerPipeFd, buff, sizeof(buff));
	//fflush(loggerPipeFd);  
}