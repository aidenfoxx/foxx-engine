#include "renderer/renderable/geometry.h"

/**
 * TODO: Test if you can pass a NULL mesh to Geometry.
 */
RenderableGeometry *renderableGeometryNew(Geometry geometry)
{
	RenderableGeometry *renderableGeometry = malloc(sizeof(RenderableGeometry));

	renderableGeometry->indices = 0;
	renderableGeometry->aabb.min = vec3(0.0f, 0.0f, 0.0f);
	renderableGeometry->aabb.max = vec3(0.0f, 0.0f, 0.0f);

	glGenVertexArrays(1, &renderableGeometry->vao);
	glGenBuffers(4, renderableGeometry->vbo);

	Mesh *mesh = NULL;

	if (geometry.type == GEOMETRY_MESH) {
		mesh = geometry.mesh;
	} else if (geometry.type == GEOMETRY_PLANE) {
		// Generate mesh
	} else if (geometry.type == GEOMETRY_CUBE) {
		// Generate mesh
	} else if (geometry.type == GEOMETRY_SPHERE) {
		// Generate mesh
	} else if (geometry.type == GEOMETRY_CAPSULE) {
		// Generate mesh
	} else if (geometry.type == GEOMETRY_CYLINDER) {
		// Generate mesh
	} else if (geometry.type == GEOMETRY_RAY) {
		// Generate mesh
	}

	if (mesh != NULL) {
		renderableGeometry->indices = (GLsizei)mesh->indices.length;

		/**
		 * Define VAO.
		 */
		glBindVertexArray(renderableGeometry->vao);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0); 
		glVertexAttribFormat(1, 2, GL_FLOAT, GL_FALSE, 0); 
		glVertexAttribFormat(2, 3, GL_FLOAT, GL_FALSE, 0);
		
		/**
		 * Define VBOs.
		 */
		if (mesh->vertices.length > 0) {
			glBindBuffer(GL_ARRAY_BUFFER, renderableGeometry->vbo[0]);
			glBufferStorage(GL_ARRAY_BUFFER, mesh->vertices.length * sizeof(Vec3), (float*)mesh->vertices.data, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);	
		}

		if (mesh->uvs.length > 0) {
			glBindBuffer(GL_ARRAY_BUFFER, renderableGeometry->vbo[1]);
			glBufferStorage(GL_ARRAY_BUFFER, mesh->uvs.length * sizeof(Vec2), (float*)mesh->uvs.data, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
		}

		if (mesh->normals.length > 0) {
			glBindBuffer(GL_ARRAY_BUFFER, renderableGeometry->vbo[2]);
			glBufferStorage(GL_ARRAY_BUFFER, mesh->normals.length * sizeof(Vec3), (float*)mesh->normals.data, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
		}

		if (mesh->indices.length > 0) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderableGeometry->vbo[3]);
			glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.length * sizeof(unsigned), (unsigned*)mesh->indices.data, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
		}

		glBindVertexBuffer(0, renderableGeometry->vbo[0], 0, sizeof(Vec3));
		glBindVertexBuffer(1, renderableGeometry->vbo[1], 0, sizeof(Vec2));
		glBindVertexBuffer(2, renderableGeometry->vbo[2], 0, sizeof(Vec3));

		/**
		 * Unbind.
		 */
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
	return renderableGeometry;
}

void renderableGeometryFree(RenderableGeometry *renderableGeometry)
{
	assert(renderableGeometry != NULL);
	glDeleteVertexArrays(1, &renderableGeometry->vao);
	glDeleteBuffers(4, renderableGeometry->vbo);
	free(renderableGeometry);
}