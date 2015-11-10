# $Id: Makefile,v 1.2 2004/10/12 09:06:17 marquet Exp $
##############################################################################

ROOTDIR=/home/enseign/ASE

CC	= gcc
CFLAGS	= -Wall -ansi -pedantic 
CFLAGS  += -g -m32
LIBDIR  = $(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    = -L$(LIBDIR) -lhardware 

###------------------------------
### Main targets 
###------------------------------------------------------------
BINARIES= mkhd mkvol
OBJECTS	= $(addsuffix .o,\
	  mkhd)

all: realclean $(BINARIES) $(OBJECTS)


###------------------------------
### Main rules 
###------------------------------------------------------------
mkhd.o: mkhd.c
	$(CC) $(CFLAGS) -c mkhd.c $(INCDIR)

mkhd: mkhd.o drive.o
	$(CC) $(CFLAGS) -o mkhd  mkhd.o drive.o $(LIBS)

drive.o: drive.c
	$(CC) $(CFLAGS) -c drive.c $(INCDIR)

mbr.o: mbr.c
	$(CC) $(CFLAGS) -c mbr.c $(INCDIR)

mkvol.o: mkvol.c
	$(CC) $(CFLAGS) -c mkvol.c $(INCDIR)

mkvol: mkvol.o mbr.o
	$(CC) $(CFLAGS) -o mkvol  mkvol.o mbr.o $(LIBS)
###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o $(BINARIES)
realclean: clean 
	$(RM) vdiskA.bin vdiskB.bin
