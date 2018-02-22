#include "assets/mesh/obj.h"

static Mesh *meshObjEmpty(Mesh*);
static Mesh *meshObjProcess(const char*);
static Mesh *meshObjIndex(Mesh*);

static unsigned meshObjProcessVec3(char*, Vec3*);
static unsigned meshObjProcessVec2(char*, Vec2*);
static unsigned meshObjProcessFace(char*, int*);

Mesh *meshObjNew(const char *data)
{
	Mesh *processed = meshObjProcess(data);
	Mesh *indexed = meshObjIndex(processed);

	meshFree(processed);

	return indexed;
}

Mesh *meshObjEmpty(Mesh *mesh)
{
	free(mesh->vertices.data);
	free(mesh->uvs.data);
	free(mesh->normals.data);
	free(mesh->indices.data);

	mesh->vertices.data = NULL;
	mesh->uvs.data = NULL;
	mesh->normals.data = NULL;
	mesh->indices.data = NULL;

	mesh->vertices.length = 0;
	mesh->uvs.length = 0;
	mesh->normals.length = 0;
	mesh->indices.length = 0;

	return mesh;
}

Mesh *meshObjProcess(const char *data)
{
	Mesh *mesh = malloc(sizeof(Mesh));

	mesh->vertices.length = 0;
	mesh->uvs.length = 0;
	mesh->normals.length = 0;
	mesh->indices.length = 0;

	/**
	 * Get object info.
	 */
	char *currentLine = (char*)data;

	while (currentLine) {
		char *nextLine = strchr(currentLine, '\n');

		if (currentLine[0] == 'v') {
			if (currentLine[1] == ' ') {
				mesh->vertices.length++;
			} else if (currentLine[1] == 't' && currentLine[2] == ' ') {
				mesh->uvs.length++;
			} else if (currentLine[1] == 'n' && currentLine[2] == ' ') {
				mesh->normals.length++;
			}
		} else if (currentLine[0] == 'f' && currentLine[1] == ' ') {
			mesh->indices.length += 3;
		}

		currentLine = nextLine != NULL ? (nextLine + 1) : NULL;
	}

	/**
	 * Allocate storage for data.
	 */
	mesh->vertices.data = malloc(mesh->vertices.length * sizeof(Vec3));
	mesh->uvs.data = malloc(mesh->uvs.length * sizeof(Vec2));
	mesh->normals.data = malloc(mesh->normals.length * sizeof(Vec3));
	mesh->indices.data = malloc((mesh->indices.length * 9) * sizeof(int));

	mesh->vertices.length = 0;
	mesh->uvs.length = 0;
	mesh->normals.length = 0;
	mesh->indices.length = 0;

	/**
	 * Reset position in data.
	 */
	currentLine = (char*)data;

	while (currentLine) {
		char *nextLine = strchr(currentLine, '\n');

		/**
		 * Terminate the current line on the newline 
		 * character.
		 */
		if (nextLine != NULL) {
			*nextLine = '\0';
		}

		if (currentLine[0] == 'v') {
			if (currentLine[1] == ' ') {
				if (!meshObjProcessVec3(currentLine, &mesh->vertices.data[mesh->vertices.length])) {
					mesh->vertices.length++;
				} else {
					/**
					 * If parsing failed break out and
					 * return empty mesh.
					 */
					mesh = meshObjEmpty(mesh);
					break;
				}
			} else if (currentLine[1] == 't' && currentLine[2] == ' ') {
				if (!meshObjProcessVec2(currentLine, &mesh->uvs.data[mesh->uvs.length])) {
					mesh->uvs.length++;
				} else {
					/**
					 * If parsing failed break out and
					 * return empty mesh.
					 */
					mesh = meshObjEmpty(mesh);
					break;
				}
			} else if (currentLine[1] == 'n' && currentLine[2] == ' ') {
				if (!meshObjProcessVec3(currentLine, &mesh->normals.data[mesh->normals.length])) {
					mesh->normals.length++;
				} else {
					/**
					 * If parsing failed break out and
					 * return empty mesh.
					 */
					mesh = meshObjEmpty(mesh);
					break;
				}
			}
		} else if (currentLine[0] == 'f' && currentLine[1] == ' ') {
			if (!meshObjProcessFace(currentLine, &mesh->indices.data[mesh->indices.length * 3])) {
				mesh->indices.length += 3;
			} else {
				/**
				 * If parsing failed break out and
				 * return empty mesh.
				 */
				mesh = meshObjEmpty(mesh);
				break;
			}
		}

		/**
		 * Set the next line to begin after the newline
		 * character we found.
		 */
		currentLine = nextLine != NULL ? (nextLine + 1) : NULL;
	}

	return mesh;
}

