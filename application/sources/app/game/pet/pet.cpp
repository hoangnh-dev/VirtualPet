#include "pet.h"
#include "pet_frames.h"
#include "pet_config.h"
#include <cstring>

pet_t pet;
uint8_t pet_reset_time = 0;
bool is_setup = false;

//  --------------Setup--------------
void pet_set_frame(const sprite_frame_t *frame){
    pet.current_frame = *frame; 
}

void pet_setup(){
    pet.animation_check = 0;
    pet.action = PET_ACTION_IDLE;
    pet.event = PET_EVENT_NONE;

    if (is_setup) return;

    pet.type = PET_TYPE_EGG;
    pet_set_frame(&egg_frames[0]);
    pet.satiety = 0;
    pet.health = 0;
    pet.poop = 0;
    pet.time.sleep_time = 0;
    pet.time.life_time =  0;
    pet.time.food_time = 0;
}
void pet_reset(){
    pet_reset_time ++;
    if (pet_reset_time >= 5){
        pet_reset_time = 0;
        pet.action = PET_ACTION_IDLE;
    }
}

//  --------------Time set--------------
bool pet_check_time(uint32_t *last_time, uint32_t interval){
    if ((pet.time.life_time - *last_time) >= interval) {
        *last_time = pet.time.life_time;
        return true;
    }
    return false;
}
void pet_time_update(uint32_t *last_time){
    *last_time = pet.time.life_time;
}
//  --------------Bitmmap set--------------

void child_update_bitmap(){
    switch (pet.action) {
        case PET_ACTION_EAT:{
                pet_set_frame(&child_eat_frames[pet.animation_check]);
            if(pet.animation_check == 1){
                task_post_pure_msg(VP_GAME_FOOD_ID, VP_GAME_FOOD_TICK);
            }
        }break;

        case PET_ACTION_DISLIKE:{
            pet_set_frame(&child_dislike_frames[pet.animation_check]);
            pet_reset();
        }break;

        case PET_ACTION_HAPPY:{
            pet_set_frame(&child_happy_frames[pet.animation_check]);
            pet_reset();
        }break;

        case PET_ACTION_ANNOY:{
            pet_set_frame(&child_annoying_frames[pet.animation_check]);
        }break;

        case PET_ACTION_SLEEP:{
            if (pet.health >= 100){
                pet.action = PET_ACTION_HAPPY;
                pet_time_update(&pet.time.sleep_time);
                return;
            }
            pet.health = pet.health + 5;
            pet_set_frame(&pet_sleep_frame);
        }break;

        case PET_ACTION_TRAIN:{
            pet_set_frame(&child_attack_frames[pet.animation_check]);
            if (pet.animation_check == 1){
                task_post_pure_msg(VP_GAME_FIRE_ID, VP_GAME_FIRE_START);
            }
        }
        break;

        default:{
            pet_set_frame(&child_frames[pet.animation_check]);
        }break;
    }
}
void pet_update_bitmap(){
    switch (pet.type) {
        case PET_TYPE_EGG:{
            pet_set_frame(&egg_frames[pet.animation_check]);
        }break;
        case PET_TYPE_CHILD:{
            child_update_bitmap();
        }break;
        default:
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
        case PET_EVENT_HATCH:{
            pet_set_frame(&egg_hatch_frame);
            pet.event = PET_EVENT_EVOLVE;
        }
        break;
        case PET_EVENT_EVOLVE:{
            pet_evolve();
        }break;
        default:
        break;
    }
}

void pet_update(){
    if (pet.event != PET_EVENT_NONE) {
        pet_event_update();
    } else {
        pet_animation_update();
    }
}

//  --------------Pet Action--------------

void pet_set_poop(){
    pet.action = PET_ACTION_ANNOY;
    pet.poop = 0;
    task_post_pure_msg(VP_GAME_POOP_ID, VP_GAME_POOP_SETUP);
}
void pet_satiety_reduce(){
    if (pet.type == PET_TYPE_EGG || pet.satiety == 0 || pet.action == PET_ACTION_EAT) {
        return;
    }

    if (pet_check_time(&pet.time.food_time, PET_EAT_TIME)) {
        pet.satiety--;
        pet.poop ++;
        if (pet.poop == 100){
            pet_set_poop();
        }
    }
}
void pet_health_reduce(){
    if (pet.type == PET_TYPE_EGG || pet.health == 0 || pet.action == PET_ACTION_SLEEP) {
        return;
    }

    if (pet_check_time(&pet.time.sleep_time, PET_SLEEP_TIME)) {
        pet.health--;
    }
}

void pet_eating(){
    pet.animation_check = 0;
    if(pet.satiety < 100 && pet.action == PET_ACTION_IDLE){
        pet.action = PET_ACTION_EAT;
        task_post_pure_msg(VP_GAME_FOOD_ID, VP_GAME_FOOD_SETUP);
    }else {
        pet.action = PET_ACTION_DISLIKE;
    }
}
void pet_sleep(){
    pet.animation_check = 0;
     if(pet.health < 100 && pet.action == PET_ACTION_IDLE){
        pet.action = PET_ACTION_SLEEP;
     }else {
        pet.action = PET_ACTION_DISLIKE;
     }
}
void pet_train(){
    pet.action = PET_ACTION_TRAIN;
    pet.animation_check = 0;
    pet_update_bitmap();
}

void pet_reject(){
    pet.action = PET_ACTION_DISLIKE;
};

//  --------------Time tick--------------
void pet_time(){
    pet.time.life_time++;

    if(pet.type == PET_TYPE_EGG && pet.time.life_time >= EGG_HATCH_TIME){
        pet.event = PET_EVENT_HATCH;
    }
    if (pet.type != PET_TYPE_EGG && pet.time.life_time % 10 == 0){
        task_post_pure_msg(VP_GAME_PROFILE_ID, VP_GAME_PROFILE_AGE);
    }

    pet_satiety_reduce();
    pet_health_reduce();
    
}
//  --------------Pet Msg--------------

void pet_finish(pet_finish_t reason){
    switch (reason) {
        case PET_FINISH_EAT:{
            pet.satiety = 100;
            pet_time_update(&pet.time.food_time);
        }break;

        case PET_FINISH_TRAIN:{
            if (pet.health >= 30) pet.health -= 30;
        }break;
        case PET_FINISH_SLEEP:
        case PET_FINISH_CLEAN:
        default:break;
    }      
}

void pet_task_handle(ak_msg_t *msg)
{
    switch (msg->sig) {
        case VP_GAME_PET_SETUP:{
            pet_setup();
        }
        break;
        case VP_GAME_PET_TICK:{
            pet_update();
        }
        break;
        case VP_GAME_PET_TIME:{
            pet_time();
        }
        break;
        case VP_GAME_PET_EAT:{
            pet_eating();
        }
        break;
        case VP_GAME_PET_SLEEP:{
            pet_sleep();
        }
        break;
        case VP_GAME_PET_TRAIN: {
            pet_train();
        }
        break;
        case VP_GAME_PET_REJECT: {
            pet_reject();
        }
        break;
        case VP_GAME_PET_FINISH:{
            pet_finish_t reason;
            memcpy(&reason, get_data_common_msg(msg), sizeof(reason));
            pet.action = PET_ACTION_HAPPY;
            pet_finish(reason);
        }
        break;
        
        default:
        break;
    }
}
//  --------------extension--------------
const sprite_frame_t *pet_sleep_effect_get_frame(){
    return &pet_sleep_effect_frame;
}
bool pet_check_free(){
    return (pet.action == PET_ACTION_IDLE || pet.action == PET_ACTION_ANNOY);
}