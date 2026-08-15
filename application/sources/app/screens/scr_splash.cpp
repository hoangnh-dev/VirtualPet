#include "scr_splash.h"
#include "pet.h"
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
		if (pet_manager_load_game()) {
			timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_HOME, AC_DISPLAY_STARTUP_INTERVAL, TIMER_ONE_SHOT);
		}else{
			timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_NAMING, AC_DISPLAY_STARTUP_INTERVAL, TIMER_ONE_SHOT);
			task_post_pure_msg(VP_GAME_PROFILE_ID, VP_GAME_PROFILE_SETUP);
		};
		task_post_pure_msg(VP_GAME_PET_ID, VP_GAME_PET_SETUP);
		
	} break;
	case AC_DISPLAY_SHOW_HOME:{
		APP_DBG_SIG("AC_DISPLAY_SHOW_HOME\n");
		SCREEN_TRAN(scr_home_handle, &scr_home);
	}break;
	case AC_DISPLAY_SHOW_NAMING:{
		APP_DBG_SIG("AC_DISPLAY_SHOW_NAMING\n");
		SCREEN_TRAN(scr_naming_handle, &scr_naming);
	}break;

	default:
		break;
	}
}