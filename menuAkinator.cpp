#include "akinator.h"
#include "graphicDump.h"
#include "objectComparison.h"
#include "objectDefinition.h"
#include "guessingMode.h"
#include "modeWithSaving.h"

#define LONG_LINE "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"

unsigned char IS_UPLOAD = 0;

const int noMACROS = 'n';
const int NOMACROS = 'N';
const int yesMACROS = 'y';
const int YESMACROS = 'Y';

//--------------------------------------------------static----------------------------------------------------------

static void deleteTree (nodeTree_t * node)
{
	printf ("node->feature = %s\n", node->feature);
	if (node->leftDescendant != nullptr)
	{
		printf ("before go to left node: node->leftDescendant->feature = %s\n", node->feature);
		deleteTree (node->leftDescendant);
	}
	printf ("before go to right: node->feature = %s\n", node->feature);
	if (node->rightDescendant != nullptr)
	{
		deleteTree (node->rightDescendant);
	}
	printf ("before delete this node: node->feature = %s\n", node->feature);

	free(node->feature);
	printf ("a\n");
}

static int processCommand (void)
{
    int command = getchar ();
    MY_ASSERT (command == EOF, "Command processing error");

    while (getchar() != '\n') {;}

    if (command != '1' && command != '2' && command != '3' && command != '4' && command != '5' && command != '6')
    {
        printf ("There is no such mode of operation. Try again.\n");
        command = processCommand ();
    }

	return command;
}

//------------------------------------------------------------------------------------------------------------------
//---------------------------------------------other functions------------------------------------------------------
void operatingMode (nodeTree_t * tree, FILE * log)
{
	MY_ASSERT (tree == nullptr, "There is no access to tree");
	MY_ASSERT (log == nullptr, "There is no access to logfile");

	system("echo \"Мы сдадим матан.\" | festival --tts --language russian");
	sleep (0.3);

    printf (LONG_LINE);
    printf ("What mode of operation do you want to choose?\n");
    printf ("1) guess the object;    2) to define an object;\n");
    printf ("3) compare objects;     4) show tree;\n");
    printf ("5) exit with saving;    6) exit without saving\n");
    printf (LONG_LINE);

    int cmd = processCommand ();

	if (cmd == '1')
	{
		if (tree->feature == nullptr)
		{
			printf ("There is not a single element in the tree\n");
			printf ("What do you want: to create [n]ew tree or to [u]pload your tree to the program?\n");

			system("echo \"There is not a single element in the tree.\" | festival --tts --language english");
			system("echo \"What do you want: to create [n]ew tree or to [u]pload your tree to the program?\" | festival --tts --language english");
			sleep(0.4);

			selectingTreeSource (&tree);
		}
		guessingMode (tree, log);
		operatingMode (tree, log);
	}
	else if (cmd == '2')
	{
		if (tree->feature == nullptr)
		{
			printf ("There is not a single element in the tree\n");
			printf ("What do you want: to create [n]ew tree or to [u]pload your tree to the program?\n");

			system("echo \"There is not a single element in the tree.\" | festival --tts --language english");
			system("echo \"What do you want: to create [n]ew tree or to [u]pload your tree to the program?\" | festival --tts --language english");
			sleep(0.4);

			selectingTreeSource (&tree);
		}
		definingMode (tree, log);
		operatingMode (tree, log);
	}
	else if (cmd == '3')
	{
		if (tree->feature == nullptr)
		{
			printf ("There is not a single element in the tree\n");
			printf ("What do you want: to create [n]ew tree or to [u]pload your tree to the program?\n");

			system("echo \"There is not a single element in the tree.\" | festival --tts --language english");
			system("echo \"What do you want: to create [n]ew tree or to [u]pload your tree to the program?\" | festival --tts --language english");
			sleep(0.4);

			selectingTreeSource (&tree);
		}
		compareObjects (tree, log);
		exitWithSaving (tree, log, NO_LAST, 0);
		operatingMode (tree, log);
	}
	else if (cmd == '4')
	{
		if (tree->feature == nullptr)
		{
			printf ("There is not a single element in the tree\n");
			printf ("What do you want: to create [n]ew tree or to [u]pload your tree to the program?\n");

			system("echo \"There is not a single element in the tree.\" | festival --tts --language english");
			system("echo \"What do you want: to create [n]ew tree or to [u]pload your tree to the program?\" | festival --tts --language english");
			sleep(0.4);

			selectingTreeSource (&tree);
		}
		showTree (tree);
		operatingMode (tree, log);
	}
	else if (cmd == '5')
	{
		exitWithSaving (tree, log, NO_LAST, 0);
		fprintf (log, "\n");
	}
	else
	{
		if (tree == nullptr || tree->leftDescendant == nullptr || tree->rightDescendant == nullptr)
		{
			printf ("There are no elements in your tree, there is nothing to delete\n");
			system("echo \"There are no elements in your tree, there is nothing to delete.\" | festival --tts --language english");
			operatingMode (tree, log);
		}
		else
		{
			if (IS_UPLOAD)
			{
				free(tree);
			}
			else
			{
				deleteTree (tree);
			}
			printf ("You shouldn't be doing this to me\n");
		}
	}
}

void selectingTreeSource (nodeTree_t ** tree)
{
	MY_ASSERT (tree == nullptr, "There is no access to the tree");

	//printf ("in selectingTreeSource (ptr ptr) tree = %p\n", tree);

	int answer = getchar ();
    MY_ASSERT (answer == EOF, "Command processing error");

	// printf ("IN PROCESS ANSWER: answer = %c and in ascii \"%d\"\n", answer, answer);

    while (getchar() != '\n') {;}

	if (answer == 'n') createFirstNode (tree);
	else if (answer == 'u') uploadTree (tree);
	else
	{
		printf ("Please, enter letter \"n\" or \"u\"\n");
		selectingTreeSource(tree);
	}
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
		(*tree)->leftDescendant = createNewNode (*tree, (*tree)->leftDescendant);
	}
	if ((*tree)->rightDescendant == nullptr)
	{
		printf ("If this object isn't %s it is ...\n", (*tree)->feature);
		(*tree)->rightDescendant = createNewNode ((*tree), (*tree)->rightDescendant);
	}
}

void createFirstFeature (nodeTree_t * tree)
{
	MY_ASSERT (tree == nullptr, "There is no access to tree");

	printf ("Please, enter the feature of the first objects\n");
	tree->feature = getFeature(tree->feature);
}

nodeTree_t * createNewNode (nodeTree_t * parentNewNode, nodeTree_t * placeForNewNode)
{
	if (placeForNewNode != nullptr)
		printf ("Attention! You can overwrite old data!\n");

	placeForNewNode = (nodeTree_t *) calloc (1, sizeof(nodeTree_t));
	placeForNewNode->feature = getFeature(placeForNewNode->feature);
	placeForNewNode->parent = parentNewNode;

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

int processAnswer (void)
{
	int answer = getchar ();
    MY_ASSERT (answer == EOF, "Command processing error");

    while (getchar() != '\n') {;}

	if (answer == noMACROS || answer == NOMACROS)
	{
		return 0;
	}
	else if (answer == yesMACROS || answer == YESMACROS)
	{
		return 1;
	}
	else
	{
		printf ("Please, enter letter \"Y\" or \"y\" if you're agree with question, and \"N\" or \"n\" otherwise\n");
		processAnswer();
	}
	return -3;
}

//--------------------------------------------------------------------------------------------------------------------
