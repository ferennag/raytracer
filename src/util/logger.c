#include <stdio.h>
#include "util/logger.h"

void log_debug(const char *msg) {
    printf("DEBUG - %s\n", msg);    
}

void log_info(const char *msg) {
    printf("INFO - %s\n", msg);
}

void log_warn(const char *msg) {
    printf("WARN - %s\n", msg);
}

void log_error(const char *msg) {
    printf("ERROR - %s\n", msg);
}

void log_fatal(const char *msg) {
    printf("FATAL - %s\n", msg);
}