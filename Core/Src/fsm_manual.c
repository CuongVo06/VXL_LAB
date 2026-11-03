#include "fsm_manual.h"
#include "fsm_automatic.h"

void fsm_manual_run(void) {
    // Guard Clause 1: Thoát nếu đang ở Auto (Auto đã tự lắng nghe Nút 1 rồi)
    if (current_mode == MODE_AUTO) return;

    // Guard Clause 2: Không nhấn Nút 1 thì thoát ngay
    if (!is_button_pressed(0)) return;

    // Chuyển Mode vòng tròn khi ở các chế độ cài đặt
    switch (current_mode) {
        case MODE_SET_RED:
            current_mode = MODE_SET_YELLOW;
            temp_time = yellow_time;
            setTimer(1, 250);
            break;

        case MODE_SET_YELLOW:
            current_mode = MODE_SET_GREEN;
            temp_time = green_time;
            setTimer(1, 250);
            break;

        case MODE_SET_GREEN:
            current_mode = MODE_AUTO;
            fsm_automatic_init(); // Khởi tạo lại FSM Auto khi quay về
            break;

        default:
            break;
    }
}
