#ifndef OBJECT_FEM_H
#define OBJECT_FEM_H

#include <stdio.h>
#include <stdint.h>
#include <archive.h>
#include <archive_entry.h>

#include "object.h"
#include "texture.h"
#include "Texture/dds.h"

Object *objectFemNew(const char*);
Model *objectFemModel(uint8_t*);

#endif