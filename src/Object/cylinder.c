#include "Object/cylinder.h"

Object *objectCylinderNew()
{
	Object *cylinder = objectNew();

	if (cylinder)
	{
		objectUpdateModel(cylinder, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
	}

	return cylinder;
}