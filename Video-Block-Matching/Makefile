CC = g++
LD = g++
CCFLAGS = -c -g 
LDFLAGS = -lm -lpng -lz -L/usr/local/lib
BASE = image.o

all:	lab12

lab12:	lab12.o $(BASE)
	$(LD) lab12.o $(BASE) $(LDFLAGS) -o lab12

clean:
	rm  $(BASE) lab12.o lab12
.cc.o:
	$(CC) $(CCFLAGS) $<
	