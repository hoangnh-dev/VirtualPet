#ifndef PET_PROFILE_H
#define PET_PROFILE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <cstring>

#include "screens_bitmap.h"

#define NAME_LEN          (5)

typedef struct {
    char name[NAME_LEN + 1];
    uint16_t weight;
    uint16_t height;
    uint16_t age;
    uint16_t power;
} pet_profile_t;

extern pet_profile_t profile;
extern uint8_t name_index;

#endif