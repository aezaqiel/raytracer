#include "hittable_list.h"

void hittable_list_add(hittable_list* list, object obj) {
    list->count++;
    list->list = realloc(list->list, list->count * sizeof(object));
    list->list[list->count - 1] = obj;
}

bool hittable_list_hit(hittable_list* list, ray* r, float t_min, float t_max, hit_record* record) {
    hit_record temp_record = {0};
    bool hit_anything = false;
    float closest = t_max;

    for (uint32_t i = 0; i < list->count; i++) {
        object obj = list->list[i];
        if (obj.hit(obj.data, r, t_min, closest, &temp_record)) {
            hit_anything = true;
            closest = temp_record.t;
            *record = temp_record;
        }
    }

    return hit_anything;
}

void hittable_list_cleanup(hittable_list* list) {
    for (uint32_t i = 0; i < list->count; i++) {
        free(list->list[i].data);
    }
    free(list->list);
}