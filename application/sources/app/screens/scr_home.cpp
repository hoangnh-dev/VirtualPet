#include "scr_home.h"

static void view_scr_home();
static void egg_display();

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

void view_scr_home() {
    view_render.clear();
    egg_display();
    view_render.setTextSize(0.1);
    view_render.setCursor(2,0);
	view_render.print("Food:");
    view_render.print("100%");
    view_render.setCursor(60,0);
	view_render.print("Health:");
    view_render.print("100%");
}
void egg_display(){
	view_render.fillRect(Egg_MAX_X, Egg_H, Egg_MAX_W, Egg_H ,BLACK);

	view_render.drawBitmap(	pet.x, \
		pet.y, \
		pet.bitmap, \
		pet.w, \
		pet.h, \
		WHITE);
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
		SCREEN_TRAN(scr_menu_handle, &scr_menu);
	}break;
	case AC_DISPLAY_SHOW_EGG:{
		pet_update();
		egg_display();
		if(egg_state == EGG_STATE_HATCH){
			timer_remove_attr(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_EGG);
		}
	} break;
	case AC_DISPLAY_PET_TIME_TICK:{
		pet_time();
	} break;

	default:
		break;
	}
}