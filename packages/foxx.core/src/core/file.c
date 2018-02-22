#include "core/file.h"

int fileRead(const char *path, char **data)
{
	FILE *file;

	/**
	 * Open file for reading.
	 */
	if (file = fopen(path, "rb")) {
		/**
		 * Get file length.
		 */
		fseek(file, 0, SEEK_END);
		int length = ftell(file);
		fseek(file, 0, SEEK_SET);

		/**
		 * Allocate memory to store file.
		 */
		char *temp = calloc(length + 1, sizeof(char));

		/**
		 * Copy file to memory buffer.
		 */
		if (fread(temp, sizeof(char), length, file) == length) {
			/**
			 * On success, return the data to the pointer.
			 */
			*data = temp;
			fclose(file);
			return length;
		}

		fclose(file);
		free(temp);
		return FILE_ERROR_READ;
	}

	return FILE_ERROR_PERMISSIONS;
}

FileStatus fileWrite(const char *path, const char *data, unsigned offset)
{
	FILE *file;

	/**
	 * Open file for writing. If doesn't exist
	 * create a new file.
	 */
	if ((file = fopen(path, "rb+")) && (file = fopen(path, "wb"))) {
		unsigned length = strlen(data);
		fseek(file, offset, SEEK_SET);

		if (fwrite(data, sizeof(char), length, file) != length) {
			fclose(file);
			return FILE_SUCCESS;
		}

		fclose(file);
		return FILE_ERROR_READ;
	}

	return FILE_ERROR_PERMISSIONS;
}

FileStatus fileAppend(const char *path, const char *data)
{
	FILE *file;

	/**
	 * Open file for appending.
	 */
	if (file = fopen(path, "ab")) {
		unsigned length = strlen(data);

		if (fwrite(data, sizeof(char), length, file) == length) {
			fclose(file);
			return FILE_SUCCESS;
		}

		fclose(file);
		return FILE_ERROR_READ;
	}

	return FILE_ERROR_PERMISSIONS;
}

int fileBinaryRead(const char *path, uint8_t **data)
{
	FILE *file;

	/**
	 * Open file for reading.
	 */
	if (file = fopen(path, "rb")) {
		/**
		 * Get file length.
		 */
		fseek(file, 0, SEEK_END);
		int length = ftell(file);
		fseek(file, 0, SEEK_SET);

		/**
		 * Allocate memory to store file.
		 */
		char *temp = malloc(length * sizeof(uint8_t));

		/**
		 * Copy file to memory buffer.
		 */
		if (fread(temp, sizeof(uint8_t), length, file) == length) {
			/**
			 * On success, return the data to the pointer.
			 */
			*data = temp;
			fclose(file);
			return length;
		}

		fclose(file);
		free(temp);
		return FILE_ERROR_READ;
	}

	return FILE_ERROR_PERMISSIONS;
}

FileStatus fileBinaryWrite(const char *path, const uint8_t *data, unsigned offset, unsigned length)
{
	FILE *file;

	/**
	 * Open file for writing. If doesn't exist
	 * create a new file.
	 */
	if ((file = fopen(path, "rb+")) || (file = fopen(path, "wb"))) {
		fseek(file, offset, SEEK_SET);

		if (fwrite(data, sizeof(uint8_t), length, file) == length) {
			fclose(file);
			return FILE_SUCCESS;
		}

		fclose(file);
		return FILE_ERROR_READ;
	}

	return FILE_ERROR_PERMISSIONS;
}

FileStatus fileBinaryAppend(const char *path, const uint8_t *data, unsigned length)
{
	FILE *file;

	/**
	 * Open file for appending.
	 */
	if (file = fopen(path, "ab")) {
		if (length == fwrite(data, sizeof(uint8_t), length, file)) {
			fclose(file);
			return FILE_SUCCESS;
		}

		fclose(file);
		return FILE_ERROR_READ;
	}

	return FILE_ERROR_PERMISSIONS;
}