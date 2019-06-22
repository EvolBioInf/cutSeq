CC=gcc
export VERSION = $(shell bash ../scripts/version.sh) # The single, trailing blank is essential
export DATE    = $(shell bash ../scripts/date.sh) #    The single, trailing blank is essential
CFLAGS         = -DVERSION=\"$(VERSION)\" -DDATE=\"$(DATE)\" -O3 -Wall -Wshadow -pedantic -std=gnu99 -g -I../common/ -L../common/ #-pg

SRCFILES  = cutSeq.c interface.c
OBJFILES  = cutSeq.o interface.o
LIBS      = -lcommon -lm -lbsd
EXECFILE  = cutSeq

.PHONY : all
all : $(EXECFILE)
$(EXECFILE) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(EXECFILE) $(OBJFILES) $(LIBS)
interface.o: interface.h

cutSeq.c: cutSeq.org
	bash ../scripts/org2nw cutSeq.org | notangle -RcutSeq.c > cutSeq.c

clean:
	rm -f *.o *~ cutSeq.c
test:
	bash ../scripts/cutSeq.sh 
