# $Id: Makefile,v 1.2 2004/10/12 09:06:17 marquet Exp $
##############################################################################

ROOTDIR=/home/radgeur/Documents/M1/ASE/ase_tp4/libhardware-linux-x86-64-r103

CC	= gcc
CFLAGS	= -Wall -ansi -pedantic 
CFLAGS  += -g
LIBDIR  = $(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    = -L$(LIBDIR) -lhardware 

###------------------------------
### Main targets 
###------------------------------------------------------------
BINARIES= mkhd mkvol
OBJECTS	= $(addsuffix .o,\
	  mkhd mkvol)

all: realclean $(BINARIES) $(OBJECTS)


###------------------------------
### Main rules 
###------------------------------------------------------------
###--------------------------Hardware--------------------------
mkhd.o: mkhd.c
	$(CC) $(CFLAGS) -c mkhd.c $(INCDIR)

mkhd: mkhd.o drive.o lib_hardware.o
	$(CC) $(CFLAGS) -o mkhd  mkhd.o drive.o lib_hardware.o $(LIBS)

drive.o: drive.c
	$(CC) $(CFLAGS) -c drive.c $(INCDIR)

lib_hardware.o: lib_hardware.c
	$(CC) $(CFLAGS) -c lib_hardware.c $(INCDIR)


###--------------------------Volume----------------------------
mkvol.o: mkvol.c
	$(CC) $(CFLAGS) -c mkvol.c $(INCDIR)

mkvol: mkvol.o drive.o mbr.o
	$(CC) $(CFLAGS) -o mkvol  mkvol.o drive.o mbr.o $(LIBS)

mbr.o: mbr.c
	$(CC) $(CFLAGS) -c mbr.c $(INCDIR)

###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o $(BINARIES)
realclean: clean 
	$(RM) vdiskA.bin vdiskB.bin
