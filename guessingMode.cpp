#include "guessingMode.h"

void guessingMode (nodeTree_t * currentNode, FILE * log)
{
	MY_ASSERT (currentNode == nullptr, "There is no access to tree");
	MY_ASSERT (log == nullptr, "There is no access to logfile");

	printf ("This element is %s?\n", currentNode->feature);

	nodeTree_t * currentElem = nullptr;

	int answer = processAnswer();
	if (answer == 1)
	{
		currentElem = currentNode->leftDescendant;
		printf ("currentElem(if \"yes\")->feature = %s\n", currentElem->feature);
	}
	else
	{
		currentElem = currentNode->rightDescendant;
		printf ("currentElem(if \"no\")->feature = %s\n", currentElem->feature);
	}
	if (currentElem->leftDescendant == nullptr && currentElem->rightDescendant == nullptr)
		{
			printf ("I think you have guessed %s\n", currentElem->feature);
			printf ("Tell me, honey, is it so (enter [y]es or [n]o)?\n");
			answer = processAnswer();
			if (answer == 1)
			{
				printf ("I knew it! You're defeated, you leather bastard\n");
			}
			else
			{
				addNewNode (currentElem);
			}
		}
	else
	{
		guessingMode (currentElem, log);
	}
}

void addNewNode (nodeTree_t * currentNode)
{
	MY_ASSERT (currentNode == nullptr, "There is no access to node");

	nodeTree_t * newNodeRight = (nodeTree_t *) calloc (1, sizeof (nodeTree_t));
	MY_ASSERT (newNodeRight == nullptr, "Unable to allocate new memory");

	nodeTree_t * newNodeLeft  = (nodeTree_t *) calloc (1, sizeof (nodeTree_t));
	MY_ASSERT (newNodeLeft  == nullptr, "Unable to allocate new memory");

	printf ("Oh, this is so unexpected! Who is it?\n");

	newNodeLeft->feature = getFeature (newNodeLeft->feature);
	newNodeRight->feature = currentNode->feature;
	newNodeLeft->parent = currentNode;
	newNodeRight->parent = currentNode;

	currentNode->leftDescendant = newNodeLeft;
	currentNode->rightDescendant = newNodeRight;

	printf ("What is the difference between a %s and an %s?\n", currentNode->feature, newNodeLeft->feature);
	currentNode->feature = getFeature (currentNode->feature);

	currentNode->rightDescendant = newNodeRight;
	currentNode->leftDescendant  = newNodeLeft;
}

