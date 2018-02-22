#ifndef CORE_HASH_H
#define CORE_HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define HASH_SEED 1688943522

uint32_t hashMurmur3(const char*);

#endif