#include "clean.h"
#include "home_action_config.h"

sprite_item_t clean;

void clean_setup(){
    clean.current_frame.x = CLEAN_X;
    clean.current_frame.y = CLEAN_Y;
    clean.current_frame.w = CLEAN_W;
    clean.current_frame.h = CLEAN_HE;
    clean.frame_index = 0;
    clean.current_frame.bitmap = bitmap_clean;
    clean.visible = true;
}

void clean_update_bitmap(){
    if(clean.current_frame.x >= LCD_WIDTH){
        clean.visible = false;
        return;
    }
    if (clean.current_frame.x == POOP_X){
        task_post_pure_msg(VP_GAME_POOP_ID, VP_GAME_POOP_CLEAN);
    }
    clean.current_frame.x += 10;
}

void clean_task_handle(ak_msg_t *msg){
    switch (msg->sig) {
        case VP_GAME_CLEAN_SETUP:{
            clean_setup();
        }
        break;
        case VP_GAME_CLEAN_TICK:{
            clean_update_bitmap();
        }break;
        default:
        break;
    }
}