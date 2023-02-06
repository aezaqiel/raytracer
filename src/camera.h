#ifndef __CAMERA__
#define __CAMERA__

#include <cglm/cglm.h>

#include "ray.h"

typedef struct {
    vec3 origin;
    vec3 horizontal;
    vec3 vertical;
    vec3 offset_origin;
} camera;

camera camera_init(float aspect_ratio);
ray camera_ray(camera* cam, vec2 coord);

#endif // __CAMERA__