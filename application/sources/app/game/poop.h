#ifndef POOP_H
#define POOP_H

#include <stdbool.h>
#include <stdint.h>
#include "common.h"
#include "screens_bitmap.h"

typedef struct {
    bool visible = false;
    uint8_t frame_index;
    sprite_frame_t current_frame;
} poop_t;

extern poop_t poop;

void poop_update(void);
#endif