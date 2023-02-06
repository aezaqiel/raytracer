#ifndef __SPHERE__
#define __SPHERE__

#include <stdbool.h>

#include <cglm/cglm.h>

#include "ray.h"
#include "hittable.h"

bool sphere_hit(void* obj_data, ray* r, float t_min, float t_max, hit_record* record);
object sphere(vec3 center, float radius);

#endif // __SPHERE__