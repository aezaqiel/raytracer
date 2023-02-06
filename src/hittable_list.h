#ifndef __HITTABLE_LIST__
#define __HITTABLE_LIST__

#include <stdint.h>
#include <stdbool.h>
#include "hittable.h"

typedef struct {
    uint32_t count;
    object* list;
} hittable_list;

void hittable_list_cleanup(hittable_list* list);

void hittable_list_add(hittable_list* list, object obj);
bool hittable_list_hit(hittable_list* list, ray* r, float t_min, float t_max, hit_record* record);

#endif // __HITTABLE_LIST__