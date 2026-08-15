#include "poop.h"
#include "home_action_config.h"

sprite_item_t poop;

const uint8_t *const poop_bitmaps[2] = {
    bitmap_poop_1,
    bitmap_poop_2,
};

void poop_setup(){
    poop.current_frame.x = POOP_X;
    poop.current_frame.y = POOP_Y;
    poop.current_frame.w = POOP_W;
    poop.current_frame.h = POOP_HE;
    poop.frame_index = 0;
    poop.current_frame.bitmap = poop_bitmaps[poop.frame_index];
    poop.visible = true;
}

void poop_update_bitmap(){
    poop.frame_index = !poop.frame_index;
    poop.current_frame.bitmap = poop_bitmaps[poop.frame_index];
}

void poop_task_handle(ak_msg_t *msg){
    switch (msg->sig) {
        case VP_GAME_POOP_SETUP:{
            poop_setup();
        }break;
        case VP_GAME_POOP_TICK:{
            poop_update_bitmap();
        }break;
        case VP_GAME_POOP_CLEAN:{
            poop.visible = false;
            pet_finish_t reason = PET_FINISH_CLEAN;
            task_post_common_msg(VP_GAME_PET_ID, VP_GAME_PET_FINISH,(uint8_t*)&reason,sizeof(reason));
        }break;
        default:
        break;
    }
}