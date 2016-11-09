#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Object/mesh.h"
#include "Tools/hashtable.h"

typedef Mesh Tetrahedron;

int tetrahedronInit(Tetrahedron*, const char*);
void tetrahedronDestroy(Tetrahedron*);

#endif