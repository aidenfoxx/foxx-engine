#include "Object/plane.h"

Object *objectPlaneNew()
{
	Object *plane = objectNew();

	if (plane)
	{
		objectUpdateModel(plane, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
	}

	return plane;
}