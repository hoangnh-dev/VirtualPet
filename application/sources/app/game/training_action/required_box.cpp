#include "required_box.h"
#include "training_action_config.h"

required_box_t box;
uint8_t count_correct;

const uint8_t *const box_bitmaps[2] = {
    bitmap_train_arrow_up,
    bitmap_train_arrow_down,
};

void box_generate(){
    uint8_t minx = BOX_X - (box.count*BOX_W)/2;
    count_correct = 0;
    for (uint8_t i = 0; i < box.count; i++) {
        box.current_frame[i].x = minx + i * BOX_W;
        box.current_frame[i].y = BOX_Y;
        box.current_frame[i].w = BOX_W;
        box.current_frame[i].h = BOX_H;
        box.frame_index[i] = rand() % 2;
        box.current_frame[i].bitmap = box_bitmaps[box.frame_index[i]];
    }
}

void box_setup(){
    box.count = 1;
    box.current_time = MAX_TIME;
    box.renew_time = 5;
    box.game_score = 0;
    box_generate();
    box.visible = true;
}
void box_run(){
    if (box.renew_time > 0) return;
    if (box.count < MAX_BOX)box.count++;
    box.renew_time = 5;
    box_generate();
}
void box_correct(){
    box.current_frame[count_correct].bitmap = bitmap_check_mark;
    count_correct ++;
    if(count_correct == box.count) {
        box.game_score += 10;
        count_correct = 0;
        box.renew_time = 0;
    }
}
void box_wrong(){
    box.current_frame[count_correct].bitmap = bitmap_x_mark;
}

void time_update(){
    if(box.current_time > 0 ) box.current_time --;
    if(box.renew_time > 0 ) box.renew_time --;
    if(box.current_time == 0){
        box.visible = false;
        box.count = 1;
        task_post_pure_msg(AC_TASK_DISPLAY_ID, AC_DISPLAY_TRAIN_FINISH);
    }
}
bool box_check(uint8_t check){
    return box.frame_index[count_correct] == check;
}
void box_receiver(uint8_t button){
    if (box_check(button)){
        box_correct();
    }else {
        box_wrong();
    }
}

void box_task_handle(ak_msg_t *msg){
    switch (msg->sig) {
        case VP_GAME_BOX_SETUP:{
            box_setup();
        }break;
        case VP_GAME_BOX_TICK:{
            box_run();
        }break;
        case VP_GAME_BOX_TIME_TICK:{
            time_update();
        }break;
        case VP_GAME_BOX_TAP:{
            uint8_t button;
            memcpy(&button, get_data_common_msg(msg), 1);
            box_receiver(button);
        }break;
        default:
        break;
    }
}