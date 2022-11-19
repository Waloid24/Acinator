#include "modeWithSaving.h"

void exitWithSaving (nodeTree_t * node, FILE * log, unsigned int isLast, unsigned int numTABs)
{
 	MY_ASSERT (node == nullptr, "There is no access to the node of the tree");
	MY_ASSERT (log == nullptr, "There is no access to the logfile");

	printfTAB (numTABs, log);
	if (isLast == NO_LAST)
	{
		fprintf (log, "?%s\n", node->feature);
		if (node->leftDescendant->leftDescendant == nullptr && node->leftDescendant->rightDescendant == nullptr)
		{
			exitWithSaving (node->leftDescendant, log, LAST, ++numTABs);
		}
		else
		{
			exitWithSaving (node->leftDescendant, log, NO_LAST, ++numTABs);
		}

		if (node->rightDescendant->leftDescendant == nullptr && node->rightDescendant->rightDescendant == nullptr)
		{
			exitWithSaving (node->rightDescendant, log, LAST, numTABs);
		}
		else
		{
			exitWithSaving (node->rightDescendant, log, NO_LAST, numTABs);
		}
	}
	else
		fprintf (log, ".%s\n", node->feature);
}

void printfTAB (unsigned int numTABs, FILE * log)
{
	MY_ASSERT (log == nullptr, "There is no access to the logfile");

	for (unsigned int i = 0; i < numTABs; i++)
	{
		fprintf (log, "  ");
	}
}
