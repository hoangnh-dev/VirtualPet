#ifndef SPRITE_FRAME_H
#define SPRITE_FRAME_H

#include <stdint.h>

typedef struct {
    uint32_t x, y,w,h;
    const uint8_t *bitmap;
} sprite_frame_t;

#endif