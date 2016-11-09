#ifndef PLANE_H
#define PLANE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Object/mesh.h"
#include "Tools/hashtable.h"

typedef Mesh Plane;

int planeInit(Plane*, const char*);
void planeDestroy(Plane*);

#endif