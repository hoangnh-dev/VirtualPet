#include "scr_training.h"

static void view_scr_training();

view_dynamic_t dyn_view_training = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_training
};

view_screen_t scr_training = {
	&dyn_view_training,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};
void draw_spritet(const sprite_frame_t *frame){
    view_render.drawBitmap(frame->x,frame->y,frame->bitmap,frame->w,frame->h,WHITE);
}
void scr_training_Pet_display(){
    if (pet.action != PET_ACTION_TRAIN) return;
    draw_spritet(&pet.current_frame);
}
void scr_training_box_display(){
    if (!box.visible) return;

    for (uint8_t i = 0; i < box.count; i++) {
        raw_spritet(&box.current_frame[i]);
    }
}
void scr_training_fire_ball_display(){
    for (auto &f : fire) {
        if(f.visible) draw_spritet(&f.current_frame);
    }
}
void scr_training_text_display(){
    view_render.setTextSize (1);

    view_render.setCursor(2,0);
	view_render.print("Time:");
    view_render.print(box.current_time);

    view_render.setCursor(60,0);
    view_render.print("Score:");
    view_render.print(box.game_score);

    view_render.setCursor(2,55);
    view_render.print("Refresh:");
    view_render.print(box.renew_time);
}
void view_scr_training() {
    view_render.clear();
    scr_training_text_display();
    scr_training_Pet_display();
    scr_training_fire_ball_display();
    scr_training_box_display();
}

void scr_training_handle(ak_msg_t *msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
        timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_BOX, AC_DISPLAY_GAME_TICK_INTERVAL, TIMER_PERIODIC);
        timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_TRAIN_TIME_TICK, AC_DISPLAY_PET_TIME_TICK_INTERVAL, TIMER_PERIODIC);
		BUZZER_PlaySound(BUZZER_SOUND_WELCOME);
	} break;
    case AC_DISPLAY_SHOW_BOX: {
		task_post_pure_msg(VP_GAME_BOX_ID, VP_GAME_BOX_TICK);
        task_post_pure_msg(VP_GAME_FIRE_ID, VP_GAME_FIRE_TICK);
	} break;
    case AC_DISPLAY_TRAIN_TIME_TICK: {
		task_post_pure_msg(VP_GAME_BOX_ID, VP_GAME_BOX_TIME_TICK);
        task_post_pure_msg(VP_GAME_PET_ID, VP_GAME_PET_TICK);
	} break;
    case AC_DISPLAY_BUTTON_UP_PRESSED:{
        uint8_t input = 0;
        task_post_common_msg(VP_GAME_BOX_ID, VP_GAME_BOX_TAP,(uint8_t*)&input,1);
        break;
	}
	case AC_DISPLAY_BUTTON_DOWN_PRESSED:{
        uint8_t input = 1;
        task_post_common_msg(VP_GAME_BOX_ID, VP_GAME_BOX_TAP,(uint8_t*)&input,1);
        break;
	}
    case AC_DISPLAY_TRAIN_FINISH: {
        pet.action = PET_ACTION_IDLE;
		timer_remove_attr(AC_TASK_DISPLAY_ID,AC_DISPLAY_SHOW_BOX);
		timer_remove_attr(AC_TASK_DISPLAY_ID,AC_DISPLAY_TRAIN_TIME_TICK);
        task_post_pure_msg(VP_GAME_FIRE_ID, VP_GAME_FIRE_SETUP);
        task_post_common_msg(VP_GAME_PROFILE_ID, VP_GAME_PROFILE_POWER,(uint8_t*)&box.game_score,sizeof(box.game_score));
        pet_finish_t reason = PET_FINISH_TRAIN;
        task_post_common_msg(VP_GAME_PET_ID, VP_GAME_PET_FINISH,(uint8_t*)&reason,sizeof(reason));
        SCREEN_TRAN(scr_home_handle, &scr_home);
	} break;
	default:
		break;
	}
}