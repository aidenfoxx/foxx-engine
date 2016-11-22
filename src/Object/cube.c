#include "Object/cube.h"

Object *objectCubeNew()
{
	Object *cube = objectNew();

	if (cube)
	{
		objectUpdateModel(cube, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
	}

	return cube;
}