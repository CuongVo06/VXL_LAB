#include "fsm_setting.h"

static int toggle_flag = 0;

void fsm_setting_run(void) {
    // Guard Clause: Thoát nếu đang ở Mode Auto
    if (current_mode == MODE_AUTO) return;

    // Timer index 1: Nháy LED 2Hz (250ms)
    if (timer_flag[1] == 1) {
        setTimer(1, 250);
        toggle_flag = !toggle_flag;
    }

    // Nút 2: Tăng thời gian tạm thời
    if (is_button_pressed(1)) {
        temp_time++;
        if (temp_time > 99) temp_time = 1;
    }

    // Nút 3: Lưu thời gian chính thức
    if (is_button_pressed(2)) {
        switch (current_mode) {
            case MODE_SET_RED:
                red_time = temp_time;
                break;
            case MODE_SET_YELLOW:
                yellow_time = temp_time;
                break;
            case MODE_SET_GREEN:
                green_time = temp_time;
                break;
            default:
                break;
        }
    }

    // Nháy LED tương ứng Mode
    switch (current_mode) {
        case MODE_SET_RED:
            blink_red_leds(toggle_flag);
            break;
        case MODE_SET_YELLOW:
            blink_yellow_leds(toggle_flag);
            break;
        case MODE_SET_GREEN:
            blink_green_leds(toggle_flag);
            break;
        default:
            break;
    }

    // Quét LED 7 đoạn
    if (timer_flag[2] == 1) {
        setTimer(2, 20);
        scan_7seg(current_mode, temp_time);
    }
}
