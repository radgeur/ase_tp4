# $Id: Makefile,v 1.2 2009/11/17 10:02:37 marquet Exp $
##############################################################################

ROOTDIR=/home/enseign/ASE

CC	=  gcc -m32 
CFLAGS	=  -Wall -Werror -ansi -pedantic
CFLAGS  += -std=iso9899:1999
CFLAGS  += -g
LIBDIR  =  $(ROOTDIR)/lib
INCDIR  =  $(ROOTDIR)/include
CFLAGS  += -I$(INCDIR)
LIBS    = -lhardware 

###------------------------------
### Main targets 
###------------------------------------------------------------
BINARIES= if_pfile if_nfile if_cfile if_dfile
OBJECTS	= $(addsuffix .o,\
	  inode super mbr drive tools ifile mount)

all: $(BINARIES) $(OBJECTS)


###------------------------------
### Binaries
###------------------------------------------------------------
if_cfile : if_cfile.o $(OBJECTS)
if_nfile : if_nfile.o $(OBJECTS)
if_dfile : if_dfile.o $(OBJECTS)
if_pfile : if_pfile.o $(OBJECTS)

% : %.o
	$(CC) -o $@ $^ -L$(LIBDIR) $(LIBS)

###------------------------------
### #include dependences 
###------------------------------------------------------------
# you may fill these lines with "make depend"
if_cfile.o: if_cfile.c ifile.h inode.h tools.h mount.h ../drive.h ../mbr.h ../super.h
if_dfile.o: if_dfile.c ifile.h inode.h tools.h mount.h ../drive.h ../mbr.h ../super.h
if_nfile.o: if_nfile.c ifile.h inode.h tools.h mount.h ../drive.h ../mbr.h ../super.h
if_pfile.o: if_pfile.c ifile.h inode.h tools.h mount.h ../drive.h ../mbr.h ../super.h
ifile.o: ifile.c inode.h tools.h ifile.h 
mount.o: mount.c config.h tools.h ../mbr.h ../super.h
tools.o: tools.c tools.h
inode.o: inode.c inode.h
super.o: ../super.c ../super.h
mbr.o: ../mbr.c ../mbr.h
drive.o: ../drive.c ../drive.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
%.o: ../%.c
	$(CC) $(CFLAGS) -c $< 
###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o $(BINARIES)
realclean: clean 
depend : 
	$(CC) $(CFLAGS) -MM $(INCDIR) *.c 

