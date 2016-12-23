#ifndef TOOLS_LOG_H
#define TOOLS_LOG_H

#include <stdio.h>
#include <string.h>

#define LOG_NONE 0
#define LOG_NOTICE 1
#define LOG_ALERT 2
#define LOG_WARNING 4
#define LOG_ERROR 8
#define LOG_CRITICAL 16
#define LOG_ALL 255

void logSetLevel(int);
void logMessage(int, const char*);

#endif