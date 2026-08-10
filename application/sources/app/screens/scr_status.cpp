#include "scr_status.h"

static void view_scr_status();

view_dynamic_t dyn_view_status = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_status
};

view_screen_t scr_status = {
	&dyn_view_status,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void build_status_rows(status_t *rows) {
    rows[0].label = "NAME   :";
    strncpy(rows[0].value, profile.name, sizeof(rows[0].value));

    rows[1].label = "Weight :";
    snprintf(rows[1].value, sizeof(rows[1].value), "%d kg", profile.weight);

    rows[2].label = "Height :";
    snprintf(rows[2].value, sizeof(rows[2].value), "%d cm", profile.height);

    rows[3].label = "Age    :";
    snprintf(rows[3].value, sizeof(rows[3].value), "%d d", profile.age);

    rows[4].label = "Power  :";
    snprintf(rows[4].value, sizeof(rows[4].value), "%d", profile.power);
}

void status_display(const status_t *rows, uint8_t count){
    view_render.setTextSize(1);
	view_render.setTextColor(WHITE);
    uint8_t y = 0;
    for (uint8_t i = 0; i < 5; i++) {
        view_render.setCursor(2,y);
        view_render.print(rows[i].label);
        view_render.setCursor(60,y);
        view_render.print(rows[i].value);
        if (i == 0){
            y+= 16;
            view_render.drawLine(0, 10, LCD_WIDTH, 10,WHITE);
        }else{
            y+= 12;
        }
    }
}

void view_scr_status() {
    status_t status[5];
    build_status_rows(status);
    status_display(status, 5);
}

void scr_status_handle(ak_msg_t *msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
		BUZZER_PlaySound(BUZZER_SOUND_WELCOME);
	} break;

    case AC_DISPLAY_BUTTON_UP_PRESSED:
	case AC_DISPLAY_BUTTON_DOWN_PRESSED:
    case AC_DISPLAY_BUTTON_MODE_PRESSED:{
		SCREEN_TRAN(scr_menu_handle, &scr_menu);
	}break;
    
	default:
		break;
	}
}