#include "sleepbutton.h"
#include <LilyGo_RGBPanel.h>

extern LilyGo_RGBPanel panel;
extern bool gotoSleep;  // 引用 gotoSleep 变量

static void btn_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED) {
        lv_label_set_text(lv_obj_get_child(btn, 0), "Sleeping...");
        gotoSleep = true;
    }
}

void create_sleep_button(lv_obj_t *parent) {
    // 创建矩形按钮
    lv_obj_t *btn_sleep = lv_btn_create(parent);
    lv_obj_set_size(btn_sleep, 120, 50);  // 设置按钮大小
    lv_obj_align(btn_sleep, LV_ALIGN_CENTER, 0, 100);  // 设置按钮位置

    // 创建按钮样式
    static lv_style_t style_btn;
    lv_style_init(&style_btn);
    lv_style_set_border_color(&style_btn, lv_color_hex(0x0000FF));  // 设置边框颜色为蓝色
    lv_style_set_border_width(&style_btn, 2);  // 设置边框宽度
    lv_style_set_border_opa(&style_btn, LV_OPA_COVER);  // 设置边框不透明度

    // 将样式应用到按钮
    lv_obj_add_style(btn_sleep, &style_btn, 0);

    // 创建按钮内的标签
    lv_obj_t *btn_label = lv_label_create(btn_sleep);
    lv_label_set_text(btn_label, "Sleep now");  // 设置标签文字
    lv_obj_center(btn_label);  // 将标签居中对齐

    // 添加按钮事件回调
    lv_obj_add_event_cb(btn_sleep, btn_event_cb, LV_EVENT_ALL, NULL);
}