#include "ui_elements.h"
#include <cstdio>

lv_obj_t* title_label(lv_obj_t* parent, const char* text, lv_coord_t x, lv_coord_t y)
{
    lv_obj_t* label = lv_label_create(parent);
    lv_label_set_text(label, text);
    
    static lv_style_t style_title;
    lv_style_init(&style_title);
    lv_style_set_text_font(&style_title, &lv_font_montserrat_28);
    lv_style_set_text_color(&style_title, lv_color_hex(0x000079));  // 白色文字
    // 移除了背景颜色和不透明度的设置
    lv_obj_add_style(label, &style_title, 0);

    lv_coord_t text_width = lv_obj_get_width(label);
    lv_coord_t text_height = lv_obj_get_height(label);

    // 直接使用提供的 x 和 y 值
    lv_obj_set_pos(label, x, y);

    // 打印标签的尺寸
    printf("Label size: %d x %d\n", text_width, text_height);

    return label;
}