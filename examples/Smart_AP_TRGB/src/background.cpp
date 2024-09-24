#include "background.h"

void create_gradient_background(lv_obj_t *parent) {
    // 创建一个覆盖整个屏幕的对象
    lv_obj_t *background_obj = lv_obj_create(parent);
    lv_obj_set_size(background_obj, 480, 480);  // 使用具体的像素值
    lv_obj_set_pos(background_obj, 0, 0);  // 确保位置从(0,0)开始
    lv_obj_clear_flag(background_obj, LV_OBJ_FLAG_SCROLLABLE);

    // 移除所有边距和填充
    lv_obj_set_style_pad_all(background_obj, 0, 0);
    lv_obj_set_style_border_width(background_obj, 0, 0);
    lv_obj_set_style_radius(background_obj, 0, 0);  // 确保没有圆角

    // 创建渐变
    static lv_grad_dsc_t grad;
    grad.dir = LV_GRAD_DIR_HOR;  // 垂直方向渐变
    grad.stops_count = 2;
    grad.stops[0].color = lv_color_hex(0xFFFFAA);  // 深紫色（底部）
    grad.stops[1].color = lv_color_hex(0x79FF79);  // 浅绿色（顶部）
    grad.stops[0].frac = 0;
    grad.stops[1].frac = 255;

    // 应用渐变
    lv_obj_set_style_bg_grad(background_obj, &grad, 0);
    lv_obj_set_style_bg_main_stop(background_obj, 0, 0);
    lv_obj_set_style_bg_grad_stop(background_obj, 255, 0);

    // 确保背景对象位于最底层
    lv_obj_move_background(background_obj);
}