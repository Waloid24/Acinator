#include "objectDefinition.h"

void definingMode (nodeTree_t * node, FILE * log)
{
	MY_ASSERT (node == nullptr, "There is no access to tree");
	MY_ASSERT (log == nullptr, "There is no access to logfile");

    printf ("Enter the name of the object you want to define: ");

	char * nameObject = (char *) calloc (MAX_SIZE_FEATURE, sizeof (char));
	MY_ASSERT (nameObject == nullptr, "Unable to allocate new memory");
	getString (nameObject);

    printf ("\n");

    printf ("nameObject = %s\n", nameObject);
	unsigned char isFound = findObject (node, nameObject, 0); //0 заменить на enum с noFound

	printf ("\n");

	if (isFound == 0)
	{
		printf ("This element was not found in the tree.\n");
	}
}

unsigned int findObject (nodeTree_t * node, char * nameObject, unsigned int isObejectFound)
{

	MY_ASSERT (node == nullptr, "There is no access to tree");
	MY_ASSERT (nameObject == nullptr, "There is no access to object");

	if (myStrcmp (node->feature, nameObject) != 0)
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
		printf ("Definition of %s: ", nameObject);
		return defineOfWord (node);
	}
	return isObejectFound;
}

int defineOfWord (nodeTree_t * node)
{
	if (node->parent != nullptr)
	{
		if (myStrcmp(node->parent->rightDescendant->feature, node->feature) == 0)
		{
			printf ("not ");
		}

		printf ("%s, ", node->parent->feature);
		defineOfWord (node->parent);
	}
	return 1;
}
