#ifndef __UTILITIES__
#define __UTILITIES__

#include <stdlib.h>

static inline float randf() {
    return (float)rand() / (float)(RAND_MAX);
}

static inline float randf_range(float min, float max) {
    return min + (max - min) * randf();
}

static inline float clampf(float x, float min, float max) {
    x = x < min ? min : x;
    x = x > max ? max : x;

    return x;
}

#endif // __UTILITIES__