#include "Object/cone.h"

Object *objectConeNew()
{
	Object *cone = objectNew();

	if (cone)
	{
		objectUpdateModel(cone, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
	}

	return cone;
}