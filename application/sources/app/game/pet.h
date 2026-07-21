#ifndef SCR_PET_H
#define SCR_PET_H
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "screens_bitmap.h"

#define Pet_X         (46)
#define Egg_MAX_Y     (25)
#define Pet_W         (32)
#define Egg_Max_H     (40)
#define Egg_H         (35)
#define Egg_Y         (30)

typedef enum {
    EGG_STATE_IDLE,
    EGG_STATE_BOUNCE,
    EGG_STATE_HATCH
} egg_state_t;

typedef enum {
    PET_TYPE_EGG = 0,
    PET_TYPE_CHILD,
    PET_TYPE_ADULT         
} pet_type_t;

typedef struct {
    pet_type_t type;
    bool visible;
    uint32_t x, y,h,w;
    const uint8_t *bitmap;
} pet_t;

extern egg_state_t egg_state;
extern pet_t pet;

void pet_setup();
void pet_update();



#endif // SCR_PET_H