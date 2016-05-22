#include "Assets/obj.h"

static int objLoad(Obj*, const char*, char**);
static int objProcess(Obj*, char*);
static int objProcessVector3f(char*, Vector3f*);
static int objProcessVector2f(char*, Vector2f*);
static int objProcessFace(char*, Vector3i*, Vector3i*, Vector3i*);

int objInit(Obj *obj, const char *path)
{
	int returnError = 0;

	char *fileData = NULL;

	obj->verticesLength = 0;
	obj->uvsLength = 0;
	obj->normalsLength = 0;
	obj->indicesLength = 0;

	obj->vertices = NULL;
	obj->uvs = NULL;
	obj->normals = NULL;
	obj->indices = NULL;

	if (objLoad(obj, path, &fileData))
	{
		returnError = -1;
	}
	else
	{
		obj->vertices = malloc(obj->verticesLength * sizeof(Vector3f));
		obj->uvs = malloc(obj->uvsLength * sizeof(Vector2f));
		obj->normals = malloc(obj->normalsLength * sizeof(Vector3f));
		obj->indices = malloc((obj->indicesLength * 3) * sizeof(Vector3i));

		if (objProcess(obj, fileData))
		{
			returnError = -2;
		}
	}

	free(fileData);

	return returnError;
}

void objDestroy(Obj *obj)
{
	free(obj->vertices);
	free(obj->uvs);
	free(obj->normals);
	free(obj->indices);
}

int objLoad(Obj *obj, const char *path, char **fileData)  
{  
	FILE *file = fopen(path, "rb");
	char currentLine[128];

	if (!file)  
	{  
		return -1;  
	}  

	fseek(file, 0, SEEK_END);  
	int length = ftell(file);  
	fseek(file, 0, SEEK_SET);  

	*fileData = calloc(length + 1, 1);

	int fileIndex = 0;

	while (fgets(currentLine, 128, file) != NULL)   
	{
		if (currentLine[0] == 'v')
		{
			if (currentLine[1] == ' ')
			{
				obj->verticesLength++;
			}
			else if (currentLine[1] == 't' && currentLine[2] == ' ')
			{
				obj->uvsLength++;
			}
			else if (currentLine[1] == 'n' && currentLine[2] == ' ')
			{
				obj->normalsLength++;
			}
		}
		else if (currentLine[0] == 'f' && currentLine[1] == ' ')
		{
			obj->indicesLength += 3;
		}

		int lineLength = strlen(currentLine);
		memcpy(&(*fileData)[fileIndex], currentLine, lineLength * sizeof(char));
		fileIndex += lineLength;
	}

	fclose(file);  

	return 0;
}

int objProcess(Obj *obj, char *fileData)
{
	int returnError = 0;

	int positionIndex = 0;
	int uvIndex = 0;
	int normalIndex = 0;
	int indexIndex = 0;

	char *currentLine = fileData;

	while (currentLine)
	{
		char *nextLine = strchr(currentLine, '\n');

		if (nextLine)
		{
			*nextLine = '\0';
		}

		if (currentLine[0] == 'v')
		{
			if (currentLine[1] == ' ')
			{
				if (!objProcessVector3f(currentLine, &obj->vertices[positionIndex]))
				{
					positionIndex++;
				}
				else
				{
					returnError = -1;
				}
			}
			else if (currentLine[1] == 't' && currentLine[2] == ' ')
			{
				if (!objProcessVector2f(currentLine, &obj->uvs[uvIndex]))
				{
					uvIndex++;
				}
				else
				{
					returnError = -2;
				}
			}
			else if (currentLine[1] == 'n' && currentLine[2] == ' ')
			{
				if (!objProcessVector3f(currentLine, &obj->normals[normalIndex]))
				{
					normalIndex++;
				}
				else
				{
					returnError = -3;
				}
			}
		}
		else if (currentLine[0] == 'f' && currentLine[1] == ' ')
		{
			if (!objProcessFace(currentLine, &obj->indices[indexIndex], &obj->indices[indexIndex + 1], &obj->indices[indexIndex + 2]))
			{
				indexIndex += 3;
			}
			else
			{
				returnError = -4;
			}
		}

		if (nextLine)
		{
			*nextLine = '\n'; 
		}

		currentLine = nextLine ? (nextLine + 1) : NULL;
	}
	
	return returnError;
}

int objProcessVector3f(char *line, Vector3f *vector3)
{
	if (sscanf(line, "%*s%f %f %f", &vector3->x, &vector3->y, &vector3->z) == 3)
	{
		return 0;
	}

	return -1;
}

int objProcessVector2f(char *line, Vector2f *vector2)
{
	if (sscanf(line, "%*s%f %f", &vector2->x, &vector2->y) == 2)
	{
		return 0;
	}

	return -1;
}

int objProcessFace(char *line, Vector3i *index1, Vector3i *index2, Vector3i *index3)
{
	if (sscanf(line, "%*s%i/%i/%i %i/%i/%i %i/%i/%i", &index1->x, &index1->y, &index1->z, &index2->x, &index2->y, &index2->z, &index3->x, &index3->y, &index3->z) == 9)
	{
		return 0;
	}
	else if (sscanf(line, "%*s%i//%i %i//%i %i//%i", &index1->x, &index1->z, &index2->x, &index2->z, &index3->x, &index3->z) == 6)
	{
		index1->y = 0;
		index2->y = 0;
		index3->y = 0;

		return 0;
	}
	else if (sscanf(line, "%*s%i/%i %i/%i %i/%i", &index1->x, &index1->y, &index2->x, &index2->y, &index3->x, &index3->y) == 6)
	{
		index1->z = 0;
		index2->z = 0;
		index3->z = 0;

		return 0;
	}
	else if (sscanf(line, "%*s%i %i %i", &index1->x, &index2->x, &index3->x) == 3)
	{
		index1->y = 0;
		index2->y = 0;
		index3->y = 0;

		index1->z = 0;
		index2->z = 0;
		index3->z = 0;

		return 0;
	}

	return -1;
}