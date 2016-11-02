#ifndef CUBE_H
#define CUBE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Object/mesh.h"
#include "Tools/hashtable.h"

typedef Mesh Cube;

int cubeInit(Cube*, const char*);
void cubeDestroy(Cube*);

#endif