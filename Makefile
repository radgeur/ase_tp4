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
BINARIES= mkhd mknfs dfs
OBJECTS	= $(addsuffix .o,\
	  mkhd mknfs dfs)

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

mknfs.o: mknfs.c
	$(CC) $(CFLAGS) -c mknfs.c $(INCDIR)

mknfs: mknfs.o mkvol.o drive.o mbr.o super.o lib_hardware.o
	$(CC) $(CFLAGS) -o mknfs mknfs.o mkvol.o drive.o mbr.o super.o lib_hardware.o $(LIBS)

mbr.o: mbr.c
	$(CC) $(CFLAGS) -c mbr.c $(INCDIR)

super.o: super.c
	$(CC) $(CFLAGS) -c super.c $(INCDIR)

dfs.o: dfs.c
	$(CC) $(CFLAGS) -c dfs.c $(INCDIR)

dfs: dfs.o mkvol.o drive.o mbr.o super.o lib_hardware.o
	$(CC) $(CFLAGS) -o dfs dfs.o mkvol.o drive.o mbr.o super.o lib_hardware.o $(LIBS)

###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o $(BINARIES)
realclean: clean
	$(RM) vdiskA.bin vdiskB.bin
