#ifndef COMMON_GEOMETRY_H
#define COMMON_GEOMETRY_H

#include <stdio.h>

#include "assets/mesh.h"

typedef enum {
	GEOMETRY_MESH,
	GEOMETRY_PLANE,
	GEOMETRY_CUBE,
	GEOMETRY_SPHERE,
	GEOMETRY_CAPSULE,
	GEOMETRY_CYLINDER,
	GEOMETRY_RAY
} GeometryType;

typedef struct {
	GeometryType type;
	Mesh *mesh;
	float width;
	float height;
	float depth;
	float radius;
	Vec3 translation;
	Vec4 rotation;
	Vec3 scale;
} Geometry;

Geometry geometryMesh(Mesh*);
Geometry geometryPlane(float, float); /* width, height */
Geometry geometryCube(float, float, float); /* width, height, depth */
Geometry geometrySphere(float); /* radius */
Geometry geometryCapsule(float, float); /* height, radius */
Geometry geometryCylinder(float, float); /* height, radius */
Geometry geometryRay(float); /* height */

#endif