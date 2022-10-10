#ifndef LOGGER_H
#define LOGGER_H

void log_debug(const char *msg);
void log_info(const char *msg);
void log_warn(const char *msg);
void log_error(const char *msg);
void log_fatal(const char *msg);

#endif