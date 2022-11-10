#include "acinator.h"

#define LONG_LINE "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
const size_t MAX_SIZE_FEATURE = 40;
const size_t MAX_SIZE_NAME_FILE = 20;
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
		printf ("What do you want: to create [n]ew tree or to [u]pload your tree to the program?\n");
		selectionInGuessingMode (tree);

	}
	else
	{
		treeTraversal (*tree);
	}

	operatingMode (*tree, log);
}

void selectionInGuessingMode (nodeTree_t ** tree)
{
	MY_ASSERT (tree == nullptr, "There is no access to the tree");

	int answer = getchar ();
    MY_ASSERT (answer == EOF, "Command processing error");

	printf ("IN PROCESS ANSWER: answer = %c and in ascii \"%d\"\n", answer, answer);

    while (getchar() != '\n') {;}

	if (answer == 'n') createFirstNode (tree);
	else if (answer == 'u') uploadTree (tree);
	else
	{
		printf ("Please, enter letter \"Y\" or \"y\" if you're agree with question, and \"N\" or \"n\" otherwise\n");
		selectionInGuessingMode(tree);
	}
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
		fprintf (log, ".%s\n", node->feature);
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

void uploadTree (nodeTree_t ** tree) //void?
{
	MY_ASSERT (tree == nullptr, "There is no access to tree");

	infoAboutCustomTree_t customTree = {};
	readingFile (&customTree);
	correctBuf (&customTree);

	char ** arrayStrings = selectPlace(customTree.nStrings);
	fillingArrayOfPtrs (customTree.sizeFile, customTree.nStrings, arrayStrings, customTree.bufWithTree);

	for (int i = 0; i < customTree.nStrings; i++)
	{
		printf ("arrayStrings[%d] = %s\n", i, arrayStrings[i]);
	}
	printf ("customTree.nStrings = %zu\n", customTree.nStrings);
	printf ("before calloc\n");
	*tree = (nodeTree_t *) calloc (customTree.nStrings, sizeof (nodeTree_t));
	printf ("after calloc\n");
	MY_ASSERT (*tree == nullptr, "Unable to allocate new memory");

	printf ("before createNode\n");

	createNodeForUploadTree (*tree, customTree, arrayStrings);
	printf ("end of work of func UPLOAD_TREE");
}

void createNodeForUploadTree (nodeTree_t * node, infoAboutCustomTree_t customTree, char ** arrayStrings)
{
	char * ptrToQuestion = nullptr;
	char * ptrToFeature  = nullptr;
	for (size_t i = 0; i < customTree.nStrings; i++, node++)
	{
		if ((ptrToQuestion = strchr(arrayStrings[i], '?')) != nullptr)
		{
			node->feature = readStringFromBuf(ptrToQuestion+1);
			printf ("node->feature = %s\n", node->feature);
			node->leftDescendant = node+1;
			node->rightDescendant = node+2;
			node->leftDescendant->parent = node->rightDescendant->parent = node;
		}
		else
		{
			ptrToFeature = strchr(arrayStrings[i], '.');
			if (ptrToFeature == nullptr)
			{
				printf ("The element cannot be found\n");
				continue;
			}
			node->feature = readStringFromBuf(ptrToFeature+1);
		}
	}
}

void getString (char * nameFile)
{
	MY_ASSERT (nameFile == nullptr, "Error when transferring the file name");

	scanf ("%s", nameFile);
	while (getchar() != '\n') {;} //??????
}

void readingFile (infoAboutCustomTree_t * customTree)
{
	struct stat fileInfo;
	printf ("Please enter the name of the file where your tree is located\n");

	char * nameFile = (char *) calloc (MAX_SIZE_NAME_FILE, sizeof(char));
	MY_ASSERT (nameFile == nullptr, "Unable to allocate new memory");

	getString (nameFile);
	printf ("nameFile = %s\n", nameFile);

	FILE * inputTree = fopen ((const char *) nameFile, "rb");
	MY_ASSERT (inputTree == nullptr, "Unable to open the file with your tree");

	stat ((const char *) nameFile, &fileInfo);

	customTree->sizeFile = fileInfo.st_size;
	printf ("customTree->sizeFile = %zu\n", customTree->sizeFile);

	customTree->bufWithTree = (char *) calloc (customTree->sizeFile + 1, sizeof(char));
	MY_ASSERT (customTree->bufWithTree == nullptr, "Error in allocating memory for saving");
	(customTree->bufWithTree)[customTree->sizeFile] = '\0';

	fread (customTree->bufWithTree, customTree->sizeFile+1, 1, inputTree); //нужен ли +1?

	// FILE * forDump = fopen ("dump.txt", "wb");
	// MY_ASSERT (forDump == nullptr, "Unable to open dump.txt");
	// fwrite (customTree->bufWithTree, customTree->sizeFile+1, 1, forDump);
}

void correctBuf (infoAboutCustomTree_t * const customTree)
{
	for (int i = 0; i < customTree->sizeFile; i++)
	{
		if ((customTree->bufWithTree)[i] == '\n')
		{
			(customTree->bufWithTree)[i] = '\0';
			customTree->nStrings++;
		}
	}
	customTree->nStrings = customTree->nStrings - 1;
}

char ** selectPlace (size_t nStrings)
{
	char ** array = (char **) calloc (nStrings, sizeof (char *));
	MY_ASSERT (array == nullptr, "Unable to allocate new memory\n");
	return array;
}

void fillingArrayOfPtrs (size_t nElems, size_t nStrings, char ** arrayStrings, char * bufElems)
{
	MY_ASSERT (arrayStrings == nullptr, "There is no access to array of strings");
	MY_ASSERT (bufElems == nullptr, "There is no access to buffer of elements");

	arrayStrings[0] = bufElems;
	size_t j = 1;
	for (size_t i = 0; i < nElems && *bufElems != EOF; i++)
	{
		if (*bufElems == '\0')
		{
			arrayStrings[j] = bufElems+1;
			j++;
		}
		bufElems++;
	}

	if (nStrings == j+1)
		printf ("j == nStrings\n");
}

char * readStringFromBuf (char * bufSource)
{
	char * bufDstn = (char *) calloc (MAX_SIZE_FEATURE, sizeof(char));
	MY_ASSERT (bufDstn == nullptr, "Unable to allocate new memory for the buf");
	MY_ASSERT (bufSource == nullptr, "There is no access to buf");

	for (size_t nSym = 0; *bufSource != '\0' && nSym < MAX_SIZE_FEATURE; nSym++, bufSource++, bufDstn++)
	{
		*bufDstn = *bufSource;
	}
	printf ("bufDstn = %s\n", bufDstn);
	printf ("bufSource = %s\n", bufSource);

	return bufDstn;
}
