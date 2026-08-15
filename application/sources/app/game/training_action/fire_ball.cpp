#include "fire_ball.h"
#include "training_action_config.h"

sprite_item_t fire[MAX_FIRE];
uint8_t fire_index = 0;

const uint8_t *const fire_bitmaps[2] = {
    bitmap_fire_ball_1,
    bitmap_fire_ball_2,
};

void fire_setup(){
    for (uint8_t i = 0; i < MAX_FIRE; i++) {
        fire[i].visible = false;
        fire[i].current_frame.x = FIRE_X;
        fire[i].current_frame.y = FIRE_Y;
        fire[i].current_frame.w = FIRE_W;
        fire[i].current_frame.h = FIRE_HE;
        fire[i].frame_index = 0;
        fire[i].current_frame.bitmap = fire_bitmaps[fire[i].frame_index];
    }
}

void fire_update_bitmap(sprite_item_t* fire_ball){
    if(fire_ball->current_frame.x >= LCD_WIDTH){
        fire_ball->visible = false;
        return;
    }
    fire_ball->current_frame.x += 10;
    fire_ball->frame_index = !fire_ball->frame_index;
    fire_ball->current_frame.bitmap = fire_bitmaps[fire_ball->frame_index];
}

void fire_update(){
    for (uint8_t i = 0; i < MAX_FIRE; i++) {
        if (!fire[i].visible) continue;
        fire_update_bitmap(&fire[i]);
    }
}
void fire_start(){
    fire[fire_index].visible = true;
    fire[fire_index].current_frame.x = FIRE_X;
    fire[fire_index].frame_index = 0;
    fire_index = (fire_index +1) % MAX_FIRE;
}

void fire_task_handle(ak_msg_t *msg){
    switch (msg->sig) {
        case VP_GAME_FIRE_SETUP:{
            fire_setup();
        }break;
        case VP_GAME_FIRE_TICK:{
            fire_update();
        }break;
        case VP_GAME_FIRE_START:{
            BUZZER_PlaySound(BUZZER_SOUND_BANG);
            fire_start();
        }break;
        default:
        break;
    }
}