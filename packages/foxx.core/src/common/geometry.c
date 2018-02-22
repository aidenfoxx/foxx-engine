#include "common/geometry.h"

/**
 * Generate geometry
 */
Geometry geometryMesh(Mesh *mesh)
{
	Geometry geometry;

	geometry.type = GEOMETRY_MESH;
	geometry.mesh = mesh;

	return geometry;
}

Geometry geometryPlane(float width, float height)
{
	Geometry geometry;

	geometry.type = GEOMETRY_PLANE;
	geometry.width = width;
	geometry.height = height;
	
	return geometry;
}

Geometry geometryCube(float width, float height, float depth)
{
	Geometry geometry;

	geometry.type = GEOMETRY_CUBE;
	geometry.width = width;
	geometry.height = height;
	geometry.depth = depth;

	return geometry;
}

Geometry geometrySphere(float radius)
{
	Geometry geometry;

	geometry.type = GEOMETRY_SPHERE;
	geometry.radius = radius;

	return geometry;
}

Geometry geometryCapsule(float height, float radius)
{
	Geometry geometry;

	geometry.type = GEOMETRY_CAPSULE;
	geometry.height = height;
	geometry.radius = radius;

	return geometry;
}

Geometry geometryCylinder(float height, float radius)
{
	Geometry geometry;

	geometry.type = GEOMETRY_CYLINDER;
	geometry.height = height;
	geometry.radius = radius;

	return geometry;
}

Geometry geometryRay(float height)
{
	Geometry geometry;

	geometry.type = GEOMETRY_RAY;
	geometry.height = height;

	return geometry;
}