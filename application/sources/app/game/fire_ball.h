#ifndef FIRE_BALL_H
#define FIRE_BALL_H

#include <stdbool.h>
#include <stdint.h>
#include "common.h"

#include "screens_bitmap.h"

#define MAX_FIRE        (5)

extern sprite_item_t fire[MAX_FIRE];

void fire_bal_update(void);

#endif