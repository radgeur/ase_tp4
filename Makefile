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
BINARIES= mkhd mkvol mknfs
OBJECTS	= $(addsuffix .o,\
	  mkhd mkvol mknfs)

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

mkvol: mkvol.o drive.o mbr.o super.o
	$(CC) $(CFLAGS) -o mkvol  mkvol.o drive.o mbr.o super.o $(LIBS)

mknfs.o: mknfs.c
	$(CC) $(CFLAGS) -c mknfs.c $(INCDIR)

mknfs: mknfs.o mkvol.o drive.o mbr.o super.o
	$(CC) $(CFLAGS) -o mknfs mknfs.o mkvol.o drive.o mbr.o super.o $(LIBS)

mbr.o: mbr.c
	$(CC) $(CFLAGS) -c mbr.c $(INCDIR)

super.o: super.c
	$(CC) $(CFLAGS) -c super.c $(INCDIR)

###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o $(BINARIES)
realclean: clean
	$(RM) vdiskA.bin vdiskB.bin
