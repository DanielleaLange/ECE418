CC = g++
LD = g++
CCFLAGS = -c -g 
LDFLAGS = -lm -lpng -lz -L/usr/local/lib

BASE = image.o

all:	lab10-part1 lab10-part2 lab10-bitplanes lab10-part4

lab10-part1:	lab10-part1.o $(BASE)
	$(LD) lab10-part1.o $(BASE) $(LDFLAGS) -o lab10-part1

lab10-part2:	lab10-part2.o $(BASE)
	$(LD) lab10-part2.o $(BASE) $(LDFLAGS) -o lab10-part2

lab10-bitplanes:	lab10-bitplanes.o $(BASE)
	$(LD) lab10-bitplanes.o $(BASE) $(LDFLAGS) -o lab10-bitplanes

lab10-part4:	lab10-part4.o $(BASE)
	$(LD) lab10-part4.o $(BASE) $(LDFLAGS) -o lab10-part4

clean:
	rm  $(BASE) lab10-part1.o lab10-part1 lab10-part2.o lab10-part2 lab10-part4.o lab10-part4 lab10-bitplanes.o lab10-bitplanes

.cc.o:
	$(CC) $(CCFLAGS) $<
