#include "scr_setting.h"

static void view_scr_setting();

view_dynamic_t dyn_view_setting = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_setting
};

view_screen_t scr_setting = {
	&dyn_view_setting,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};


void view_scr_setting() {
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
	view_render.setCursor(48,32);
	view_render.print("EATING");
}

void scr_setting_handle(ak_msg_t *msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
		BUZZER_PlaySound(BUZZER_SOUND_WELCOME);
	} break;

	default:
		break;
	}
}