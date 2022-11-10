#ifndef ACINATOR_H
#define ACINATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_assert.h"

//---------------------------------variables----------------------------------------------

typedef char elem_t;

struct nodeTree {
    struct nodeTree * parent;
    elem_t * feature;
    struct nodeTree * leftDescendant;
    struct nodeTree * rightDescendant;
};

typedef struct nodeTree nodeTree_t;

enum IS_LAST {
    LAST,
    NO_LAST
};


//--------------------------------functions-------------------------------------------------

void         operatingMode      (nodeTree_t * tree, FILE * log);
int          processCommand     (void);

void         guessingMode       (nodeTree_t ** tree, FILE * log);

void         createFirstNode    (nodeTree_t ** tree);
void         createFirstFeature (nodeTree_t * tree);
nodeTree_t * createNewNode      (nodeTree_t * parentNewNode, nodeTree_t * placeForNewNode);
elem_t     * getFeature         (elem_t     * feature);
void exitWithSaving (nodeTree_t * node, FILE * log, unsigned isLast, unsigned int numTABs);
void printfTAB (unsigned int numTABs, FILE * log);


void         treeTraversal      (nodeTree_t * currentNode);
void         addNewNode         (nodeTree_t * currentNode);
int          processAnswer      (void);

#endif
