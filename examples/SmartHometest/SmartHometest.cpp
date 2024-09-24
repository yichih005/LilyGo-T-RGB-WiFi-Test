#include <LilyGo_RGBPanel.h>
#include <LV_Helper.h>
#include "src/background.h"
#include "src/ui_elements.h"
#include "src/sleepbutton.h"

LilyGo_RGBPanel panel;

// 声明UI元素
lv_obj_t *main_screen;
lv_obj_t *label_title;
lv_obj_t *sleep_label;  // 新增用于显示时间的标签
bool gotoSleep = false;  // 定义 gotoSleep 变量
bool isWakingUp = false; // 新增变量，用于标记是否正在从睡眠状态唤醒
unsigned long sleepStartTime = 0; // 记录进入睡眠状态的时间

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

    // 创建渐变背景
    create_gradient_background(main_screen);

    // 创建标题标签，位置设置为 (40, 60)
    label_title = title_label(main_screen, "SMART HOME PANEL", 85, 80);

    // 创建睡眠按钮
    create_sleep_button(main_screen);

    panel.setBrightness(16);
}

void loop()
{
    if (gotoSleep) {
        Serial.println("Entering sleep mode...");

        // 显示睡眠文本
        lv_label_set_text(label_title, "Sleeping...");
        lv_timer_handler();
        delay(500); // 减少延迟时间

        // 启用触摸唤醒
        panel.enableTouchWakeup();

        // 记录进入睡眠状态的时间
        sleepStartTime = millis();

        // 呼吸灯效果：逐渐降低亮度
        for (int i = 16; i >= 0; i--) {
            panel.setBrightness(i);
            delay(50);
        }

        // 设置屏幕为全黑
        lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), 0);
        lv_obj_set_style_bg_opa(lv_scr_act(), LV_OPA_COVER, 0);

        // 创建用于显示时间的标签
        sleep_label = lv_label_create(lv_scr_act());
        lv_label_set_text(sleep_label, "09:30");  // 设置示意时间
        lv_obj_set_style_text_color(sleep_label, lv_color_hex(0xFFFFFF), 0);  // 设置时间颜色
        lv_obj_center(sleep_label);  // 将标签居中对齐

        // 时间渐进浮现效果
        for (int opa = 0; opa <= 255; opa += 5) {
            lv_obj_set_style_text_opa(sleep_label, opa, 0);
            lv_timer_handler();
            delay(50);
        }

        // 进入睡眠模式
        panel.sleep();

        // 重置睡眠标志
        gotoSleep = false;
        isWakingUp = true; // 设置唤醒标志
    }

    if (isWakingUp) {
        // 呼吸灯效果：逐渐增加亮度
        for (int i = 0; i <= 16; i++) {
            panel.setBrightness(i);
            delay(50);
        }

        // 恢复屏幕内容
        lv_scr_load(main_screen);

        // 重置唤醒标志
        isWakingUp = false;

        Serial.println("Woke up from sleep mode");
    }

    // lvgl 任务处理应放在 loop 函数中
    lv_timer_handler();
    delay(2);
}