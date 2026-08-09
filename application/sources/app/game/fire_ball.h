#ifndef FIRE_BALL_H
#define FIRE_BALL_H

#include <stdbool.h>
#include <stdint.h>
#include "common.h"

#include "screens_bitmap.h"

#define MAX_FIRE        (5)

typedef struct {
    bool visible = false;
    uint8_t frame_index;
    sprite_frame_t current_frame;
} fire_ball_t;

extern fire_ball_t fire[MAX_FIRE];

void fire_bal_update(void);

#endif