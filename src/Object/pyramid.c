#include "Object/pyramid.h"

Object *objectPyramidNew()
{
	Object *pyramid = objectNew();

	if (pyramid)
	{
		objectUpdateModel(pyramid, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
	}

	return pyramid;
}