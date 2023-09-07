#include "common.h"

#include <stdlib.h>
#include <string.h>

char *str_duplicate(char *str)
{
	size_t len;
	void *new;

	len = strlen(str) + 1;
	new = malloc(len);
	if (!new) {
		return NULL;
	}
	return memcpy(new, str, len);
}

char *str_split(char **str_p, const char *delim)
{
	char *start, *end;

	start = *str_p;
	if (!start) {
		return NULL;
	}
	end = start + strcspn(start, delim);
	if (*end) {
		*end++ = '\0';
		*str_p = end;
	} else {
		*str_p = NULL;
	}
	return start;
}
