#include "fsm_automatic.h"
#include "button.h" // Thêm thư viện nút bấm

// 1. Giảm số hiển thị 1s bằng Timer 0
void decrease_counter(void) {
    if (timer_flag[0] == 1) {
        setTimer(0, 1000);

        if (count_road1 > 0) count_road1--;
        if (count_road2 > 0) count_road2--;
    }
}

// 2. Các hàm bọc lệnh phần cứng LED
void set_led_red1_green2(void) {
    set_traffic_leds(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET,
                     GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET);
}

void set_led_red1_yellow2(void) {
    set_traffic_leds(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET,
                     GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET);
}

void set_led_green1_red2(void) {
    set_traffic_leds(GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET,
                     GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET);
}

void set_led_yellow1_red2(void) {
    set_traffic_leds(GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET,
                     GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET);
}

void fsm_automatic_init(void) {
    auto_state = AUTO_INIT;
}

void fsm_automatic_run(void) {
    // Guard Clause 1: Thoát nếu không ở Mode Auto
    if (current_mode != MODE_AUTO) return;

    // Guard Clause 2: Nút 1 chuyển từ Auto sang Manual/Setting
    if (is_button_pressed(0)) {
        current_mode = MODE_SET_RED;
        temp_time = red_time;
        setTimer(1, 250); // Timer index 1 nháy LED 2Hz
        return;
    }

    // Cập nhật nhịp đếm lùi 1s tập trung
    decrease_counter();

    // Switch-case FSM tự động
    switch (auto_state) {
        case AUTO_INIT:
            auto_state = AUTO_RED1_GREEN2;
            count_road1 = red_time;
            count_road2 = green_time;
            setTimer(0, 1000);              // Timer 0: đếm số 1s
            setTimer(3, green_time * 1000); // Timer 3: canh pha Xanh 2
            set_led_red1_green2();
            break;

        case AUTO_RED1_GREEN2:
            set_led_red1_green2();
            // Khi hết giờ Xanh 2 -> Nạp lại thời gian Vàng 2 đúng 1 lần
            if (timer_flag[3] == 1) {
                auto_state = AUTO_RED1_YELLOW2;
                count_road2 = yellow_time;
                setTimer(3, yellow_time * 1000);
            }
            break;

        case AUTO_RED1_YELLOW2:
            set_led_red1_yellow2();
            // Khi hết giờ Vàng 2 -> Chuyển sang Xanh 1 - Đỏ 2
            if (timer_flag[3] == 1) {
                auto_state = AUTO_GREEN1_RED2;
                count_road1 = green_time;
                count_road2 = red_time;
                setTimer(3, green_time * 1000);
            }
            break;

        case AUTO_GREEN1_RED2:
            set_led_green1_red2();
            // Khi hết giờ Xanh 1 -> Nạp lại thời gian Vàng 1 đúng 1 lần
            if (timer_flag[3] == 1) {
                auto_state = AUTO_YELLOW1_RED2;
                count_road1 = yellow_time;
                setTimer(3, yellow_time * 1000);
            }
            break;

        case AUTO_YELLOW1_RED2:
            set_led_yellow1_red2();
            // Khi hết giờ Vàng 1 -> Quay lại Đỏ 1 - Xanh 2
            if (timer_flag[3] == 1) {
                auto_state = AUTO_RED1_GREEN2;
                count_road1 = red_time;
                count_road2 = green_time;
                setTimer(3, green_time * 1000);
            }
            break;

        default:
            break;
    }

    // Quét hiển thị LED 7 đoạn bằng Timer index 2
    if (timer_flag[2] == 1) {
        setTimer(2, 20);
        scan_7seg(count_road1, count_road2);
    }
}
