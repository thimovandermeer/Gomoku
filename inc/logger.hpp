//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_LOGGER_HPP
#define GOMOKU_LOGGER_HPP

enum logLevel {
    LOG_DEBUG,
    LOG_WARN,
    LOG_ERROR
};

void setLogLevel(logLevel lvl);
#define MAX_LOG_SIZE 1024
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
void log_func(logLevel lvl, const char* file, const char* func, int line, const char* fmt, ...);
#define LOG(fmt, ...) log_func(LOG_DEBUG, __FILENAME__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define WARN(fmt, ...) log_func(LOG_WARN, __FILENAME__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define ERROR(fmt, ...) log_func(LOG_ERROR, __FILENAME__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)


#endif //GOMOKU_LOGGER_HPP
