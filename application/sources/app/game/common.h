#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

typedef struct {
    uint32_t x, y,w,h;
    const uint8_t *bitmap;
} sprite_frame_t;

typedef enum {
    PET_EAT = 0,
    PET_CLEANED,
}reason_t;

#endif