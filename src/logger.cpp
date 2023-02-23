//
// Created by Jonas Bennink Bolt on 2/3/23.
//
#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <sys/time.h>
#include "logger.hpp"
#include <map>

#define CLR "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"

static const std::map<log_level, const char*> clrs = {
        {LOG_DEBUG, GREEN"DBG"},
        {LOG_WARN,  YELLOW"WRN"},
        {LOG_ERROR, RED"ERR"}
};

log_level currentLogLevel = LOG_DEBUG;

void setLogLevel(log_level lvl) {
    currentLogLevel = lvl;
}

void log_func(log_level lvl, const char* file, const char* func, int line, const char* fmt, ...) {
    if (lvl < currentLogLevel) {
        return;
    }
    char buf[MAX_LOG_SIZE];
    va_list varlist;
    va_start(varlist, fmt);
    vsnprintf(buf, MAX_LOG_SIZE, fmt, varlist);
    va_end(varlist);

    struct timeval t{};
    gettimeofday(&t, nullptr);
    struct tm* tm = localtime(&t.tv_sec);

    fprintf(stderr, "%s %02d:%02d:%02d.%03d| %s:%d: %s(): [%s]\n" CLR,
            clrs.at(lvl), tm->tm_hour, tm->tm_min, tm->tm_sec, (int)(t.tv_usec / 1000), file, line, func, buf);
}
