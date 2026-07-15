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

void view_scr_home() {
    view_render.clear();
    view_render.drawBitmap(	46, \
		25, \
		bitmap_egg, \
		31, \
		40, \
		WHITE);
    view_render.setTextSize(0.1);
    view_render.setCursor(2,0);
	view_render.print("Food:");
    view_render.print("100%");
    view_render.setCursor(60,0);
	view_render.print("Health:");
    view_render.print("100%");
}

void scr_home_handle(ak_msg_t *msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
		BUZZER_PlaySound(BUZZER_SOUND_WELCOME);
		timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_IDLE, AC_DISPLAY_IDLE_INTERVAL, TIMER_ONE_SHOT);
	} break;
		 
	case AC_DISPLAY_BUTTON_UP_PRESSED:
	case AC_DISPLAY_BUTTON_DOWN_PRESSED:{
		SCREEN_TRAN(scr_menu_handle, &scr_menu);
	}break;
	default:
		break;
	}
}