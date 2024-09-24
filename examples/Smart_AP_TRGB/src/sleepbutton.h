#ifndef SLEEPBUTTON_H
#define SLEEPBUTTON_H

#include <lvgl.h>

extern bool gotoSleep;  // 声明 gotoSleep 变量

void create_sleep_button(lv_obj_t *parent);

#endif // SLEEPBUTTON_H