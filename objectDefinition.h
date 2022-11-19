#ifndef OBJECTDEFINITION_H
#define OBJECTDEFINITION_H

#include <stdlib.h>
#include "objectComparison.h"
#include "uploadTree.h" //for getString()
#include "generalInfoAboutTree.h"
#include "unistd.h"

void            definingMode            (nodeTree_t * node, FILE * log);
int             defineOfWord            (nodeTree_t * node);
unsigned int    findObject              (nodeTree_t * node, char * nameObject, unsigned int isObejectFound);

#endif
