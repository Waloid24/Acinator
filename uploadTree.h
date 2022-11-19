#ifndef UPLOADTREE_H
#define UPLOADTREE_H

#include "generalInfoAboutTree.h"
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

//------------------------------------------------variables------------------------------------------------------------

extern unsigned char IS_UPLOAD;

const size_t MAX_SIZE_NAME_FILE = 20;

typedef struct {
    size_t sizeFile;
    char * bufWithTree;
    size_t nStrings;
} infoAboutCustomTree_t;

typedef struct {
    size_t numString;
    nodeTree_t * nodeReturn;
} returnRecurtion_t;

//----------------------------------------functions---------------------------------------------------

void            uploadTree              (nodeTree_t ** tree);
void            getString               (char * nameFile);
void            readingFile             (infoAboutCustomTree_t * customTree);
void            correctBuf              (infoAboutCustomTree_t * const customTree);
char        ** selectPlace              (size_t nStrings);
void            fillingArrayOfPtrs      (size_t nElems, size_t nStrings, char ** arrayStrings, char * bufElems);
char        * readStringFromBuf         (char * bufSource);

returnRecurtion_t createNodeForUploadTree (nodeTree_t * node, infoAboutCustomTree_t customTree, char ** arrayStrings, returnRecurtion_t recInfo);

//------------------------------------------------------------------------------------------------------

#endif
