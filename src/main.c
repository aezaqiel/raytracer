#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "utilities.h"
#include "ray.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"

void glfw_error_callback(int32_t code, const char* description) {
    fprintf(stderr, "GLFW ERROR %d: %s\n", code, description);
}

void ray_colour(ray* r, hittable_list* world, vec3 colour) {
    hit_record record = {0};
    if (hittable_list_hit(world, r, 0.001f, FLT_MAX, &record)) {
        vec3 temp;
        glm_vec3_add(record.normal, (vec3){1.0f, 1.0f, 1.0f}, temp);
        glm_vec3_scale(temp, 0.5f, temp);
        glm_vec3_add(temp, colour, colour);
        return;
    }

    float t = 0.5f * (r->direction[1] + 1.0f);

    vec3 white = {1.0f, 1.0f, 1.0f};
    vec3 blue = {0.5f, 0.7f, 1.0f};

    glm_vec3_scale(white, 1.0f - t, white);
    glm_vec3_scale(blue, t, blue);

    vec3 temp;
    glm_vec3_add(white, blue, temp);
    glm_vec3_add(temp, colour, colour);
}

int main(void) {
    const uint32_t image_width = 480;
    const uint32_t image_height = 480;
    const uint32_t samples = 16;
    
    const char* image_path = "image.png";

    printf("render specification:\n");
    printf("    resolution: %dx%d\n", image_width, image_height);
    printf("    samples: %d\n", samples);

    float aspect_ratio = (float)image_width / (float)image_height;
    camera cam = camera_init(aspect_ratio);

    hittable_list world = {0};
    hittable_list_add(&world, sphere((vec3){0.0f, 0.0f, -1.0f}, 0.5f));
    hittable_list_add(&world, sphere((vec3){0.0f, -100.5f, -1.0f}, 100.0f));

    uint8_t* bitmap = (uint8_t*)calloc(image_width * image_height * 3, sizeof(uint8_t));

    for (uint32_t j = 0; j < image_height; j++) {
        printf("scanlines: [%d/%d]\r", j+1, image_height);
        fflush(stdout);
        for (uint32_t i = 0; i < image_width; i++) {
            vec3 colour = {0};
            for (uint32_t s = 0; s < samples; s++) {
                float u = (float)(i + randf()) / (float)(image_width - 1);
                float v = (float)(j + randf()) / (float)(image_height - 1);

                vec2 coord = {u, v};

                ray r = camera_ray(&cam, coord);

                ray_colour(&r, &world, colour);
            }

            glm_vec3_divs(colour, (float)samples, colour);
            glm_vec3_clamp(colour, 0.0f, 1.0f);

            glm_vec3_sqrt(colour, colour);

            uint32_t index = (i + j * image_width) * 3;

            bitmap[index + 0] = (uint8_t)(colour[0] * 255.0f);
            bitmap[index + 1] = (uint8_t)(colour[1] * 255.0f);
            bitmap[index + 2] = (uint8_t)(colour[2] * 255.0f);
        }
    }
    printf("\n");

    stbi_flip_vertically_on_write(1);
    if (stbi_write_png(image_path, image_width, image_height, 3, bitmap, image_width * 3) == 1) {
        printf("image saved to %s\n", image_path);
    }

    glfwSetErrorCallback(glfw_error_callback);
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(image_width, image_height, "raytracer", NULL, NULL);
    glfwMakeContextCurrent(window);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawPixels(image_width, image_height, GL_RGB, GL_UNSIGNED_BYTE, bitmap);
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    hittable_list_cleanup(&world);

    free(bitmap);

    glfwDestroyWindow(window);
    glfwTerminate();

    return(0);
}
