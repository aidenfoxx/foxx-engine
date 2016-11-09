#ifndef PYRAMID_H
#define PYRAMID_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Object/mesh.h"
#include "Tools/hashtable.h"

typedef Mesh Pyramid;

int pyramidInit(Pyramid*, const char*);
void pyramidDestroy(Pyramid*);

#endif