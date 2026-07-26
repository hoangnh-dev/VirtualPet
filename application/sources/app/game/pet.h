#ifndef SCR_PET_H
#define SCR_PET_H
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "screens_bitmap.h"

#define EGG_X          (46)
#define EGG_MAX_X      (40)
#define EGG_W          (36)
#define EGG_MAX_W      (48)
#define EGG_MAX_H      (39)
#define EGG_H          (33)
#define EGG_Y          (20)
#define EGG_MAX_Y      (26)

#define Child_X        (46)
#define Child_W        (30)
#define Child_MAX_H    (27)
#define Child_H        (24)
#define Child_Y        (28)
#define Child_MAX_Y    (31)

typedef enum {
    PET_ACTION_NONE,
    PET_ACTION_HATCH,
    PET_ACTION_TRAN
} pet_action_t;

typedef enum {
    PET_TYPE_EGG = 0,
    PET_TYPE_CHILD,
    PET_TYPE_ADULT         
} pet_type_t;

typedef struct {
    pet_type_t type;
    bool visible;
    uint32_t x, y,h,w;
    uint8_t animation_check;
    const uint8_t *bitmap;
    uint32_t lifetime;
    pet_action_t action;
} pet_t;

extern pet_t pet;

void pet_setup();
void pet_update();
void pet_time();

#endif // SCR_PET_H