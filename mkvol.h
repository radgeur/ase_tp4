#ifndef _MKVOL_
#define _MKVOL_

#include "mbr.h"

extern void dvol();
extern void mbrvol(unsigned nbblocs, unsigned firstCylinder, unsigned firstSector);

#endif
