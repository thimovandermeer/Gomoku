//
// Created by Jonas Bennink Bolt on 2/3/23.
//

#ifndef GOMOKU_LOGGER_HPP
#define GOMOKU_LOGGER_HPP

#define MAX_LOG_SIZE 1024
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
void log_func(const char* file, const char* func, int line, const char* fmt, ...);
#define LOG(fmt, ...) log_func(__FILENAME__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)


#endif //GOMOKU_LOGGER_HPP
