#include "scr_home.h"

static void view_scr_home();

view_dynamic_t dyn_view_home = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_home
};

view_screen_t scr_home = {
	&dyn_view_home,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void draw_sprite(const sprite_frame_t *frame){
    view_render.drawBitmap(frame->x,frame->y,frame->bitmap,frame->w,frame->h,WHITE);
}

void sleep_effect_display(){
	const sprite_frame_t *frame = pet_sleep_effect_get_frame();
	draw_sprite(frame);
}

void pet_display(){
    view_render.fillRect(46,15,48,54, BLACK);
    draw_sprite(&pet.current_frame);
	if (pet.type == PET_TYPE_EGG) return;
	if(pet.action == PET_ACTION_SLEEP && pet.animation_check == 1){
		sleep_effect_display();
	}
}
void food_display(){
	draw_sprite(&food.current_frame);
}
void poop_display(){
	draw_sprite(&poop.current_frame);
}

void view_scr_home() {
    view_render.clear();
    pet_display();
	if (food.visible) food_display();
	if (poop.visible) poop_display();
    view_render.setTextSize(0.1);
    view_render.setCursor(2,0);
	view_render.print("Food:");
    view_render.print(pet.satiety);
    view_render.setCursor(60,0);
	view_render.print("Health:");
    view_render.print(pet.health);
}

void scr_home_handle(ak_msg_t *msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
		BUZZER_PlaySound(BUZZER_SOUND_WELCOME);
		
		timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_EGG, AC_DISPLAY_EGG_INTERVAL, TIMER_PERIODIC);
		timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_PET_TIME_TICK, AC_DISPLAY_PET_TIME_TICK_INTERVAL, TIMER_PERIODIC);
		// timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_IDLE, AC_DISPLAY_IDLE_INTERVAL, TIMER_ONE_SHOT);
	} break;
		 
	case AC_DISPLAY_BUTTON_UP_PRESSED:
	case AC_DISPLAY_BUTTON_DOWN_PRESSED:{
		timer_remove_attr(AC_TASK_DISPLAY_ID,AC_DISPLAY_SHOW_EGG);
		timer_remove_attr(AC_TASK_DISPLAY_ID,AC_DISPLAY_PET_TIME_TICK);
		SCREEN_TRAN(scr_menu_handle, &scr_menu);
	}break;
	case AC_DISPLAY_SHOW_EGG:{
		task_post_pure_msg(VP_GAME_PET_ID, VP_GAME_PET_TICK);
		task_post_pure_msg(VP_GAME_POOP_ID, VP_GAME_POOP_TICK);
	} break;
	case AC_DISPLAY_PET_TIME_TICK:{
		task_post_pure_msg(VP_GAME_PET_ID, VP_GAME_PET_TIME);
	} break;

	default:
		break;
	}
}