CC=gcc
CFLAGS= -std=gnu99 -Wall -g #-DDEBUG
ODIR=./obj
SRC=./src
BIN=./bin
LIBS= -lwiringPi

INCPY = -I/usr/include/python2.7 -lpython2.7

EXECS= execute_afib_detect

all: $(EXECS)

execute_afib_detect: $(SRC)/rpi_afib_detect_main.c $(SRC)/dataAcq.c $(SRC)/rpiWriteCSV.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) $(INCPY)

.PHONY: clean

clean:
	rm -f *~ core* $(BIN)/$(EXECS)
