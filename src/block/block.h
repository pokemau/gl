#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "../gfx/vao.h"
#include "cglm/types.h"

typedef struct block {
    vec3 pos;
} block;

struct VAO block_create();

#endif
