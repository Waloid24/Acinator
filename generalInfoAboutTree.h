#ifndef GENERALINFOABOUTTREE_H
#define GENERALINFOABOUTTREE_H

#include <stdio.h>
#include "my_assert.h"

const size_t MAX_SIZE_FEATURE = 40;

typedef char elem_t;

struct nodeTree {
    struct nodeTree * parent;
    elem_t * feature;
    struct nodeTree * leftDescendant;
    struct nodeTree * rightDescendant;
};

typedef struct nodeTree nodeTree_t;

enum IS_LAST {
    LAST,
    NO_LAST
};

#endif
