#ifndef __RAY__
#define __RAY__

#include <cglm/cglm.h>

typedef struct {
    vec3 origin;
    vec3 direction;
} ray;

ray ray_init(vec3 origin, vec3 direction);
void ray_at(ray* r, float t, vec3 dest);

#endif // __RAY__
