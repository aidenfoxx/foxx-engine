#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <string.h>

#define LOG_NONE 0
#define LOG_NOTICE 1
#define LOG_ALERT 2
#define LOG_WARNING 4
#define LOG_ERROR 8
#define LOG_CRITICAL 16
#define LOG_ALL 255

void logSetLevel(unsigned int);
void logMessage(unsigned int, const char*);

#endif