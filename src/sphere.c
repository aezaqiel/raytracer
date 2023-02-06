#include "sphere.h"

#include <math.h>

typedef struct {
    vec3 center;
    float radius;
} sphere_data;

bool sphere_hit(void* obj_data, ray* r, float t_min, float t_max, hit_record* record) {
    sphere_data* data = (sphere_data*)obj_data;

    vec3 oc;
    glm_vec3_sub(r->origin, data->center, oc);

    float a = glm_vec3_dot(r->direction, r->direction);
    float b = 2.0f * glm_vec3_dot(oc, r->direction);
    float c = glm_vec3_dot(oc, oc) - data->radius * data->radius;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0.0f) {
        return false;
    }

    float sqrtd = sqrtf(discriminant);
    float two_a = 2.0f * a;

    float root = (-b - sqrtd) / two_a;

    if (root < t_min || root > t_max) {
        root = (-b + sqrtd) / two_a;
        if (root < t_min || root > t_max) {
            return false;
        }
    }

    record->t = root;
    ray_at(r, root, record->p);
    glm_vec3_sub(record->p, data->center, record->normal);
    glm_vec3_divs(record->normal, data->radius, record->normal);

    set_face_normal(record, r);

    return true;
}

object sphere(vec3 center, float radius) {
    sphere_data* data = (sphere_data*)malloc(sizeof(sphere_data));
    glm_vec3_copy(center, data->center);
    data->radius = radius;

    object obj = {0};
    obj.hit = &sphere_hit;
    obj.data = (void*)data;

    return obj;
}