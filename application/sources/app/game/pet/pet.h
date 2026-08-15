#ifndef SCR_PET_H
#define SCR_PET_H

#include "common.h"

const sprite_frame_t *pet_sleep_effect_get_frame();
extern pet_t pet;
extern bool is_setup;

void pet_setup();
void pet_update();
void pet_time();
bool pet_check_free();

#endif // SCR_PET_H