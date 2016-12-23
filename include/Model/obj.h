#ifndef MODEL_OBJ_H
#define MODEL_OBJ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "model.h"
#include "Tools/glmath.h"
#include "Tools/hashtable.h"

Model *modelObjNew(uint8_t*);
Model *modelObjLoad(const char*);

#endif