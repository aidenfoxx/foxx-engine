#ifndef CYLINDER_H
#define CYLINDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Object/mesh.h"
#include "Tools/hashtable.h"

typedef Mesh Cylinder;

int cylinderInit(Cylinder*, const char*);
void cylinderDestroy(Cylinder*);

#endif