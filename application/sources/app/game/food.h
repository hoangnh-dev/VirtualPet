#ifndef FOOD_H
#define FOOD_H

#include <stdbool.h>
#include <stdint.h>
#include "sprite_frame_t.h"
#include "screens_bitmap.h"

typedef struct {
    bool visible;
    uint8_t frame_index;
    sprite_frame_t current_frame;
} food_t;

extern food_t food;

void food_update(void);

#endif