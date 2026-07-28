#ifndef PET_FRAME_T_H
#define PET_FRAME_T_H

#include <stdint.h>

typedef struct {
    uint32_t x, y,w,h;
    const uint8_t *bitmap;
} pet_frame_t;

#endif