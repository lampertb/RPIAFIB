# include <Python.h>
# include "rpiWriteCSV.h"
# include "dataAcq.h"

int main(int argc, char ** argv){

	//Initialize the output file
	FILE * outputFile = initOutputFile();
	outFile=outputFile;

  //Initialize adas1000
  init_adas_spi();

	//Create a timer
	struct itimerval timer={0};
	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 4000;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 4000;
	signal(SIGALRM, &timer_handler);
	setitimer(ITIMER_REAL, &timer, NULL);

	//Handle a force quit gracefully
	signal(SIGINT, handleForceQuit);

  struct timeval tv0;
  struct timezone tz;

  // FIXME: add tz0 to compare time zone
  struct timeval tv;

  gettimeofday(&tv0, &tz);
  
  tv = tv0; 

  while(tv.tv_sec < tv0.tv_sec + 150){
    gettimeofday(&tv, &tz);
  }

  fclose(outFile);
  clean_up();
  
  FILE * fp;

  Py_Initialize();

  fp = fopen("ECG_DATA.csv", "r");
  PyRun_SimpleFile(fp, argv[1]);

  Py_Finalize();

  return 0;
}
