#include "str.h"

#include <stdio.h>
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
	char *start;
	char *end;

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

char *str_read_file(const char *filename)
{
	FILE *fp;
	char *src;
	char buf;
	size_t len;

	fp = fopen(filename, "rb+");
	if (!fp) {
		return NULL;
	}
	fseek(fp, 0, SEEK_END);
	len = (size_t)(ftell(fp));
	fseek(fp, 0, SEEK_SET);
	src = calloc(len + 1, sizeof(char));
	if (!src) {
		fclose(fp);
		return NULL;
	}
	len = 0;
	while ((buf = (char)(fgetc(fp))) != EOF) {
		src[len] = buf;
		src[len + 1] = '\0';
		++len;
	}
	fclose(fp);
	return src;
}
