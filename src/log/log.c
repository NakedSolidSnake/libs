#include <log/log.h>
#include <syslog.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>


int logger(int logType, const char *module, const char *logMessage)
{
  openlog(module, LOG_PID | LOG_CONS , LOG_USER);
  syslog(logType, logMessage);
  closelog();
  return EXIT_SUCCESS;
}

int loggerArgs(int logType, const char *module, const char *logMessage, ...)
{
  char buffer[MAX_BUF] = {0};
  va_list args;
  va_start(args, logMessage);
  vsprintf(buffer, logMessage, args);
  va_end(args);

  return logger(LOG_INFO, module, buffer);
}
