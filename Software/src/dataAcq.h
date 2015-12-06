#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#ifndef _DATAACQ_H_
#define _DATAACQ_H_

#define	TRUE	(1==1)
#define	FALSE	(!TRUE)

#define	SPI_CHAN		0
#define	NUM_TIMES		100
#define	MAX_SIZE		(1024*1024)
#define PKT_SIZE    4

#define NRST_PIN 5

static int myFd ;

void spiSetup (int speed);
void sendMessage(uint32_t message);
int rcvMsg(uint32_t* message);
int rdval(uint32_t msg);
void init_adas_spi();
void rd_frame(int * data);
void clean_up();

#endif 
