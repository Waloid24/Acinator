#include "acinator.h"

#define LONG_LINE "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
#define dumplineTree(text, ...)\
		fprintf (graphicDump, text, ##__VA_ARGS__)

const size_t MAX_SIZE_FEATURE = 40;
const size_t MAX_SIZE_NAME_FILE = 20;
const int noMACROS = 'n';
const int NOMACROS = 'N';
const int yesMACROS = 'y';
const int YESMACROS = 'Y';  //добавить частицы не в определение объекта: не серый
//файл , куда будет загружаться дерево (пользователь может сам выбрать имя)


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

	printf ("in operatingMode (ptr) tree = %p\n", tree);

    int cmd = processCommand ();
	// printf ("cmd = %d\n", cmd);
	if (cmd == 49) guessingMode (&tree, log);
	else if (cmd == 50) definingMode (tree, log);
	else if (cmd == 51) {
						 if (tree->feature == nullptr)
						 {
							 printf ("There is not a single element in the tree\n");
							 printf ("What do you want: to create [n]ew tree or to [u]pload your tree to the program?\n");
							 selectionInGuessingMode (&tree);
						 }
						 compareObject (tree, log);
						 exitWithSaving (tree, log, NO_LAST, 0);
						 operatingMode (tree, log);
						}
	else if (cmd == 52) {
						 if (tree->feature == nullptr)
						 {
							 printf ("There is not a single element in the tree\n");
							 printf ("What do you want: to create [n]ew tree or to [u]pload your tree to the program?\n");
							 selectionInGuessingMode (&tree);
						 }
						 showTree (tree, log);
						 operatingMode (tree, log);
						}
	else if (cmd == 53) {
						 exitWithSaving (tree, log, NO_LAST, 0);
						 fprintf (log, "\n");
						}
	else 				printf ("You shouldn't be doing this to me\n");
}

void showTree (const nodeTree_t * tree, FILE * const log)
{
	MY_ASSERT (tree == nullptr, "There is no access to tree");
	MY_ASSERT (log == nullptr, "There is no access to logfile");

	const char * nameGraphDOTfileTree = "treeGraphviz.dot";
	const char * nameGraphHTMLfileTree = "treeGraphviz.html";

	graphTree (tree, nameGraphDOTfileTree);
	createPictureTree (nameGraphDOTfileTree, timesCreatePictureTree);
	createHTMLfileTree (nameGraphHTMLfileTree, &timesCreatePictureTree);
}

void graphTree (const nodeTree_t * node, const char * nameGraphDOTfileTree)
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
    dumplineTree ("              fixedsize = true, height = 1, width = 2,\n");
    dumplineTree ("              penwidth = 4, color =\"#fa9fb5\", fontsize = 30];\n\n");


	nodeGraph (node, graphicDump);

	dumplineTree ("}\n");

	fflush (graphicDump);
	fclose (graphicDump);
}

void createPictureTree (const char * nameDOTfile, unsigned int timesCreatePicture)
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

	// printf ("namePicture = %s\n", namePicture);

	fprintf (treeHTML, "<pre>\n");
	fprintf (treeHTML, "<img src=\"%s\" alt=\"dump №%u\"/>\n", namePicture, *timesCreatePicture);
	fprintf (treeHTML, "</pre>\n");

    (*timesCreatePicture)++;

    fflush (treeHTML);
    fclose (treeHTML);
}

