#ifndef __LOG_H
#define __LOG_H

#define MAX_BUF         1024

#define LOGGER_INFO        0
#define LOGGER_WARNING     1
#define LOGGER_CRITICAL    2
#define LOGGER_FATAL       3

int logger(int logType, const char *module, const char *logMessage);
int loggerArgs(int logType, const char *module, const char *logMessage, ...);

#endif
