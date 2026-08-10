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
    for (uint8_t i = 0; i < NAME_LEN; i++) {
        view_render.setCursor(x,50);
        view_render.print(profile.name[i]);
        if(i == name_index){
            view_render.setCursor(x,60);
            view_render.print('^');
        }
        x += 10;
    }
}
void name_button_action(uint8_t input){
	task_post_common_msg(VP_GAME_PROFILE_ID, VP_GAME_PROFILE_BUTTON,(uint8_t*)&input,1);
}
// void next_action(){
// 	if(select_intdex == NAME_MAX){
// 		SCREEN_TRAN(scr_home_handle, &scr_home);
// 	}else{
// 		select_intdex ++;
// 	}
// }

void scr_naming_handle(ak_msg_t *msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_NAMING_UPDATE, AC_DISPLAY_EGG_INTERVAL, TIMER_PERIODIC);
		BUZZER_PlaySound(BUZZER_SOUND_WELCOME);
	} break;
	case AC_DISPLAY_NAMING_UPDATE:{
		task_post_pure_msg(VP_GAME_PROFILE_ID, VP_GAME_PROFILE_TICK);
	}break;
	case AC_DISPLAY_BUTTON_UP_PRESSED:{
		name_button_action(0);
	}break;
	case AC_DISPLAY_BUTTON_DOWN_PRESSED:{
		name_button_action(1);
	}break;
	case AC_DISPLAY_BUTTON_MODE_PRESSED:{
		if((name_index + 1) == NAME_LEN){
			SCREEN_TRAN(scr_home_handle, &scr_home);
		}else{
			name_button_action(2);
		}
	}break;

	default:
		break;
	}
}