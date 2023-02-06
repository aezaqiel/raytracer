#include "ray.h"

ray ray_init(vec3 origin, vec3 direction)
{
    ray r = {0};

    glm_vec3_copy(origin, r.origin);
    glm_vec3_normalize_to(direction, r.direction);

    return r;
}

void ray_at(ray* r, float t, vec3 dest)
{
    glm_vec3_scale(r->direction, t, dest);
    glm_vec3_add(r->origin, dest, dest);
}