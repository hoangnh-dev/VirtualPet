#ifndef CLEAN_H
#define CLEAN_H

#include <stdbool.h>
#include <stdint.h>
#include "sprite_frame_t.h"
#include "screens_bitmap.h"

typedef struct {
    bool visible = false;
    uint8_t frame_index;
    sprite_frame_t current_frame;
} clean_t;

extern clean_t clean;

void clean_update(void);

#endif