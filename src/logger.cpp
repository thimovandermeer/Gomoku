//
// Created by Jonas Bennink Bolt on 2/3/23.
//
#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <sys/time.h>
#include "logger.hpp"

void log_func(const char* file, const char* func, int line, const char* fmt, ...) {
    char buf[MAX_LOG_SIZE];
    va_list varlist;
    va_start(varlist, fmt);
    vsnprintf(buf, MAX_LOG_SIZE, fmt, varlist);
    va_end(varlist);

    struct timeval t{};
    gettimeofday(&t, nullptr);
    struct tm *tm = localtime(&t.tv_sec);

    fprintf(stderr, "%02d:%02d:%02d.%03d| %s:%d: %s(): [%s]\n",
            tm->tm_hour, tm->tm_min, tm->tm_sec, (int)(t.tv_usec / 1000), file, line, func, buf);
}