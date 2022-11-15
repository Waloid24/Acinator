#ifndef ACINATOR_H
#define ACINATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include "my_assert.h"

//---------------------------------variables----------------------------------------------

typedef char elem_t;

struct nodeTree {
    struct nodeTree * parent;
    elem_t * feature;
    struct nodeTree * leftDescendant;
    struct nodeTree * rightDescendant;
};

typedef struct {
    size_t sizeFile;
    char * bufWithTree;
    size_t nStrings;
} infoAboutCustomTree_t;

typedef struct nodeTree nodeTree_t;

struct returnRecurtion {
    size_t numString;
    nodeTree_t * nodeReturn;
};

enum IS_LAST {
    LAST,
    NO_LAST
};

static unsigned int timesCreatePictureTree = 1;


//--------------------------------functions-------------------------------------------------

void         operatingMode      (nodeTree_t * tree, FILE * log);
int          processCommand     (void);

void         guessingMode       (nodeTree_t ** tree, FILE * log);

void         createFirstNode    (nodeTree_t ** tree);
void         createFirstFeature (nodeTree_t * tree);
nodeTree_t * createNewNode      (nodeTree_t * parentNewNode, nodeTree_t * placeForNewNode);
elem_t     * getFeature         (elem_t     * feature);

void         exitWithSaving     (nodeTree_t * node, FILE * log, unsigned int isLast, unsigned int numTABs);
void         printfTAB          (unsigned int numTABs, FILE * log);


void         treeTraversal      (nodeTree_t * currentNode);
void         addNewNode         (nodeTree_t * currentNode);
int          processAnswer      (void);

void         uploadTree               (nodeTree_t ** tree);
//nodeTree_t * createNodeForUploadTree (nodeTree_t * node, infoAboutCustomTree_t customTree, char ** arrayStrings, int i);
nodeTree_t * createNodeForUploadTree (nodeTree_t * node, infoAboutCustomTree_t customTree, char ** arrayStrings, struct returnRecurtion * recInfo);

void         getString                (char * nameFile);
void         readingFile              (infoAboutCustomTree_t * customTree);
void         correctBuf               (infoAboutCustomTree_t * const customTree);
char      ** selectPlace              (size_t nStrings);
void         fillingArrayOfPtrs       (size_t nElems, size_t nStrings, char ** arrayStrings, char * bufElems);
char       * readStringFromBuf        (char * bufSource);
void         selectionInGuessingMode  (nodeTree_t ** tree);

int          my_strcmp                (const char * string1, const char * string2);
void         definingMode             (nodeTree_t * node, FILE * log);
int          defineOfWord             (nodeTree_t * node);
unsigned int findObject               (nodeTree_t * node, char * nameObject, unsigned int isObejectFound);
int          compareObject            (nodeTree_t * node, FILE * log);
nodeTree_t * findObjectForCompare     (nodeTree_t * node, char * nameObject, nodeTree_t * desiredObject);
void         printСomparison          (nodeTree_t * node, nodeTree_t * firstObject, nodeTree_t * secondObject);

void showTree (const nodeTree_t * tree, FILE * const log);
void graphTree (const nodeTree_t * node, const char * nameGraphDOTfileTree);
void nodeGraph (const nodeTree_t * node, FILE * graphicDump);
void createPictureTree (const char * nameDOTfile, unsigned int timesCreatePicture);
static void createHTMLfileTree(const char * nameFileDump, unsigned int * timesCreatePicture);

#endif
