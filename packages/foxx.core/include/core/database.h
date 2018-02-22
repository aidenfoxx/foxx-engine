#ifndef CORE_DATABASE_H
#define CORE_DATABASE_H

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sqlite3.h>

#include "core/memory.h"
#include "core/math.h"

typedef enum {
	DATABASE_SUCCESS = 0,
	DATABASE_ERROR = INT_MIN
} DatabaseStatus;

typedef sqlite3 Database;

typedef struct {
	unsigned bound;
	unsigned rows;
	unsigned columns;
	char **data;
	sqlite3_stmt *statement;
} DatabaseQuery;

Database *databaseOpen(const char*);
void databaseClose(Database*);

DatabaseQuery *databaseQueryNew(Database*, const char*);
void databaseQueryDestroy(DatabaseQuery*);

void databaseQueryBindInt(DatabaseQuery*, int);
void databaseQueryBindFloat(DatabaseQuery*, float);
void databaseQueryBindVec2(DatabaseQuery*, Vec2);
void databaseQueryBindVec3(DatabaseQuery*, Vec3);
void databaseQueryBindVec4(DatabaseQuery*, Vec4);
void databaseQueryBindMat4(DatabaseQuery*, Mat4);
void databaseQueryBindString(DatabaseQuery*, const char*);

DatabaseStatus databaseQueryExecute(DatabaseQuery*);
unsigned databaseQueryData(DatabaseQuery*, char***);

DatabaseStatus databaseExecute(Database*, const char*);

#endif