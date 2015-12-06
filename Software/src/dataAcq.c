#include "dataAcq.h"

void spiSetup (int speed)
{
	if ((myFd = wiringPiSPISetup (SPI_CHAN, speed)) < 0)
	{
		fprintf (stderr, "Can't open the SPI bus: %s\n", strerror (errno)) ;
		exit (EXIT_FAILURE) ;
	}
}

void sendMessage(uint32_t message){

	int size ;
	int spiFail ;
	unsigned char myData[4] ;

	spiFail = FALSE ;

	myData[0] = (message & 0xFF000000) >> 24;
	myData[1] = (message & 0x00FF0000) >> 16;
	myData[2] = (message & 0x0000FF00) >> 8;
	myData[3] = (message & 0x000000FF);

	size=4;
	if (wiringPiSPIDataRW (SPI_CHAN, myData, size) == -1)
	{
		printf ("SPI failure: %s\n", strerror (errno)) ;
		spiFail = TRUE ;
	}
}

int rcvMsg(uint32_t* message){

	int spiFail ;
	unsigned char myData[4] ;

	spiFail = FALSE ;

	myData[0] = (*message & 0xFF000000) >> 24;
	myData[1] = (*message & 0x00FF0000) >> 16;
	myData[2] = (*message & 0x0000FF00) >> 8;
	myData[3] = (*message & 0x000000FF);

	if (wiringPiSPIDataRW (SPI_CHAN, myData, PKT_SIZE) == -1)
	{
		printf ("SPI failure: %s\n", strerror (errno)) ;
		spiFail = TRUE ;
	}

  *message = myData[0];
  *message = (*message << 8) | myData[1];
  *message = (*message << 8) | myData[2];
  *message = (*message << 8) | myData[3];

  int retval = rdval(*message);

  return retval;
}

int rdval(uint32_t msg){
  int retval;
  
  unsigned char sign;
  unsigned char lead;
  
  lead = (msg & 0xFF000000) >> 24;
  sign = (msg & 0x00800000) >> 23;
  
  if (sign == 1)
    retval = msg | 0xFF000000;
  else
    retval = msg & 0x00FFFFFF;
  retval -= 100;
  
  return retval;
}

void init_adas_spi()
{
  int speed = 2;
	wiringPiSetup () ;

  pinMode(NRST_PIN, OUTPUT);
  digitalWrite(NRST_PIN, LOW);
  digitalWrite(NRST_PIN, HIGH);
  sleep(1);

	spiSetup (speed * 1000000) ;

  sendMessage(0x85E0004A);
  sendMessage(0x8B000000);
  sendMessage(0x8A1FC60C);
  sendMessage(0x81F800AE);
  sendMessage(0x83002099);
  sendMessage(0x82000015);
}

void rd_frame(int * data)
{
  uint32_t msg;
  sendMessage(0x40000000);
  msg = 0x11000000;
  data[0] = rcvMsg(&msg);
  msg = 0x12000000;
  data[1] = rcvMsg(&msg);
  msg = 0x13000000;
  data[2] = rcvMsg(&msg);
  msg = 0x00000000;
  data[3] = rcvMsg(&msg);
}

void clean_up()
{
	close (myFd) ;
}
