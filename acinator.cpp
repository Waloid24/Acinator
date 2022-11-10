#include "acinator.h"

#define LONG_LINE "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
#define MAX_SIZE_FEATURE 40
const int noMACROS = 'n';
const int NOMACROS = 'N';
const int yesMACROS = 'y';
const int YESMACROS = 'Y';


void operatingMode (nodeTree_t * tree, FILE * log)
{
	MY_ASSERT (tree == nullptr, "There is no access to tree");
	MY_ASSERT (log == nullptr, "There is no access to logfile");

    printf (LONG_LINE);
    printf ("What mode of operation do you want to choose?\n");
    printf ("1) guess the object;    2) to define an object;\n");
    printf ("3) compare objects;     4) show tree;\n");
    printf ("5) exit with saving;    6) exit without saving\n");
    printf (LONG_LINE);

    int cmd = processCommand ();
	// printf ("cmd = %d\n", cmd);
	if (cmd == 49) guessingMode (&tree, log);
	else if (cmd == 50) printf ("define no\n");
	else if (cmd == 51) printf ("compare no\n");
	else if (cmd == 52) printf ("show\n");
	else if (cmd == 53) {exitWithSaving (tree, log, NO_LAST, 0);
						 fprintf (log, "\n");}
	else 				printf ("no saving\n");
}

int processCommand (void)
{
    int command = getchar ();
    MY_ASSERT (command == EOF, "Command processing error");

	//printf ("command = %c and in ascii \"%d\"\n", command, command);

    while (getchar() != '\n') {;}

    if (command != '1' && command != '2' && command != '3' && command != '4' && command != '5' && command != '6')
    {
        printf ("There is no such mode of operation. Try again.\n");
        command = processCommand ();
    }

	// printf ("$$$$ command = %c and in ascii \"%d\" $$$$\n", command, command);

	return command;
}

void guessingMode (nodeTree_t ** tree, FILE * log)
{
	MY_ASSERT (tree == nullptr, "There is no access to tree");

	if ((*tree)->feature == nullptr)
	{
		printf ("There is not a single element in the tree\n");
		createFirstNode (tree);
	}
	else
	{
		treeTraversal (*tree);
	}

	operatingMode (*tree, log);
}

