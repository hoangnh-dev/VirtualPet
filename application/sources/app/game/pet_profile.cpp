#include "pet_profile.h"

#define BASIC_HEIGHT          (20)
#define BASIC_WEIGHT          (2)
#define CHAR_TABLE_LEN        (26)

typedef enum {
    CHAR_UP = 0,
    CHAR_DOWN,
    CHAR_NEXT,
} button_action_t;

typedef enum {
    STAT_WEIGHT = 0,
    STAT_HEIGHT,
} stat_type_t;

const char char_table[] = "abcdefghijklmnopqrstuvwxyz";
uint8_t char_index = 0;

pet_profile_t profile;
uint8_t name_index;

void pet_profile_update_name(){
    profile.name[name_index] = char_table[char_index];
}

void pet_profile_setup(){
    name_index = 0;
    memset(profile.name, '_', NAME_LEN);
    profile.name[NAME_LEN] = '\0';
    profile.weight = BASIC_WEIGHT;
    profile.height = BASIC_HEIGHT;
    profile.age = 0;
    profile.power = 0;
    
    pet_profile_update_name();
}

void pet_profile_char_up(){
    if (char_index == 0){
        char_index = CHAR_TABLE_LEN - 1;
    }else{
        char_index --;
    }
}
void pet_profile_char_down(){
    char_index = (char_index + 1) % CHAR_TABLE_LEN;
}
void pet_profile_char_next(){
    name_index ++;
    char_index = 0;
    pet_profile_update_name();
}

void pet_profile_scroll_char(button_action_t direction){
    switch (direction){
        case CHAR_UP:{
            pet_profile_char_up();
        } break;
        case CHAR_DOWN:{
            pet_profile_char_down();
        } break;
        case CHAR_NEXT:{
            pet_profile_char_next();
        } break;
        default:
		break;
    }
}
void set_weight(){
    profile.weight = BASIC_WEIGHT + (profile.age/5);
}
void set_height(){
    profile.height = BASIC_HEIGHT + (profile.age/10);
}
void set_age(){
    profile.age ++;
    set_height();
    set_weight();
}
void set_power(uint8_t point){
    profile.power += point;
}
void profile_task_handle(ak_msg_t *msg){
    switch (msg->sig) {
        case VP_GAME_PROFILE_SETUP:{
            pet_profile_setup();
        } break;
        case VP_GAME_PROFILE_TICK:{
            pet_profile_update_name();
        } break;
        case VP_GAME_PROFILE_BUTTON:{
            button_action_t button;
            memcpy(&button, get_data_common_msg(msg), 1);
            pet_profile_scroll_char(button);
        } break;
        case VP_GAME_PROFILE_AGE:{
            set_age();
        } break;
        case VP_GAME_PROFILE_POWER:{
            uint8_t point;
            memcpy(&point, get_data_common_msg(msg), sizeof(point));
            set_power(point);
        } break;
        default:
		break;
    }
}