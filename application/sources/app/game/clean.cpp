#include "clean.h"
#include "task_list.h"

#define CLEAN_X          (0)
#define CLEAN_Y          (16)
#define CLEAN_W          (18)
#define CLEAN_HE         (48)

clean_t clean;

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
    if(clean.current_frame.x >= 128){
        clean.visible = false;
        return;
    }
    if (clean.current_frame.x == 80){
        task_post_pure_msg(VP_GAME_POOP_ID, VP_GAME_POOP_CLEAN);
    }
    clean.current_frame.x += 10;
}

void clean_task_handle(ak_msg_t *msg){
    switch (msg->sig) {
        case VP_GAME_CLEAN_SETUP:
            clean_setup();
        break;
        case VP_GAME_CLEAN_TICK:
            clean_update_bitmap();
        break;
        default:
        break;
    }
}