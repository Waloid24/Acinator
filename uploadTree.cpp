#include "uploadTree.h"

void uploadTree (nodeTree_t ** tree)
{
	MY_ASSERT (tree == nullptr, "There is no access to tree");
	IS_UPLOAD = 1;

	infoAboutCustomTree_t customTree = {};
	readingFile (&customTree);

	correctBuf (&customTree);

	char ** arrayStrings = selectPlace(customTree.nStrings);

	fillingArrayOfPtrs (customTree.sizeFile, customTree.nStrings, arrayStrings, customTree.bufWithTree);

	*tree = (nodeTree_t *) calloc (customTree.nStrings, sizeof (nodeTree_t));
	printf ("in uploadTree: *tree = %p\n", *tree);
	MY_ASSERT (*tree == nullptr, "Unable to allocate new memory");

	returnRecurtion_t recInfo = {};
	createNodeForUploadTree (*tree, customTree, arrayStrings, recInfo);
}

returnRecurtion_t createNodeForUploadTree (nodeTree_t * node, infoAboutCustomTree_t customTree, char ** arrayStrings, returnRecurtion_t recInfo)
{
	char * ptrToQuestion = nullptr;
	char * ptrToFeature  = nullptr;

	if ((ptrToQuestion = strchr(arrayStrings[recInfo.numString], '?')) != nullptr)
	{
		node->feature = readStringFromBuf(ptrToQuestion+1);
		node->leftDescendant = node+1;
		node->leftDescendant->parent = node;

		char * nameLeftDescendant = nullptr;
		char * nameRightDescendant = nullptr;

		if ((nameLeftDescendant = strchr(arrayStrings[(recInfo.numString)+1], '?')) != nullptr)
		{
			node->leftDescendant->feature = nameLeftDescendant+1;
			returnRecurtion_t  forSaveIngoThisNode = recInfo;
			recInfo.numString = recInfo.numString+1;
			recInfo = createNodeForUploadTree (node+1, customTree, arrayStrings, recInfo);

			if (strchr(arrayStrings[recInfo.numString], '?'))
			{
				node->rightDescendant = recInfo.nodeReturn + 3;
				node->rightDescendant->parent = node;
				recInfo.numString = recInfo.numString+3;
				returnRecurtion_t nodeIfSecondQuestion = createNodeForUploadTree (node->rightDescendant, customTree, arrayStrings, recInfo);
			}
			else
			{
				node->rightDescendant = recInfo.nodeReturn + 1;
				node->rightDescendant->parent = node;
				recInfo.numString = recInfo.numString+1;
				returnRecurtion_t nodeIfSecondQuestion = createNodeForUploadTree (node->rightDescendant, customTree, arrayStrings, recInfo);
			}
		}


		else if ((nameRightDescendant = strchr(arrayStrings[(recInfo.numString)+2], '?')) != nullptr)
		{
			char * nameLeftNode = strchr(arrayStrings[(recInfo.numString)+1], '.');
			node->leftDescendant->feature = readStringFromBuf(nameLeftNode+1);

			node->rightDescendant = node+2;
			node->rightDescendant->feature = nameRightDescendant+1;
			node->rightDescendant->parent = node;
			recInfo.numString = recInfo.numString+2;
			returnRecurtion_t nodeIfSecondQuestion = createNodeForUploadTree (node+2, customTree, arrayStrings, recInfo);
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
	else if ((ptrToFeature = strchr(arrayStrings[(recInfo.numString)], '.')) != nullptr) //arrayStrings[(recInfo.numString)+1]
	{
		node->feature = readStringFromBuf (ptrToFeature+1);
		recInfo.nodeReturn = node;
		return (recInfo);
	}
	else
	{
		printf ("\nERROR\n");
		recInfo = {0};
		return recInfo;
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

	FILE * inputTree = fopen ((const char *) nameFile, "rb");
	MY_ASSERT (inputTree == nullptr, "Unable to open the file with your tree");

	stat ((const char *) nameFile, &fileInfo);

	customTree->sizeFile = fileInfo.st_size;

	customTree->bufWithTree = (char *) calloc (customTree->sizeFile + 1, sizeof(char));
	MY_ASSERT (customTree->bufWithTree == nullptr, "Error in allocating memory for saving");
	(customTree->bufWithTree)[customTree->sizeFile] = '\0';

	fread (customTree->bufWithTree, customTree->sizeFile+1, 1, inputTree);
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
	return array;
}

void fillingArrayOfPtrs (size_t nElems, size_t nStrings, char ** arrayStrings, char * bufElems)
{
	MY_ASSERT (arrayStrings == nullptr, "There is no access to array of strings");
	MY_ASSERT (bufElems == nullptr, "There is no access to buffer of elements");

	arrayStrings[0] = bufElems;
	size_t j = 1;

	for (size_t i = 0; i < nElems && *bufElems != EOF && j < nStrings; i++)
	{
		if (*bufElems == '\0')
		{
			arrayStrings[j] = bufElems+1;
			j++;
		}
		bufElems++;
	}
}

char * readStringFromBuf (char * bufSource)
{
	char * bufDstn = (char *) calloc (MAX_SIZE_FEATURE, sizeof(char));
	MY_ASSERT (bufDstn == nullptr, "Unable to allocate new memory for the buf");
	MY_ASSERT (bufSource == nullptr, "There is no access to buf");

	bufDstn = strncpy (bufDstn, bufSource, MAX_SIZE_FEATURE);

	return bufDstn;
}
