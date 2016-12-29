#ifndef MODEL_DDS_H
#define MODEL_DDS_H

#include <stdio.h>

#include "context.h"
#include "model.h"

typedef struct {
	GLuint vbo[4];
	Model *model;
} ModelBuffer;

ModelBuffer *modelBufferNew(Model*);
void modelBufferFree(ModelBuffer*);

Model *modelBufferGetModel(ModelBuffer*);

void modelBufferBind(ModelBuffer*, int);
void modelBufferUnbind();

#endif