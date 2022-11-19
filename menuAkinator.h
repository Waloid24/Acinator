#ifndef MENUAKINATOR_H
#define MENUAKINATOR_H

#include "generalInfoAboutTree.h"

//----------------------------------------functions---------------------------------------------------

void            operatingMode       (nodeTree_t * tree, FILE * log);
void            createFirstNode     (nodeTree_t ** tree);
void            createFirstFeature  (nodeTree_t * tree);
nodeTree_t *    createNewNode       (nodeTree_t * parentNewNode, nodeTree_t * placeForNewNode);
elem_t     *    getFeature          (elem_t     * feature); //in guessing mode.cpp and in akinator.cpp
int             processAnswer       (void); //in guessnig mode.cpp and in akinator.cpp
void            selectingTreeSource (nodeTree_t ** tree);

//------------------------------------------------------------------------------------------------------

#endif
