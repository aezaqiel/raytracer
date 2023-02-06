#include "camera.h"

camera camera_init(float aspect_ratio) {
    camera cam = {0};

    float viewport_height = 2.0f;
    float viewport_width = viewport_height * aspect_ratio;
    float focal_length = 1.0f;

    glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, cam.origin);
    glm_vec3_copy((vec3){viewport_width, 0.0f, 0.0f}, cam.horizontal);
    glm_vec3_copy((vec3){0.0f, viewport_height, 0.0f}, cam.vertical);

    vec3 depth = {0.0f, 0.0f, focal_length};

    vec3 half_horizontal;
    glm_vec3_scale(cam.horizontal, 0.5f, half_horizontal);

    vec3 half_vertical;
    glm_vec3_scale(cam.vertical, 0.5f, half_vertical);

    glm_vec3_sub(cam.origin, half_horizontal, cam.offset_origin);
    glm_vec3_sub(cam.offset_origin, half_vertical, cam.offset_origin);
    glm_vec3_sub(cam.offset_origin, depth, cam.offset_origin);

    return cam;
}

ray camera_ray(camera* cam, vec2 coord) {
    vec3 horizontal_offset;
    glm_vec3_scale(cam->horizontal, coord[0], horizontal_offset);

    vec3 vertical_offset;
    glm_vec3_scale(cam->vertical, coord[1], vertical_offset);

    vec3 offset;
    glm_vec3_add(cam->offset_origin, horizontal_offset, offset);
    glm_vec3_add(offset, vertical_offset, offset);
    glm_vec3_sub(offset, cam->origin, offset);

    return ray_init(cam->origin, offset);
}