#include "fsm_setting.h"

static int toggle_flag = 0;

void fsm_setting_run(void) {
    if (current_mode == MODE_AUTO) return;

    if (timer2_flag == 1) {
        setTimer2(250);
        toggle_flag = !toggle_flag;
    }

    if (is_button_pressed(1)) { // Nút 2 (PB10): Tăng thời gian
        temp_time++;
        if (temp_time > 99) temp_time = 1;
    }

    if (is_button_pressed(2)) { // Nút 3 (PB11): Xác nhận
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

    if (timer3_flag == 1) {
        setTimer3(20); // Thay vì 10
        scan_7seg(current_mode, temp_time);
    }
}
