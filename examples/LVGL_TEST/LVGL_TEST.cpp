#include <LilyGo_RGBPanel.h>
#include <LV_Helper.h>

LilyGo_RGBPanel panel;

// 声明UI元素
lv_obj_t *main_screen;

void create_circle(lv_obj_t *parent) {
    // 创建圆对象
    lv_obj_t *arc = lv_arc_create(parent);
    
    // 设置圆的尺寸和位置
    lv_obj_set_size(arc, 200, 200);  // 设置圆的直径
    lv_obj_align(arc, LV_ALIGN_CENTER, 0, 0);  // 居中对齐

    // 设置圆的起始角度和结束角度
    lv_arc_set_start_angle(arc, 0);
    lv_arc_set_end_angle(arc, 360);

    // 设置圆的样式
    lv_obj_set_style_arc_width(arc, 10, 0);  // 设置圆的线宽
    lv_obj_set_style_arc_color(arc, lv_color_hex(0xFF0000), 0);  // 设置圆的颜色
}

void setup()
{
    Serial.begin(115200);

    if (!panel.begin()) {
        while (1) {
            Serial.println("Error, failed to initialize T-RGB");
            delay(1000);
        }
    }

    beginLvglHelper(panel, false);

    // 创建主屏幕
    main_screen = lv_obj_create(NULL);
    lv_scr_load(main_screen);

    // 创建圆
    create_circle(main_screen);

    panel.setBrightness(16);
}

void loop()
{
    lv_timer_handler();
    delay(2);
}