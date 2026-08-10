#include "pet_profile.h"

#define BASIC_HEIGHT          (20)
#define BASIC_WEIGHT          (2)
#define CHAR_TABLE_LEN        (26)

enum {
    CHAR_UP = 0,
    CHAR_DOWN,
    CHAR_NEXT,        
};

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
    profile.weight = BASIC_HEIGHT;
    profile.height = BASIC_HEIGHT;
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

void pet_profile_scroll_char(uint8_t direction){
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
void profile_task_handle(ak_msg_t *msg){
    switch (msg->sig) {
        case VP_GAME_PROFILE_SETUP:{
            pet_profile_setup();
        } break;
        case VP_GAME_PROFILE_TICK:{
            pet_profile_update_name();
        } break;
        case VP_GAME_PROFILE_BUTTON:{
            uint8_t button;
            memcpy(&button, get_data_common_msg(msg), 1);
            pet_profile_scroll_char(button);
        } break;
        default:
		break;
    }
}