#include "Object/sphere.h"

Object *objectSphereNew()
{
	Object *sphere = objectNew();

	if (sphere)
	{
		objectUpdateModel(sphere, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
	}

	return sphere;
}