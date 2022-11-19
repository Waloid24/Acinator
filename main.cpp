#include "akinator.h"

int main (void)
{
    nodeTree_t tree = {};

    FILE * log = fopen ("log.txt", "a");
    MY_ASSERT (log == nullptr, "There is no access to logfile");

    printf ("Hello, master! You shoud answer \"yes\" or \"no\". Let's get started!\n");

    operatingMode (&tree, log);

    return 0;
}
