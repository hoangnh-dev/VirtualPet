#include "scr_naming.h"

static void view_scr_naming();

view_dynamic_t dyn_view_naming = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_naming
};

view_screen_t scr_naming = {
	&dyn_view_naming,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void view_scr_naming() {
    view_render.clear();
    view_render.drawBitmap(46,0,bitmap_egg_1,36,39,WHITE);
    uint8_t x = 42;
    for (uint8_t i = 0; i < 5; i++) {
        view_render.setCursor(x,50);
        view_render.print('_');
        if(i == 0){
            view_render.setCursor(x,60);
            view_render.print('^');
        }
        x += 10;
    }
}

void scr_naming_handle(ak_msg_t *msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
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