#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>

#include "dataAcq.h"

#ifndef _RPIWRITECSV_H_
#define _RPIWRITECSV_H_

static FILE * outFile;

void timer_handler(int signum);
void handleForceQuit(int signnum);
void outputArray(int * data, int size, FILE *outputFile);
void format_time(char *output);
FILE * initOutputFile();

#endif 
