#include "src_splash.h"

static void view_scr_splash();

view_dynamic_t dyn_view_splash = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_splash
};

view_screen_t scr_splash = {
	&dyn_view_splash,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void view_scr_splash() {
    view_render.clear();
    view_render.drawBitmap(	0, \
		0, \
		bitmap_egg_splash, \
		119, \
		62, \
		WHITE);
}

void scr_splash_handle(ak_msg_t *msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
		BUZZER_PlaySound(BUZZER_SOUND_WELCOME);
		timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_HOME, AC_DISPLAY_STARTUP_INTERVAL, TIMER_ONE_SHOT);
	} break;
	case AC_DISPLAY_SHOW_HOME:{
		APP_DBG_SIG("AC_DISPLAY_SHOW_HOME\n");
		SCREEN_TRAN(scr_home_handle, &scr_home);
	}break;

	default:
		break;
	}
}