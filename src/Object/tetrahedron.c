#include "Object/tetrahedron.h"

Object *objectTetrahedronNew()
{
	Object *tetrahedron = objectNew();

	if (tetrahedron)
	{
		objectUpdateModel(tetrahedron, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
	}

	return tetrahedron;
}