void nodeGraph (const nodeTree_t * node, FILE * graphicDump)
{
	if (node->leftDescendant == nullptr && node->rightDescendant == nullptr)
		dumplineTree ("\t \"%s\"[style = filled, color = black, fillcolor = orange];\n", node->feature);

	else
		dumplineTree ("\t \"%s\"[style = filled, color = black, fillcolor = orange];\n", node->feature);

	if (node->leftDescendant != nullptr)
		dumplineTree ("\t \"%s\" -> \"%s\" [label=\"yes\"];\n", node->feature, node->leftDescendant->feature);

	if (node->rightDescendant != nullptr)
		dumplineTree ("\t \"%s\" -> \"%s\" [label=\"no\"];\n", node->feature, node->rightDescendant->feature);

	if (node->leftDescendant != nullptr) nodeGraph (node->leftDescendant, graphicDump);

	if (node->rightDescendant != nullptr) nodeGraph (node->rightDescendant, graphicDump);
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

int compareObject (nodeTree_t * node, FILE * log)
{
	MY_ASSERT (node == nullptr, "There is no access to tree");
	MY_ASSERT (log == nullptr, "There is no access to logfile");

	printf ("Please, enter the name of the first object which you want to find\n");
	char * nameObjectFirst = (char *) calloc (MAX_SIZE_FEATURE, sizeof (char));
	MY_ASSERT (nameObjectFirst == nullptr, "Unable to allocate new memory");
	getString (nameObjectFirst);

	printf ("Please, enter the name of the second object which you want to find\n");
	char * nameObjectSecond = (char *) calloc (MAX_SIZE_FEATURE, sizeof (char));
	MY_ASSERT (nameObjectSecond == nullptr, "Unable to allocate new memory");
	getString (nameObjectSecond);

	nodeTree_t * firstObject = findObjectForCompare(node, nameObjectFirst, nullptr);
	if (firstObject == nullptr)
	{
		printf ("This element was not found in the tree.\n");
		return 1;
	}

	nodeTree_t * secondObject = findObjectForCompare(node, nameObjectSecond, nullptr);
	if (secondObject == nullptr)
	{
		printf ("This element was not found in the tree.\n");
		return 1;
	}

	printf ("in findObjectForCompare: firstObject = %s\n", firstObject->feature);
	printf ("in findObjectForCompare: secondObject = %s\n", secondObject->feature);

	if (my_strcmp(firstObject->feature, secondObject->feature) == 0)
	{
		printf ("You enter two you have entered two identical objects. Here is the definition: \n");
		findObject (node, firstObject->feature, 0);
	}

	printСomparison(node, firstObject, secondObject);

	return 2;
}

void printСomparison (nodeTree_t * node, nodeTree_t * firstObject, nodeTree_t * secondObject)
{
	MY_ASSERT (firstObject == nullptr, "There is no access to first object");
	MY_ASSERT (firstObject == nullptr, "There is no access to second object");

	if (firstObject->parent == nullptr)
	{
		printf ("First object is %s\n", node->feature);
	}
	else if (secondObject->parent == nullptr)
	{
		printf ("Second obfect is %s\n", node->feature);
	}

	if (firstObject->parent == nullptr)
	{
		findObject (node, secondObject->feature, 0);
	}
	else if (secondObject->parent == nullptr)
	{
		findObject (node, firstObject->feature, 0);
	}

	if (firstObject->parent != nullptr && secondObject->parent != nullptr)
	{
		// printf ("Difference between these objects: \n");

		nodeTree_t * fstObj = firstObject;
		nodeTree_t * scndObj = secondObject;

		printf ("The first object, unlike the second, ");
		while (my_strcmp(fstObj->feature, scndObj->feature) != 0)
		{
			if (fstObj->parent != nullptr)
			{
				if (my_strcmp(fstObj->parent->rightDescendant->feature, fstObj->feature) == 0)
					printf ("not ");

				printf ("%s, ", fstObj->parent->feature);
			}
			if (fstObj->parent != nullptr)
			{
				fstObj = fstObj->parent;
			}
			if (scndObj->parent != nullptr)
			{
				scndObj = scndObj->parent;
			}
		}

		fstObj = firstObject;
		scndObj = secondObject;

		printf ("\nBut the second object ");
		while (my_strcmp(fstObj->feature, scndObj->feature) != 0)
		{
			if (scndObj->parent != nullptr)
			{
				if (my_strcmp(scndObj->parent->rightDescendant->feature, scndObj->feature) == 0)
				printf ("not ");
			}
			printf ("%s, ", scndObj->parent->feature);
			if (fstObj->parent != nullptr)
			{
				fstObj = fstObj->parent;
			}
			if (scndObj->parent != nullptr)
			{
				scndObj = scndObj->parent;
			}
		}

		printf ("\nAnd what they have in common is that they are both ");
		while (fstObj->parent != nullptr)
		{
			if (fstObj->parent == nullptr)
				printf ("%s.", fstObj->feature);
			else
				printf ("%s, ", fstObj->feature);
			fstObj = fstObj->parent;
		}
	}

	printf ("EEENNNDDD\n");

}

nodeTree_t * findObjectForCompare (nodeTree_t * node, char * nameObject, nodeTree_t * desiredObject)
{
	MY_ASSERT (node == nullptr, "There is no access to tree");
	MY_ASSERT (nameObject == nullptr, "There is no access to object");

	// printf ("----in findObjectForCompare: nameObject = %s\n", nameObject);
	// printf ("----in findObjectForCompare: node->feature = %s\n", node->feature);
	// printf ("----in findObjectForCompare: desiredObject = %p\n", desiredObject);

	if (my_strcmp (node->feature, nameObject) != 0)
	{
		if (node->leftDescendant != nullptr && desiredObject == nullptr)
		{
			desiredObject = findObjectForCompare (node->leftDescendant, nameObject, desiredObject);
			// printf ("after leftDescendant: desiredObject = %p\n", desiredObject);
		}
		if (node->rightDescendant != nullptr && desiredObject == nullptr)
		{
			desiredObject = findObjectForCompare (node->rightDescendant, nameObject, desiredObject);
			// printf ("after rightDescendant: desiredObject = %p\n", desiredObject);

		}
	}
	else
	{
		// printf ("YEES: desiredObject = %p\n", node);
		return node;
	}
	// printf ("before exit from findObjectForCompare: desiredObject = %p\n", desiredObject);
	return desiredObject;
}

void definingMode (nodeTree_t * node, FILE * log)
{
	MY_ASSERT (node == nullptr, "There is no access to tree");
	MY_ASSERT (log == nullptr, "There is no access to logfile");

	printf ("Please, enter the name of the object\n");
	char * nameObject = (char *) calloc (MAX_SIZE_FEATURE, sizeof (char));
	MY_ASSERT (nameObject == nullptr, "Unable to allocate new memory");
	getString (nameObject);
	//printf ("node = %p\n", node);
	unsigned char isFound = findObject (node, nameObject, 0); //0 заменить на enum с noFound

	printf ("\n");

	if (isFound == 0)
	{
		printf ("This element was not found in the tree.\n");
	}

	operatingMode (node, log);
}

unsigned int findObject (nodeTree_t * node, char * nameObject, unsigned int isObejectFound) //возможно стоит каждый раз создавать переменную внутри фукнции
{
	//printf ("----in anotherObject: node = %p\n", node);
	//printf ("----in anotherObject: nameObject = %s\n", nameObject);

	MY_ASSERT (node == nullptr, "There is no access to tree");
	MY_ASSERT (nameObject == nullptr, "There is no access to object");
	//printf ("----in anotherObject: node->feature = %s\n", node->feature);
	// printf ("----isObejectFound = %u\n", isObejectFound);

	// if (node->parent != nullptr)
	// {
	// 	printf ("%s->parent = %s\n", node->feature, node->parent->feature);
	// }

	if (my_strcmp (node->feature, nameObject) != 0)
	{
		if (node->leftDescendant != nullptr && isObejectFound != 1)
		{
			isObejectFound = findObject (node->leftDescendant, nameObject, isObejectFound);
		}
		if (node->rightDescendant != nullptr && isObejectFound != 1)
		{
			isObejectFound = findObject (node->rightDescendant, nameObject, isObejectFound);
		}
	}
	else
	{
		printf ("^^^^Definition of %s: ", nameObject);
		return defineOfWord (node);
	}
	return isObejectFound;
}

int defineOfWord (nodeTree_t * node)
{
	if (node->parent != nullptr)
	{
		if (my_strcmp(node->parent->rightDescendant->feature, node->feature) == 0)
					printf ("not ");
		printf ("%s, ", node->parent->feature);
		defineOfWord (node->parent);
	}
	return 1;
}

void guessingMode (nodeTree_t ** tree, FILE * log)
{
	MY_ASSERT (tree == nullptr, "There is no access to tree");
	MY_ASSERT (log == nullptr, "There is no access to logfile");

	printf ("guessingMode (ptr ptr) tree = %p\n", tree);

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

	//printf ("in selectionInGuessingMode (ptr ptr) tree = %p\n", tree);

	int answer = getchar ();
    MY_ASSERT (answer == EOF, "Command processing error");

	// printf ("IN PROCESS ANSWER: answer = %c and in ascii \"%d\"\n", answer, answer);

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
		treeTraversal (currentElem);
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

void exitWithSaving (nodeTree_t * node, FILE * log, unsigned int isLast, unsigned int numTABs)
{
 	MY_ASSERT (node == nullptr, "There is no access to the node of the tree");
	MY_ASSERT (log == nullptr, "There is no access to the logfile");

	// printf ("numTABs = %u\n", numTABs);
	printfTAB (numTABs, log);
	if (isLast == NO_LAST)
	{
		fprintf (log, "?%s\n", node->feature);
		printf ("\nKKKKEEEEEEEEEEEKKKKK\n\n");
		if (node->leftDescendant->leftDescendant == nullptr && node->leftDescendant->rightDescendant == nullptr)
		{
			// printf ("node->leftDescendant/LAST = %p\n", node->leftDescendant);
			printf ("node->leftDescendant->feature/LAST = %s\n", node->leftDescendant->feature);
			exitWithSaving (node->leftDescendant, log, LAST, ++numTABs);
		}
		else
		{
			// printf ("node->leftDescendant/NO_LAST = %p\n", node->leftDescendant);
			printf ("node->leftDescendant->feature/NO_LAST = %s\n", node->leftDescendant->feature);
			exitWithSaving (node->leftDescendant, log, NO_LAST, ++numTABs);
		}

		if (node->rightDescendant->leftDescendant == nullptr && node->rightDescendant->rightDescendant == nullptr)
		{
			// printf ("node->rightDescendant/LAST = %p\n", node->rightDescendant);
			printf ("node->rightDescendant->feature/LAST = %s\n", node->rightDescendant->feature);
			exitWithSaving (node->rightDescendant, log, LAST, numTABs);
		}
		else
		{
			// printf ("node->rightDescendant/NO_LAST = %p\n", node->rightDescendant);
			printf ("node->rightDescendant->feature/NO_LAST = %s\n", node->rightDescendant->feature);
			exitWithSaving (node->rightDescendant, log, NO_LAST, numTABs);
		}
	}
	else
		fprintf (log, ".%s\n", node->feature);


}

void printfTAB (unsigned int numTABs, FILE * log)
{
	MY_ASSERT (log == nullptr, "There is no access to the logfile");

	// printf ("func PRINTFTAB: numTABs = %u\n", numTABs);
	for (unsigned int i = 0; i < numTABs; i++)
	{
		fprintf (log, "  ");
	}
}

int processAnswer (void)
{
	int answer = getchar ();
    MY_ASSERT (answer == EOF, "Command processing error");

	// printf ("IN PROCESS ANSWER: answer = %c and in ascii \"%d\"\n", answer, answer);

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

void uploadTree (nodeTree_t ** tree)
{
	MY_ASSERT (tree == nullptr, "There is no access to tree");

	// printf ("in uploadTree (ptr ptr) tree = %p\n", tree);
	// printf ("in uploadTree (ptr) *tree = %p\n", *tree);

	infoAboutCustomTree_t customTree = {};
	readingFile (&customTree);

	correctBuf (&customTree);

	char ** arrayStrings = selectPlace(customTree.nStrings);

	//ok

	// printf ("customTree.sizeFile = %zu\n", customTree.sizeFile);
	printf ("customTree.nStrings = %zu\n", customTree.nStrings);

	fillingArrayOfPtrs (customTree.sizeFile, customTree.nStrings, arrayStrings, customTree.bufWithTree);

	// no ok

	// nodeTree_t * camoc = (nodeTree_t *) calloc (1, sizeof (nodeTree_t));
	// printf ("in uploadTree (ptr) camoc = %p\n", camoc);

	// for (size_t i = 0; i < customTree.nStrings; i++)
	// {
	// 	printf ("arrayStrings[%zu] = %s\n", i, arrayStrings[i]);
	// }

// 	printf ("customTree.nStrings = %zu\n", customTree.nStrings);
// 	printf ("before calloc\n");
// 	printf ("sizeof (nodeTree_t) = %zu\n", sizeof (nodeTree_t));
//
// 	printf ("before calloc *tree = %p\n", *tree);

	*tree = (nodeTree_t *) calloc (customTree.nStrings, sizeof (nodeTree_t));
	// printf ("after calloc\n");
	MY_ASSERT (*tree == nullptr, "Unable to allocate new memory");

// 	printf ("after calloc *tree = %p\n", *tree);
//
// 	printf ("before createNode\n");

	struct returnRecurtion recInfo = {};
	createNodeForUploadTree (*tree, customTree, arrayStrings, recInfo);

	// FILE * fileDumpUploadTree = fopen ("dump.txt", "a");
	// exitWithSaving (*tree, fileDumpUploadTree, NO_LAST, 0);

	// printf ("end of work of func UPLOAD_TREE\n\n");
}

struct returnRecurtion createNodeForUploadTree (nodeTree_t * node, infoAboutCustomTree_t customTree, char ** arrayStrings, struct returnRecurtion recInfo)
{
	char * ptrToQuestion = nullptr;
	char * ptrToFeature  = nullptr;

	printf ("\nThere is dump of information about custom tree:\n");
	printf ("**nStrings = %zu\n", customTree.nStrings);
	printf ("**sizeFile = %zu\n\n", customTree.sizeFile);

	if ((ptrToQuestion = strchr(arrayStrings[recInfo.numString], '?')) != nullptr)
	{
		node->feature = readStringFromBuf(ptrToQuestion+1);
		node->leftDescendant = node+1;
		node->leftDescendant->parent = node;
		printf ("node->feature (struct:%zu) = %s\n", recInfo.numString, node->feature);

		char * nameLeftDescendant = nullptr;
		char * nameRightDescendant = nullptr;

		if ((nameLeftDescendant = strchr(arrayStrings[(recInfo.numString)+1], '?')) != nullptr)
		{
			node->leftDescendant->feature = nameLeftDescendant+1;
			struct returnRecurtion forSaveIngoThisNode = recInfo;
			recInfo.numString = recInfo.numString+1;
			recInfo = createNodeForUploadTree (node+1, customTree, arrayStrings, recInfo);
			if (recInfo.nodeReturn == nullptr)
			{
				printf ("recInfo.nodeReturn (%zu) = nullptr\n", recInfo.numString);
			}
			else
			{
				printf ("recInfo.nodeReturn->feature (%zu) = %s\n", recInfo.numString, (recInfo.nodeReturn)->feature);
				printf ("and now we are in node->feature = %s\n", node->feature);
			}
			node->rightDescendant = recInfo.nodeReturn + 3;
			node->rightDescendant->parent = node;
			recInfo.numString = recInfo.numString+3;
			struct returnRecurtion nodeIfSecondQuestion = createNodeForUploadTree (node->rightDescendant, customTree, arrayStrings, recInfo);
		}


		else if ((nameRightDescendant = strchr(arrayStrings[(recInfo.numString)+2], '?')) != nullptr)
		{
			char * nameLeftNode = strchr(arrayStrings[(recInfo.numString)+1], '.');
			node->leftDescendant->feature = readStringFromBuf(nameLeftNode+1);

			node->rightDescendant = node+2;
			node->rightDescendant->feature = nameRightDescendant+1;
			node->rightDescendant->parent = node;
			recInfo.numString = recInfo.numString+2;
			struct returnRecurtion nodeIfSecondQuestion = createNodeForUploadTree (node+2, customTree, arrayStrings, recInfo);
		}
		else
		{
			node->rightDescendant = node+2;
			node->rightDescendant->parent = node;

			char * nameLeftFeature = strchr (arrayStrings[(recInfo.numString)+1], '.');
			char * nameRightFeature = strchr (arrayStrings[(recInfo.numString)+2], '.');

			node->leftDescendant->feature = readStringFromBuf(nameLeftFeature+1);
			node->rightDescendant->feature = readStringFromBuf(nameRightFeature+1);

			recInfo.nodeReturn = node;

			return (recInfo);
		}
	}
	else if ((ptrToFeature = strchr(arrayStrings[(recInfo.numString)+1], '.')) != nullptr)
	{
		node->feature = readStringFromBuf (ptrToFeature+1);
		recInfo.nodeReturn = node;
		return (recInfo);
	}
	else
	{
		printf ("\nERROR\n");
	}
}



void getString (char * nameFile)
{
	MY_ASSERT (nameFile == nullptr, "Error when transferring the file name");

	scanf ("%s", nameFile);
	while (getchar() != '\n') {;}
}

void readingFile (infoAboutCustomTree_t * customTree)
{
	struct stat fileInfo = {};
	printf ("Please enter the name of the file where your tree is located\n");

	char * nameFile = (char *) calloc (MAX_SIZE_NAME_FILE, sizeof(char));
	MY_ASSERT (nameFile == nullptr, "Unable to allocate new memory");

	getString (nameFile);
	// printf ("nameFile = %s\n", nameFile);

	FILE * inputTree = fopen ((const char *) nameFile, "rb");
	MY_ASSERT (inputTree == nullptr, "Unable to open the file with your tree");

	stat ((const char *) nameFile, &fileInfo);

	customTree->sizeFile = fileInfo.st_size;
	// printf ("customTree->sizeFile = %zu\n", customTree->sizeFile);

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
	for (size_t i = 0; i < customTree->sizeFile; i++)
	{
		if ((customTree->bufWithTree)[i] == '\n')
		{
			(customTree->bufWithTree)[i] = '\0';
			customTree->nStrings++;
		}
	}
	customTree->nStrings = customTree->nStrings;
}

char ** selectPlace (size_t nStrings)
{
	char ** array = (char **) calloc (nStrings, sizeof (char *));
	MY_ASSERT (array == nullptr, "Unable to allocate new memory\n");
	// printf ("in selectPlace: array = %p\n", array);
	return array;
}

void fillingArrayOfPtrs (size_t nElems, size_t nStrings, char ** arrayStrings, char * bufElems)
{
	MY_ASSERT (arrayStrings == nullptr, "There is no access to array of strings");
	MY_ASSERT (bufElems == nullptr, "There is no access to buffer of elements");

	arrayStrings[0] = bufElems;
	// printf ("arrayStrings[0] = %s\n", arrayStrings[0]);
	size_t j = 1;

	// printf ("sizeof (nodeTree_t) = %zu\n", sizeof (nodeTree_t));

	// nodeTree_t * camoc = (nodeTree_t *) calloc (1, sizeof (nodeTree_t));
	// printf ("AAAAAAAAAAAAAA in fillingArrayOfPtrs: camoc = %p\n", camoc);

	for (size_t i = 0; i < nElems && *bufElems != EOF && j < nStrings; i++) //здесь была ошибка
	{
		if (*bufElems == '\0')
		{
			arrayStrings[j] = bufElems+1;
			// printf ("arrayStrings[%zu] = %s\n", j, arrayStrings[j]);
			j++;
		}
		bufElems++;
	}

	// nodeTree_t * cam = (nodeTree_t *) calloc (1, sizeof (nodeTree_t));
	// printf ("AAAAAAAAAAAAAA in fillingArrayOfPtrs: cam = %p, cam++ = %p, cam+2 = %p\n", cam, cam+1, cam+2);

	if (nStrings == j+1)
		printf ("nStrings = %zu\n", nStrings);
}

char * readStringFromBuf (char * bufSource)
{
	char * bufDstn = (char *) calloc (MAX_SIZE_FEATURE, sizeof(char));
	MY_ASSERT (bufDstn == nullptr, "Unable to allocate new memory for the buf");
	MY_ASSERT (bufSource == nullptr, "There is no access to buf");

	// printf ("in readStringFromBuf: %c\n", *bufSource);
	// printf ("before for bufSource = %s\n", bufSource);

	bufDstn = strncpy (bufDstn, bufSource, MAX_SIZE_FEATURE);

	// printf ("bufDstn = %s\n", bufDstn);
	// printf ("bufSource = %s\n", bufSource);

	return bufDstn;
}


