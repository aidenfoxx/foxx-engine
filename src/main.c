#include <stdio.h>

#include "core/array.h"
#include "core/database.h"

int main(int argc, char *argv[])
{
	Array *test = arrayNew();
	Database *database = databaseOpen("test.db");

	return 0;
}