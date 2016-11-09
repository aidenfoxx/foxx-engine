#ifndef FEM_H
#define FEM_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

#include "Object/mesh.h"
#include "Object/texture.h"
#include "Tools/hashtable.h"

int femLoad(Mesh*, Texture*, Texture*, Texture*, const char*);

#endif