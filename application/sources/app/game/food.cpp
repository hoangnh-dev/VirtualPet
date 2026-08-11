#include "food.h"
#include "task_list.h"

#define FOOD_X          (20)
#define FOOD_Y          (34)
#define FOOD_W          (21)
#define FOOD_HE         (21)

sprite_item_t food;

const uint8_t *const food_bitmaps[4] = {
    bitmap_food_1,
    bitmap_food_2,
    bitmap_food_3,
    bitmap_food_4,
};

void food_setup(){
    food.current_frame.x = FOOD_X;
    food.current_frame.y = FOOD_Y;
    food.current_frame.w = FOOD_W;
    food.current_frame.h = FOOD_HE;
    food.frame_index = 0;
    food.current_frame.bitmap = food_bitmaps[food.frame_index];
    food.visible = true;
}
void food_update_bitmap(){
    if (food.frame_index >= 3){
        food.visible = false;
        reason_t reason = PET_EAT;
        task_post_common_msg(VP_GAME_PET_ID, VP_GAME_PET_FINISH,(uint8_t*)&reason,sizeof(reason));
        // task_post_pure_msg(VP_GAME_PET_ID, VP_GAME_PET_FINISH);
        return;
    }
    food.frame_index ++;
    food.current_frame.bitmap = food_bitmaps[food.frame_index];
}

void food_task_handle(ak_msg_t *msg){
    switch (msg->sig) {
        case VP_GAME_FOOD_SETUP:
            food_setup();
        break;
        case VP_GAME_FOOD_TICK:
            food_update_bitmap();
        break;
        default:
        break;
    }
}