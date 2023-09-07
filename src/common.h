#ifndef COMMON_H
#define COMMON_H

#define UNUSED(x) (void)(x)
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

char *str_duplicate(char *str);
char *str_split(char **str_p, const char *delim);

#endif
