#include "pet.h"
#include "pet_frames.h"
#include "pet_config.h"
#define EGG_HATCH_TIME (8)

pet_t pet;

void pet_set_frame(const sprite_frame_t *frame){
    pet.current_frame = *frame; 
}

void pet_setup(){
    pet.type = PET_TYPE_EGG;
    pet_set_frame(&egg_frames[0]);
    pet.animation_check = 0;
    pet.action = PET_ACTION_IDLE;
    pet.event = PET_EVENT_NONE; 
}
void child_update_bitmap(){
    switch (pet.action) {
        case PET_ACTION_EAT:
            pet_set_frame(&child_eat_frames[pet.animation_check]);
        break;

        case PET_ACTION_DISLIKE:
            pet_set_frame(&child_dislike_frames[pet.animation_check]);
        break;

        case PET_ACTION_HAPPY:
            pet_set_frame(&child_happy_frames[pet.animation_check]);
        break;

        default:
            pet_set_frame(&child_frames[pet.animation_check]);
        break;
    }
}
void pet_update_bitmap(){
    switch (pet.type) {
        case PET_TYPE_EGG:
            pet_set_frame(&egg_frames[pet.animation_check]);
        break;
        default:
            child_update_bitmap();
        break;
    }
}
void pet_animation_update(){
    pet.animation_check = !pet.animation_check;
    pet_update_bitmap();
}

void pet_evolve(){
    if (pet.type >= PET_TYPE_ADULT) return;
    pet.type = static_cast<pet_type_t>(pet.type + 1);
    pet.event = PET_EVENT_NONE;
    pet.action = PET_ACTION_IDLE;
    pet.animation_check = 0;
    pet_update_bitmap();
}

void pet_event_update(){
    switch (pet.event) {
        case PET_EVENT_HATCH:
            pet_set_frame(&egg_hatch_frame);
            pet.event = PET_EVENT_EVOLVE;
        break;
        case PET_EVENT_EVOLVE:
            pet_evolve();
        break;
        default:
        break;
    }
}
void pet_action_update(){
    switch (pet.action) {
        case PET_ACTION_IDLE:
            pet_animation_update();
        break;
        default:
        break;
    }
}
void pet_update(){
    if (pet.event != PET_EVENT_NONE) {
        pet_event_update();
    } else {
        pet_action_update();
    }
}
void pet_time(){
    pet.lifetime ++;
    if(pet.type == PET_TYPE_EGG && pet.lifetime >= EGG_HATCH_TIME){
        pet.event = PET_EVENT_HATCH;
    }
}
void pet_task_handle(ak_msg_t *msg)
{
    switch (msg->sig) {
        case VP_GAME_PET_SETUP:
            pet_setup();
        break;
        case VP_GAME_PET_TICK:
            pet_update();
        break;
        case VP_GAME_PET_TIME:
            pet_time();
        break;
        default:
        break;
    }
}