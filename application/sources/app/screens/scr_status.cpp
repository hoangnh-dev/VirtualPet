#include "scr_status.h"

static void view_scr_status();

status_t status[5] = {
    {"NAME   :", "Pochi"},
    {"Weight :", "999 kg"},
    {"Height :", "999 d"},
    {"Age    :", "999 cm"},
    {"Power  :", "999999"}
};

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



void view_scr_status() {
    view_render.setTextSize(1);
	view_render.setTextColor(WHITE);
    uint8_t y = 0;
    for (uint8_t i = 0; i < 5; i++) {
        view_render.setCursor(2,y);
        view_render.print(status[i].label);
        view_render.setCursor(60,y);
        view_render.print(status[i].value);
        if (i == 0){
            y+= 16;
            view_render.drawLine(0, 10, LCD_WIDTH, 10,WHITE);
        }else{
            y+= 12;
        }
    }
}

void scr_status_handle(ak_msg_t *msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
		BUZZER_PlaySound(BUZZER_SOUND_WELCOME);
	} break;
    
	default:
		break;
	}
}