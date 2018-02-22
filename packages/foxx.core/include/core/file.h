#ifndef CORE_FILE_H
#define CORE_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef enum {
	FILE_SUCCESS = 0,
	FILE_ERROR_READ = INT_MIN,
	FILE_ERROR_PERMISSIONS
} FileStatus;

int fileRead(const char*, char**);
FileStatus fileWrite(const char*, const char*, unsigned);
FileStatus fileAppend(const char*, const char*);

int fileBinaryRead(const char*, uint8_t**);
FileStatus fileBinaryWrite(const char*, const uint8_t*, unsigned, unsigned);
FileStatus fileBinaryAppend(const char*, const uint8_t*, unsigned);

#endif