#include "log.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static struct tm *read_time(void)
{
	time_t t;
	struct tm *tm;

	t = time(NULL);
	tm = localtime(&t);
	return tm;
}

void log_log(int die, const char *file, int line, const char *fmt, ...)
{
	FILE *fp;
	size_t len;
	char time[32];
	va_list args;

	fp = stderr;
	len = strftime(time, sizeof(time), "%H:%M:%S", read_time());
	time[len] = '\0';
	va_start(args, fmt);
	fprintf(fp, "%s %s:%d: ", time, file, line);
	vfprintf(fp, fmt, args);
	fprintf(fp, "\n");
	fflush(fp);
	va_end(args);
	if (die) {
		exit(EXIT_FAILURE);
	}
}
