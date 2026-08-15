#ifndef COMMON_H
#define COMMON_H

#include "task_list.h"
#include <stdint.h>
/* ========================================================================== */
/*                            1. UTILITY TYPES                                */
/* ========================================================================== */

typedef struct {
    uint32_t x, y,w,h;
    const uint8_t *bitmap;
} sprite_frame_t;

typedef struct {
    bool visible;
    uint8_t frame_index;
    sprite_frame_t current_frame;
} sprite_item_t;

typedef enum {
    PET_FINISH_EAT = 0,
    PET_FINISH_SLEEP,
    PET_FINISH_CLEAN,
    PET_FINISH_TRAIN,
}pet_finish_t;

/* ========================================================================== */
/*                               2. PET TYPES                                 */
/* ========================================================================== */

typedef enum {
    PET_ACTION_IDLE,
    PET_ACTION_EAT,
    PET_ACTION_SLEEP,
    PET_ACTION_HAPPY,
    PET_ACTION_DISLIKE,
    PET_ACTION_ANNOY,
    PET_ACTION_TRAIN
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
    uint32_t life_time;
    uint32_t food_time;
    uint32_t sleep_time;
} pet_time_t;

typedef struct {
    pet_type_t type;
    bool visible;
    uint8_t animation_check;
    uint8_t satiety;
    uint8_t health;
    uint8_t poop;
    pet_time_t time;
    pet_action_t action;
    pet_event_t event;
    sprite_frame_t current_frame;
} pet_t;

// PET PROFILE
#define NAME_LEN          (5)

typedef struct {
    char name[NAME_LEN + 1];
    uint16_t weight;
    uint16_t height;
    uint16_t age;
    uint16_t power;
} pet_profile_t;

// PET DATA SAVE
typedef struct {
    pet_type_t type;
    uint8_t satiety;
    uint8_t health;
    uint8_t poop;
    pet_time_t time;
} pet_save_t;
typedef struct {
	uint32_t magic_number;
	pet_profile_t data_profile;
    pet_save_t data_pet;
	uint8_t check_sum;
} vp_game_eeprom_t;
/* ========================================================================== */
/*                               3. TRAINING BOX                              */
/* ========================================================================== */

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

#endif