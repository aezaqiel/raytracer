#ifndef __HITTABLE__
#define __HITTABLE__

#include <stdbool.h>

#include <cglm/cglm.h>

#include "ray.h"

typedef struct {
    vec3 p;
    vec3 normal;
    float t;
    bool front_face;
} hit_record;

static void set_face_normal(hit_record* record, ray* r) {
    record->front_face = glm_vec3_dot(r->direction, record->normal) < 0.0f;
    if (!record->front_face) {
        glm_vec3_negate(record->normal);
    }
}

typedef bool (*hit_fn)(void* data, ray* r, float t_min, float t_max, hit_record* record);

typedef struct {
    hit_fn hit;
    void* data;
} object;

#endif // __HITTABLE__