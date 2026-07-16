#include "scr_menu.h"

typedef enum {
    EATING = 0,
    CLEANING,
    TRAINING,
    BACK,
    MENU_COUNT          
} menu_item_t;

static const char *menu_items[] = {
    [EATING]   = "Eating",
    [CLEANING] = "Cleaning",
    [TRAINING] = "Training",
    [BACK]     = "Back"
};
static void view_scr_menu();
static uint8_t menu_index = EATING; //current index

view_dynamic_t dyn_view_menu = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_menu
};

view_screen_t scr_menu = {
	&dyn_view_menu,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void scr_menu_show_items(){
	view_render.fillRect(48,25,6,8,BLACK);
	view_render.setCursor(48,25);
	view_render.print(menu_items[menu_index]);
}

void view_scr_menu() {
    view_render.clear();
	view_render.drawBitmap(	58, \
		0, \
		bitmap_arrow_up, \
		16, \
		9, \
		WHITE);

	view_render.drawBitmap(	58, \
		55, \
		bitmap_arrow_down, \
		16, \
		9, \
		WHITE);
	scr_menu_show_items();
}
void scr_menu_select_items(){
	switch (menu_index) {
        case EATING:
            
            break;
        case CLEANING:
           
            break;
        case TRAINING:
            
            break;
        case BACK:
			menu_index = EATING;
            SCREEN_TRAN(scr_home_handle, &scr_home);
            break;
        default:
            break;
    }
}



void scr_menu_handle(ak_msg_t *msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
		BUZZER_PlaySound(BUZZER_SOUND_WELCOME);
	} break;
	case AC_DISPLAY_BUTTON_UP_PRESSED:{
		menu_index = (menu_index == 0) ? (MENU_COUNT - 1) : (menu_index - 1);
		scr_menu_show_items();
	}break;
	case AC_DISPLAY_BUTTON_DOWN_PRESSED:{
		menu_index = (menu_index + 1) % MENU_COUNT;
		scr_menu_show_items();
	}break;
	case AC_DISPLAY_BUTTON_MODE_PRESSED:{
		scr_menu_select_items();
	}break;
	default:
		break;
	}
}