void treeTraversal (nodeTree_t * currentNode)
{
	MY_ASSERT (currentNode == nullptr, "There is no access to the node");

	printf ("This element is %s?", currentNode->feature);
	nodeTree_t * currentElem = nullptr;
	int answer = processAnswer();
	if (answer == 1)
	{
		currentElem = currentNode->leftDescendant;
	}
	else
	{
		currentElem = currentNode->rightDescendant;
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
}

void addNewNode (nodeTree_t * currentNode)
{
	MY_ASSERT (currentNode == nullptr, "There is no access to node");

	nodeTree_t * newNodeRight = (nodeTree_t *) calloc (1, sizeof (nodeTree_t));
	MY_ASSERT (newNodeRight == nullptr, "Unable to allocate new memory");

	nodeTree_t * newNodeLeft  = (nodeTree_t *) calloc (1, sizeof (nodeTree_t));
	MY_ASSERT (newNodeLeft  == nullptr, "Unable to allocate new memory");

	printf ("Oh, this is so unexpected! Who is it?\n"); //tell me, how does this distinguish your object from the proposed one? This object

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

void createFirstNode (nodeTree_t ** tree)
{
	MY_ASSERT (tree == nullptr, "There is no access to tree");

	*tree = (nodeTree_t *) calloc (1, sizeof (nodeTree_t));
	MY_ASSERT (*tree == nullptr, "Unable to allocate new memory");

	createFirstFeature (*tree);

	if ((*tree)->leftDescendant == nullptr)
	{
		printf ("If this object is %s it is ...\n", (*tree)->feature);
		//printf ("before createNew tree->leftDescendant = %p\n", tree->leftDescendant);
		(*tree)->leftDescendant = createNewNode (*tree, (*tree)->leftDescendant);
		//printf ("after creteNew tree->leftDescendant = %p\n", tree->leftDescendant);
	}
	if ((*tree)->rightDescendant == nullptr)
	{
		printf ("If this object isn't %s it is ...\n", (*tree)->feature);
		(*tree)->rightDescendant = createNewNode ((*tree), (*tree)->rightDescendant);
	}

	printf ("OK! It is a %s?\n", (*tree)->feature);
	printf ("No! It is a %s\n", (*tree)->rightDescendant->feature);
	printf ("Yes! It is a %s\n", (*tree)->leftDescendant->feature);
}

void createFirstFeature (nodeTree_t * tree)
{
	MY_ASSERT (tree == nullptr, "There is no access to tree");

	printf ("Please, enter the feature of the first objects\n");
	tree->feature = getFeature(tree->feature);
	printf ("tree->feature = %s\n", tree->feature);
}

nodeTree_t * createNewNode (nodeTree_t * parentNewNode, nodeTree_t * placeForNewNode)
{
	if (placeForNewNode != nullptr)
		printf ("Attention! You can overwrite old data!\n");

	placeForNewNode = (nodeTree_t *) calloc (1, sizeof(nodeTree_t));
	placeForNewNode->feature = getFeature(placeForNewNode->feature);
	placeForNewNode->parent = parentNewNode;

	printf ("placeForNewNode->feature = %s\n", placeForNewNode->feature);

	return placeForNewNode;
}

elem_t * getFeature (elem_t * feature)
{
	feature = (elem_t *) calloc (MAX_SIZE_FEATURE, sizeof(char));
	scanf ("%s", feature);
	while (getchar() != '\n') {;}
	printf ("%s\n", feature);

	return feature;
}

int my_strcmp (const char * string1, const char * string2)
{
	int i = 0, j = 0;
	for (; string1[i] != '\0' && string2[j] != '\0'; i++, j++)
	{
		while (!isalpha(string1[i]) && string1[i] != '\0')
			i++;
		while (!isalpha(string2[j]) && string2[j] != '\0')
			j++;
		if (tolower(string1[i]) == tolower(string2[j]))
			continue;
		return (tolower(string1[i]) - tolower(string2[j]));
	}

	while (!isalpha(string1[i]) && string1[i] != '\0')
			i++;

	while (!isalpha(string2[j]) && string2[j] != '\0')
			j++;

	return (tolower(string1[i]) - tolower(string2[j]));
}

// void exitWithSaving (nodeTree_t * node, FILE * log)
// {
// 	MY_ASSERT (node == nullptr, "There is no access to the node of the tree");
//
// 	fprintf (log, "(%s ", node->feature);
//
// 	// if (node->leftDescendant) fprintf (log, "node->leftDescendant = %s\n",node->leftDescendant->feature);
// 	// if (node->rightDescendant) fprintf (log, "node->rightDescendant = %s\n", node->rightDescendant->feature);
//
// 	if (node->leftDescendant != nullptr) exitWithSaving (node->leftDescendant, log);
//
// 	if (node->rightDescendant != nullptr) exitWithSaving (node->rightDescendant, log);
// 	fprintf (log, ")");
// 	printf ("ok\n");
// }

void exitWithSaving (nodeTree_t * node, FILE * log, unsigned isLast, unsigned int numTABs)
{
 	MY_ASSERT (node == nullptr, "There is no access to the node of the tree");
	MY_ASSERT (log == nullptr, "There is no access to the logfile");

	printf ("numTABs = %u\n", numTABs);
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
		fprintf (log, "%s\n", node->feature);
}

void printfTAB (unsigned int numTABs, FILE * log)
{
	MY_ASSERT (log == nullptr, "There is no access to the logfile");

	printf ("func PRINTFTAB: numTABs = %u\n", numTABs);
	for (int i = 0; i < numTABs; i++)
	{
		fprintf (log, "  ");
	}
}

int processAnswer (void)
{
	int answer = getchar ();
    MY_ASSERT (answer == EOF, "Command processing error");

	printf ("IN PROCESS ANSWER: answer = %c and in ascii \"%d\"\n", answer, answer);

    while (getchar() != '\n') {;}

	if (answer == noMACROS || answer == NOMACROS) return 0;
	else if (answer == yesMACROS || answer == YESMACROS) return 1;
	else
	{
		printf ("Please, enter letter \"Y\" or \"y\" if you're agree with question, and \"N\" or \"n\" otherwise\n");
		processAnswer();
	}

	return -3;
}

// void createTreeFromFile (nodeTree_t * tree) //void?
// {
// 	MY_ASSERT (tree == nullptr, "There is no access to tree");
//
//
// }
