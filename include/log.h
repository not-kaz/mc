#ifndef LOG_H
#define LOG_H

#define LOG(...) log_log(0, __FILE__, __LINE__, __VA_ARGS__);
#define DIE(...) log_log(1, __FILE__, __LINE__, __VA_ARGS__);

void log_log(int die, const char *file, int line, const char *fmt, ...);

#endif
