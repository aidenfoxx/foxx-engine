#ifndef OBJECT_FEM_H
#define OBJECT_FEM_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

#include "object.h"

Object *objectFemNew(const char*);

void objectFemUpdateModel(Object*, uint8_t*);

#endif