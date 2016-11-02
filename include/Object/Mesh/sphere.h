#ifndef SPHERE_H
#define SPHERE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Object/mesh.h"
#include "Tools/hashtable.h"

typedef Mesh Sphere;

int sphereInit(Sphere*, const char*);
void sphereDestroy(Sphere*);

#endif