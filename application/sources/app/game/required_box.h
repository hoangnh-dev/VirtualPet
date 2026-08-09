#ifndef REQUIRED_BOX_H
#define REQUIRED_BOX_H

#include <stdbool.h>
#include <stdint.h>
#include "common.h"
#include "screens_bitmap.h"

#define MAX_BOX        (4)
#define MAX_TIME       (60)

typedef enum {
    BOX_RUNNING,        
    BOX_CORRECT,   
    BOX_WRONG     
} box_state_t;

typedef struct {
    bool visible = false;
    uint8_t count;
    uint8_t current_time;
    uint8_t renew_time = 5;
    uint8_t game_score;
    uint8_t frame_index[MAX_BOX];
    sprite_frame_t current_frame[MAX_BOX];
} required_box_t;

extern required_box_t box;

void box_update(void);
#endif