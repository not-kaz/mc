#ifndef COMMON_H
#define COMMON_H

#define UNUSED(x) ((void)(x))
#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))
#define FOR_RANGE(x, rng) for (int (x) = (-rng); (x) <= (rng); (x++))

#endif
