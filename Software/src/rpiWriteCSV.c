#include "rpiWriteCSV.h"

//Cheesy headers (Should be in an include file)
void timer_handler(int signum);
void outputArray(int * data, int size, FILE *outputFile);
void format_time(char *output);
FILE * initOutputFile();

//Static output file pointer (so interupt has access to it)
static FILE * outFile;

void timer_handler(int signnum){
	//	printf("In timer %d \n", signnum);
	int frame[4];
  rd_frame(frame);
	outputArray(&frame[1], 1, outFile);
}

//Since we have a file open, make sure it's closed when we quit
void handleForceQuit(int signnum){
	fclose(outFile); 
  clean_up();
	exit(0);
}


//Write an array to the file
//NOTE: outputFile is local, but calls use the static outFile variable
void outputArray(int * data, int size, FILE *outputFile){
	//	printf("in output");
	int i;
	for(i=0;i<(size-1);i++){
		fprintf(outputFile, "%d,", data[i]);
	}
	fprintf(outputFile, "%d", data[i]);
	fprintf(outputFile, "\n");
}

//Initialize the file (open it and add the headers)
FILE * initOutputFile(){
	FILE *outputFile;
	outputFile = fopen("ECG_DATA.csv", "a");
	fprintf(outputFile, "ECG\n");
	return outputFile;
}

