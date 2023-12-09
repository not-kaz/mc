#ifndef COMMON_H
#define COMMON_H

#include <assert.h>

#define ASSERT(expr) assert((expr))
#define UNUSED(x) ((void)(x))
#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

#endif
