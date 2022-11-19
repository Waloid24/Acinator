#ifndef MODEWITHSAVING_H
#define MODEWITHSAVING_H

#include "generalInfoAboutTree.h"

void         exitWithSaving     (nodeTree_t * node, FILE * log, unsigned int isLast, unsigned int numTABs);
void         printfTAB          (unsigned int numTABs, FILE * log);

#endif
