#ifndef __SCREENS_H__
#define __SCREENS_H__

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "sys_ctrl.h"
#include "sys_dbg.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"
#include "view_render.h"

#include "buzzer.h"

#include <math.h>
#include <vector>

#include "qrcode.h"
#include "screens_bitmap.h"

// scr_startup
extern view_dynamic_t dyn_view_startup;
extern view_screen_t scr_startup;
extern void scr_startup_handle(ak_msg_t* msg);

// scr_splash
extern view_dynamic_t dyn_view_splash;
extern view_screen_t scr_splash;
extern void scr_splash_handle(ak_msg_t* msg);

// scr_home
extern view_dynamic_t dyn_view_home;
extern view_screen_t scr_home;
extern void scr_home_handle(ak_msg_t* msg);

// scr_menu
extern view_dynamic_t dyn_view_menu;
extern view_screen_t scr_menu;
extern void scr_menu_handle(ak_msg_t* msg);

// scr_training
extern view_dynamic_t dyn_view_training;
extern view_screen_t scr_training;
extern void scr_training_handle(ak_msg_t* msg);

// scr_status
extern view_dynamic_t dyn_view_status;
extern view_screen_t scr_status;
extern void scr_status_handle(ak_msg_t* msg);

// scr_naming
extern view_dynamic_t dyn_view_naming;
extern view_screen_t scr_naming;
extern void scr_naming_handle(ak_msg_t* msg);

#endif //__SCREENS_H__