Mesh *meshObjIndex(Mesh *mesh)
{
	Mesh *indexed = malloc(sizeof(Mesh));

	indexed->vertices.data = malloc(mesh->indices.length * sizeof(Vec3));
	indexed->uvs.data = malloc(mesh->indices.length * sizeof(Vec2));
	indexed->normals.data = malloc(mesh->indices.length * sizeof(Vec3));
	indexed->indices.data = malloc(mesh->indices.length * sizeof(unsigned));

	indexed->vertices.length = 0;
	indexed->uvs.length = 0;
	indexed->normals.length = 0;
	indexed->indices.length = mesh->indices.length;

	HashTable *indexTable = hashTableNew();

	unsigned index = 0;
	unsigned *duplicate = NULL;

	for (unsigned i = 0; i < mesh->indices.length; i++) {
		unsigned x = i * 3;		

		/**
		 * Create a unique key from all 3 index
		 * variables.
		 */
		int keyLength = snprintf(NULL, 0, "%i/%i/%i", (int)mesh->indices.data[x], (int)mesh->indices.data[x + 1], (int)mesh->indices.data[x + 2]);

		if (keyLength > 0) {
			char key[keyLength + 1];

			sprintf(key, "%i/%i/%i", (int)mesh->indices.data[x], (int)mesh->indices.data[x + 1], (int)mesh->indices.data[x + 2]);

			if ((duplicate = (unsigned*)hashTableGet(indexTable, hashMurmur3(key))) == NULL) {
				if ((int)mesh->indices.data[x] > 0) {
					indexed->vertices.data[index] = mesh->vertices.data[(int)mesh->indices.data[x] - 1];
					indexed->vertices.length++;
				} else if ((int)mesh->indices.data[x] < 0) {
					indexed->vertices.data[index] = mesh->vertices.data[mesh->vertices.length + (int)mesh->indices.data[x]];
					indexed->vertices.length++;
				} else {
					/**
					 * If vertex data is missing nullify 
					 * the mesh and break out.
					 */
					indexed = meshObjEmpty(indexed);
					break;
				}

				if ((int)mesh->indices.data[x + 1] > 0) {
					indexed->uvs.data[index] = mesh->uvs.data[(int)mesh->indices.data[x + 1] - 1];
					indexed->uvs.length++;
				} else if ((int)mesh->indices.data[x + 1] < 0) {
					indexed->uvs.data[index] = mesh->uvs.data[mesh->uvs.length + (int)mesh->indices.data[x + 1]];
					indexed->uvs.length++;
				}

				if ((int)mesh->indices.data[x + 2] > 0) {
					indexed->normals.data[index] = mesh->normals.data[(int)mesh->indices.data[x + 2] - 1];
					indexed->normals.length++;
				} else if ((int)mesh->indices.data[x + 2] < 0) {
					indexed->normals.data[index] = mesh->normals.data[mesh->normals.length + (int)mesh->indices.data[x + 2]];
					indexed->normals.length++;
				}

				indexed->indices.data[i] = index;
				index++;

				hashTableSet(indexTable, hashMurmur3(key), &indexed->indices.data[i]);
			} else {
				indexed->indices.data[i] = *duplicate;
			}
		}
	}

	hashTableFree(indexTable);

	/**
	 * Resize buffers to match data.
	 */
	if (indexed->uvs.length != indexed->vertices.length) {
		indexed->uvs.length = 0;
	}
	
	if (indexed->normals.length != indexed->vertices.length) {
		indexed->normals.length = 0;
	}

	indexed->vertices.data = realloc(indexed->vertices.data, indexed->vertices.length * sizeof(Vec3));
	indexed->uvs.data = realloc(indexed->uvs.data, indexed->uvs.length * sizeof(Vec2));
	indexed->normals.data = realloc(indexed->normals.data, indexed->normals.length * sizeof(Vec3));

	return indexed;
}

unsigned meshObjProcessVec3(char *line, Vec3 *vec3)
{
	if (sscanf(line, "%*s%f %f %f", &vec3->x, &vec3->y, &vec3->z) == 3) {
		return 0;
	}
	return -1;
}

unsigned meshObjProcessVec2(char *line, Vec2 *vec2)
{
	if (sscanf(line, "%*s%f %f", &vec2->x, &vec2->y) == 2) {
		return 0;
	}
	return -1;
}

unsigned meshObjProcessFace(char *line, int *face)
{
	if (sscanf(line, "%*s%i/%i/%i %i/%i/%i %i/%i/%i", &face[0], &face[1], &face[2], &face[3], &face[4], &face[5], &face[6], &face[7], &face[8]) == 9) {
		return 0;
	} else if (sscanf(line, "%*s%i//%i %i//%i %i//%i", &face[0], &face[2], &face[3], &face[5], &face[6], &face[8]) == 6) {
		face[1] = 0;
		face[4] = 0;
		face[7] = 0;

		return 0;
	} else if (sscanf(line, "%*s%i/%i %i/%i %i/%i", &face[0], &face[1], &face[3], &face[4], &face[6], &face[7]) == 6) {
		face[2] = 0;
		face[5] = 0;
		face[8] = 0;

		return 0;
	} else if (sscanf(line, "%*s%i %i %i", &face[0], &face[3], &face[6]) == 3) {
		face[1] = 0;
		face[4] = 0;
		face[7] = 0;

		face[2] = 0;
		face[5] = 0;
		face[8] = 0;

		return 0;
	}
	return -1;
}