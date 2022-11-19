#ifndef OBJECTCOMPARISON_H
#define OBJECTCOMPARISON_H

#include <ctype.h>
#include <stdlib.h>
#include "generalInfoAboutTree.h"
#include "objectDefinition.h"

int             compareObjects          (nodeTree_t * node, FILE * log);
nodeTree_t *    findObjectForCompare    (nodeTree_t * node, char * nameObject, nodeTree_t * desiredObject);
void            printСomparison         (nodeTree_t * node, nodeTree_t * firstObject, nodeTree_t * secondObject);
int             myStrcmp                (const char * string1, const char * string2);


#endif
