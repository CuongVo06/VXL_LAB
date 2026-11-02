#include "fsm_automatic.h"

static AutoState auto_state = AUTO_RED1_GREEN2;
static int count_road1 = 0;
static int count_road2 = 0;

void fsm_automatic_init(void) {
    auto_state = AUTO_RED1_GREEN2;
    count_road1 = red_time;
    count_road2 = green_time;
    setTimer1(1000);
}

void fsm_automatic_run(void) {
    if (current_mode != MODE_AUTO) return;

    if (timer1_flag == 1) {
        setTimer1(1000);
        count_road1--;
        count_road2--;

        switch (auto_state) {
            case AUTO_RED1_GREEN2:
                if (count_road2 <= 0) {
                    auto_state = AUTO_RED1_YELLOW2;
                    count_road2 = yellow_time;
                }
                break;

            case AUTO_RED1_YELLOW2:
                if (count_road2 <= 0) {
                    auto_state = AUTO_GREEN1_RED2;
                    count_road1 = green_time;
                    count_road2 = red_time;
                }
                break;

            case AUTO_GREEN1_RED2:
                if (count_road1 <= 0) {
                    auto_state = AUTO_YELLOW1_RED2;
                    count_road1 = yellow_time;
                }
                break;

            case AUTO_YELLOW1_RED2:
                if (count_road1 <= 0) {
                    auto_state = AUTO_RED1_GREEN2;
                    count_road1 = red_time;
                    count_road2 = green_time;
                }
                break;
        }
    }

    switch (auto_state) {
        case AUTO_RED1_GREEN2:
            set_traffic_leds(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET,
                             GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET);
            break;
        case AUTO_RED1_YELLOW2:
            set_traffic_leds(GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET,
                             GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET);
            break;
        case AUTO_GREEN1_RED2:
            set_traffic_leds(GPIO_PIN_RESET, GPIO_PIN_RESET, GPIO_PIN_SET,
                             GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET);
            break;
        case AUTO_YELLOW1_RED2:
            set_traffic_leds(GPIO_PIN_RESET, GPIO_PIN_SET, GPIO_PIN_RESET,
                             GPIO_PIN_SET, GPIO_PIN_RESET, GPIO_PIN_RESET);
            break;
    }

    if (timer3_flag == 1) {
        setTimer3(20); // Thay vì 10
        scan_7seg(count_road1, count_road2);
    }
}
