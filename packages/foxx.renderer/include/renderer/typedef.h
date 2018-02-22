#ifndef RENDERER_TYPEDEF_H
#define RENDERER_TYPEDEF_H

#include <stdio.h>

#include "renderer/camera.h"
#include "renderer/shader.h"
#include "renderer/renderable/geometry.h"
#include "renderer/renderable/material.h"

typedef struct Scene Scene;
typedef struct Actor Actor;
typedef struct Renderable Renderable;

struct Scene {
	Camera *camera;
	Shader *shader;
	struct {
		Actor **data;
		unsigned length;
	} actors;
};

struct Actor{
	void **parent;
	struct {
		Renderable **data;
		unsigned length;
	} renderables;
	Vec3 translation;
	Vec4 rotation;
	Vec3 scale;
	Mat4 transform;
};

struct Renderable {
	void **parent;
	RenderableGeometry *geometry;
	RenderableMaterial *material;
	Vec3 translation;
	Vec4 rotation;
	Vec3 scale;
	Mat4 transform;
	struct {
		Vec3 min;
		Vec3 max;
	} aabb;
};

#endif