#include "core/database.h"

static int databaseCallback();

Database *databaseOpen(const char *path)
{	
	Database *database;

	if (sqlite3_open(path, &database) != SQLITE_OK) {
		sqlite3_close(database);
		return NULL;
	}

	return database;
}

void databaseClose(Database *database)
{
	assert(database != NULL);
	sqlite3_close(database);
}


DatabaseQuery *databaseQueryNew(Database *database, const char *sql)
{
	assert(database != NULL);

	DatabaseQuery *query = malloc(sizeof(DatabaseQuery));

	query->bound = 0;
	query->rows = 0;
	query->columns = 0;
	query->data = NULL;

	if (sqlite3_prepare(database, sql, -1, &query->statement, NULL) != SQLITE_OK) {
		sqlite3_finalize(query->statement);
		free(query);
		return NULL;
	}

	return query;
}

void databaseQueryDestroy(DatabaseQuery *query)
{
	assert(query != NULL);

	if (query->data != NULL) {
		unsigned length = query->rows * query->columns;

		for (unsigned i = 0; i < length; i++) {
			if (query->data[i] != NULL) {
				free(query->data[i]);
			}
		}

		free(query->data);
	}

	sqlite3_finalize(query->statement);
	free(query);
}

void databaseQueryBindInt(DatabaseQuery *query, int value)
{
	assert(query != NULL);
	sqlite3_bind_int(query->statement, ++query->bound, value);
}

void databaseQueryBindFloat(DatabaseQuery *query, float value)
{
	assert(query != NULL);
	sqlite3_bind_double(query->statement, ++query->bound, (double)value);
}

void databaseQueryBindVec2(DatabaseQuery *query, Vec2 value)
{
	assert(query != NULL);
	sqlite3_bind_blob(query->statement, ++query->bound, &value, sizeof(Vec2), SQLITE_TRANSIENT);
}

void databaseQueryBindVec3(DatabaseQuery *query, Vec3 value)
{
	assert(query != NULL);
	sqlite3_bind_blob(query->statement, ++query->bound, &value, sizeof(Vec3), SQLITE_TRANSIENT);
}

void databaseQueryBindVec4(DatabaseQuery *query, Vec4 value)
{
	assert(query != NULL);
	sqlite3_bind_blob(query->statement, ++query->bound, &value, sizeof(Vec4), SQLITE_TRANSIENT);
}

void databaseQueryBindMat4(DatabaseQuery *query, Mat4 value)
{
	assert(query != NULL);
	sqlite3_bind_blob(query->statement, ++query->bound, &value, sizeof(Mat4), SQLITE_TRANSIENT);
}


void databaseQueryBindString(DatabaseQuery *query, const char *value)
{
	assert(query != NULL);
	sqlite3_bind_text(query->statement, ++query->bound, value, -1, SQLITE_TRANSIENT);
}

int databaseQueryExecute(DatabaseQuery *query)
{
	assert(query != NULL);

	query->columns = sqlite3_column_count(query->statement);

	for (;;) {
		switch (sqlite3_step(query->statement)) {
			case SQLITE_ROW:
				query->rows++;
				continue;

			case SQLITE_DONE:
				sqlite3_reset(query->statement);
				return DATABASE_SUCCESS;

			default:
				sqlite3_reset(query->statement);
				return DATABASE_ERROR;
		}
	}
}

unsigned databaseQueryData(DatabaseQuery *query, char ***data)
{
	assert(query != NULL);

	unsigned length = query->rows * query->columns;

	if (query->data == NULL) {
		query->data = calloc(length, sizeof(char*));

		/**
		 * Loop through all the rows.
		 */
		for (unsigned x = 0; x < query->rows; x++) {
			if (sqlite3_step(query->statement) == SQLITE_ROW) {
				/**
				 * Loop through columns.
				 */
				for (unsigned y = 0; y < query->columns; y++) {
					const char *column = (const char*)sqlite3_column_text(query->statement, y);
					query->data[x * query->columns + y] = strdup(column);
				}	
			} else {
				/**
				 * Cleanup data to start again.
				 */
				for (unsigned i = 0; i < length; i++) {
					if (query->data[i] != NULL) {
						free(query->data[i]);
					}
				}

				sqlite3_reset(query->statement);
				free(query->data);

				/**
				 * Null set the data so we can try again.
				 */
				query->data = NULL;
				return 0;
			}
		}
	}

	*data = query->data;
	return length;
}

DatabaseStatus databaseExecute(Database *database, const char *sql)
{
	assert(database != NULL);

	DatabaseStatus status = DATABASE_ERROR;
	DatabaseQuery *query;

	if ((query = databaseQueryNew(database, sql)) != NULL) {
		status = databaseQueryExecute(query);
		databaseQueryDestroy(query);
	}

	return status;
}