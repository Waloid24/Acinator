#ifndef GRAPHICDUMP_H
#define GRAPHICDUMP_H

#include "generalInfoAboutTree.h"

#define dumplineTree(text, ...)\
		fprintf (graphicDump, text, ##__VA_ARGS__)

void            showTree                (const nodeTree_t * tree);
void            dotFileHeaderTree       (const nodeTree_t * node, const char * nameGraphDOTfileTree);
void            writeNodeToDotFile      (const nodeTree_t * node, FILE * graphicDump);
void            createFileWithTreeImage (const char * nameDOTfile, unsigned int timesCreatePicture);
static void     createHTMLfileTree      (const char * nameFileDump, unsigned int * timesCreatePicture);

#endif
