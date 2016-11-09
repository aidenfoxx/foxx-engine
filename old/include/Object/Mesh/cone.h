#ifndef CONE_H
#define CONE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Object/mesh.h"
#include "Tools/hashtable.h"

typedef Mesh Cone;

int coneInit(Cone*, const char*);
void coneDestroy(Cone*);

#endif