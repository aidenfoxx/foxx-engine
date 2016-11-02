#include "Tools/log.h"

static unsigned int logLevel = LOG_ALL;

void logSetLevel(unsigned int level)
{
	logLevel = level;
}

void logMessage(unsigned int code, const char *message)
{
	char logLine[256];

	switch (code & logLevel)
	{
		case LOG_NOTICE:
			snprintf(logLine, 256, "NOTICE: %s", message);
			break;

		case LOG_ALERT:
			snprintf(logLine, 256, "ALERT: %s", message);
			break;

		case LOG_WARNING:
			snprintf(logLine, 256, "WARNING: %s", message);
			break;

		case LOG_ERROR:
			snprintf(logLine, 256, "ERROR:  %s", message);
			break;

		case LOG_CRITICAL:
			snprintf(logLine, 256, "CRITICAL: %s", message);
			break;

		default:
			snprintf(logLine, 256, "%s", message);
			break;
	}

	printf("%s\n", logLine);

	FILE *logFile = fopen("logs/log.txt", "a");

	if (logFile)
	{
		fprintf(logFile, "%s\n", logLine);
	}

	fclose(logFile);
}