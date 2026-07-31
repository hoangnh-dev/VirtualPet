#ifndef SCR_PET_H
#define SCR_PET_H
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "screens_bitmap.h"
#include "sprite_frame_t.h"

typedef enum {
    PET_ACTION_IDLE,
    PET_ACTION_EAT,
    PET_ACTION_SLEEP,
    PET_ACTION_HAPPY,
    PET_ACTION_DISLIKE
} pet_action_t;

typedef enum {
    PET_EVENT_NONE,
    PET_EVENT_HATCH,
    PET_EVENT_EVOLVE
} pet_event_t;

typedef enum {
    PET_TYPE_EGG = 0,
    PET_TYPE_CHILD,
    PET_TYPE_ADULT         
} pet_type_t;

typedef struct {
    pet_type_t type;
    bool visible;
    uint8_t animation_check;
    uint8_t hunger;
    uint32_t lifetime;
    pet_action_t action;
    pet_event_t event;
    sprite_frame_t current_frame;
} pet_t;

extern pet_t pet;

void pet_setup();
void pet_update();
void pet_time();

#endif // SCR_PET_H