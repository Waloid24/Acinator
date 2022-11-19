#include "graphicDump.h"

static unsigned int	NUMBER_GRAPHICAL_TREE_DUMPS = 0;

void showTree (const nodeTree_t * tree)
{
	MY_ASSERT (tree == nullptr, "There is no access to tree");

	const char * nameGraphDOTfileTree = "treeGraphviz.dot";
	const char * nameGraphHTMLfileTree = "treeGraphviz.html";

	dotFileHeaderTree 		(tree, nameGraphDOTfileTree);
	createFileWithTreeImage (nameGraphDOTfileTree, NUMBER_GRAPHICAL_TREE_DUMPS);
	createHTMLfileTree		(nameGraphHTMLfileTree, &NUMBER_GRAPHICAL_TREE_DUMPS);
}

void dotFileHeaderTree (const nodeTree_t * node, const char * nameGraphDOTfileTree)
{
	MY_ASSERT (node == nullptr, "There is no access to tree");

	FILE * graphicDump = fopen (nameGraphDOTfileTree, "w");
	MY_ASSERT (graphicDump == nullptr, "Unable to open the file for graphic dump");

	dumplineTree ("digraph G{\n");
	dumplineTree ("  graph [dpi = 100];\n\n");
	dumplineTree ("  ranksep = 1.5;\n\n");
	dumplineTree ("  splines = ortho;\n\n");

	dumplineTree ("  edge[minlen = 3, penwidth = 3];\n");
    dumplineTree ("  node[shape = rectangle, style = \"rounded, filled\",\n");
    dumplineTree ("              fixedsize = false, height = 1, width = 4,\n");
    dumplineTree ("              penwidth = 4, color =\"#fa9fb5\", fontsize = 30];\n\n");


	writeNodeToDotFile (node, graphicDump);

	dumplineTree ("}\n");

	fflush (graphicDump);
	fclose (graphicDump);
}

void createFileWithTreeImage (const char * nameDOTfile, unsigned int timesCreatePicture)
{
	MY_ASSERT (nameDOTfile == nullptr, "There is no access to name file for graphic dump");

	char buf[100] = {};
    sprintf(buf, "dot -T png -o graph%u.png %s", timesCreatePicture, nameDOTfile);
    system(buf);
}

static void createHTMLfileTree(const char * nameFileDump, unsigned int * timesCreatePicture)
{
	FILE * treeHTML = fopen (nameFileDump, "a");
	MY_ASSERT (treeHTML == nullptr, "Unable to open the file for html-dump");

	char namePicture[60] = {};
    sprintf (namePicture, "graph%u.png", *timesCreatePicture);

	printf ("namePicture = %s\n", namePicture);

	fprintf (treeHTML, "<img src=\"%s\" alt=\"dump №%u\">\n", namePicture, *timesCreatePicture);
	fprintf (treeHTML, "<hr>\n\n");

    (*timesCreatePicture)++;

    fflush (treeHTML);
    fclose (treeHTML);
}

void writeNodeToDotFile (const nodeTree_t * node, FILE * graphicDump)
{
	if (node->leftDescendant == nullptr && node->rightDescendant == nullptr)
	{
		dumplineTree ("\t \"%s\"[style = filled, color = black, fillcolor = orange];\n", node->feature);
	}
	else
	{
		dumplineTree ("\t \"%s\"[style = filled, color = black, fillcolor = orange];\n", node->feature);
	}
	if (node->leftDescendant != nullptr)
	{
		dumplineTree ("\t \"%s\" -> \"%s\" [xlabel=\"yes\"];\n", node->feature, node->leftDescendant->feature);
	}
	if (node->rightDescendant != nullptr)
	{
		dumplineTree ("\t \"%s\" -> \"%s\" [xlabel=\"no\"];\n", node->feature, node->rightDescendant->feature);
	}
	if (node->leftDescendant != nullptr)
	{
		writeNodeToDotFile (node->leftDescendant, graphicDump);
	}
	if (node->rightDescendant != nullptr)
	{
		writeNodeToDotFile (node->rightDescendant, graphicDump);
	}
}
