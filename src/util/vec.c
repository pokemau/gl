#include "vec.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    unsigned int capacity;
    unsigned int count;
    size_t element_size;
} vec_info;

void vec_init(void *list, unsigned int capacity, size_t element_size) {
    vec_info *self = malloc(sizeof(vec_info) * (capacity * element_size));

    if (self == NULL) {
        printf("ERROR VEC_INIT");
        exit(1);
    }

    *((void**) list) = self + 1;
    self->capacity = capacity;
    self->count = 0;
    self->element_size = element_size;
}

void vec_add(void* list, const void* _value) {
    vec_info* info = ((vec_info*)(*((void**)list))) - 1;

    if (info->count >= info->capacity)
    {
        info->capacity = info->capacity * 1.5;

        info = realloc( info,
            sizeof(vec_info) + (info->capacity * info->element_size)
        );

        if (info == NULL)
        {
            printf("vec failed to realloc\n");
        }

        // if realloc moved the memory then we need to change where the _refList is pointing
        *((void**)list) = info + 1;
    }

    memcpy(
        (*(char**)list + (info->count * info->element_size)),
        _value,
        info->element_size
    );

    info->count++;
}
