#include "objectComparison.h"

int compareObjects (nodeTree_t * node, FILE * log)
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

	if (myStrcmp(firstObject->feature, secondObject->feature) == 0)
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
		nodeTree_t * fstObj = (nodeTree_t *) firstObject;
		nodeTree_t * scndObj = (nodeTree_t *) secondObject;

		printf ("The first object, unlike the second, ");
		while (myStrcmp(fstObj->feature, scndObj->feature) != 0)
		{
			if (fstObj->parent != nullptr)
			{
				if (myStrcmp(fstObj->parent->rightDescendant->feature, fstObj->feature) == 0)
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

		fstObj = (nodeTree_t * ) firstObject;
		scndObj = (nodeTree_t * ) secondObject;

		printf ("\nBut the second object ");
		while (myStrcmp(fstObj->feature, scndObj->feature) != 0)
		{
			if (scndObj->parent != nullptr)
			{
				if (myStrcmp(scndObj->parent->rightDescendant->feature, scndObj->feature) == 0)
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
}

nodeTree_t * findObjectForCompare (nodeTree_t * node, char * nameObject, nodeTree_t * desiredObject)
{
	MY_ASSERT (node == nullptr, "There is no access to tree");
	MY_ASSERT (nameObject == nullptr, "There is no access to object");

	if (myStrcmp (node->feature, nameObject) != 0)
	{
		if (node->leftDescendant != nullptr && desiredObject == nullptr)
		{
			desiredObject = findObjectForCompare (node->leftDescendant, nameObject, desiredObject);
		}
		if (node->rightDescendant != nullptr && desiredObject == nullptr)
		{
			desiredObject = findObjectForCompare (node->rightDescendant, nameObject, desiredObject);
		}
	}
	else
	{
		return node;
	}
	return desiredObject;
}

int myStrcmp (const char * string1, const char * string2)
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
