#include "fsm_manual.h"
#include "fsm_automatic.h"

void fsm_manual_run(void) {
    if (is_button_pressed(0)) { // Nhấn Nút 1 (PB9) chuyển Mode
        current_mode++;
        if (current_mode > MODE_SET_GREEN) {
            current_mode = MODE_AUTO;
        }

        switch (current_mode) {
            case MODE_AUTO:
                fsm_automatic_init();
                break;
            case MODE_SET_RED:
                temp_time = red_time;
                break;
            case MODE_SET_YELLOW:
                temp_time = yellow_time;
                break;
            case MODE_SET_GREEN:
                temp_time = green_time;
                break;
            default:
                break;
        }
    }
}
