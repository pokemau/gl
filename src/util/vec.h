#ifndef _ARRAY_H_
#define _ARRAY_H_

// https://github.com/EricWRogers/c_vec

#include <stddef.h>

void vec_init(void *list, unsigned int capacity, size_t element_size);
void vec_add(void* list, const void* _value);
void vec_free(void *ref_list);


#endif
