#include "traffic_display.h"

const uint8_t char_7seg[10] = {
    0b1000000, // 0
    0b1111001, // 1
    0b0100100, // 2
    0b0110000, // 3
    0b0011001, // 4
    0b0010010, // 5
    0b0000010, // 6
    0b1111000, // 7
    0b0000000, // 8
    0b0010000  // 9
};

void set_traffic_leds(GPIO_PinState r1, GPIO_PinState y1, GPIO_PinState g1,
                      GPIO_PinState r2, GPIO_PinState y2, GPIO_PinState g2) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, r1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, y1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, g1);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, r2);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, y2);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, g2);
}

void blink_red_leds(int state) {
    GPIO_PinState pin_st = state ? GPIO_PIN_SET : GPIO_PIN_RESET;
    set_traffic_leds(pin_st, GPIO_PIN_RESET, GPIO_PIN_RESET, pin_st, GPIO_PIN_RESET, GPIO_PIN_RESET);
}

void blink_yellow_leds(int state) {
    GPIO_PinState pin_st = state ? GPIO_PIN_SET : GPIO_PIN_RESET;
    set_traffic_leds(GPIO_PIN_RESET, pin_st, GPIO_PIN_RESET, GPIO_PIN_RESET, pin_st, GPIO_PIN_RESET);
}

void blink_green_leds(int state) {
    GPIO_PinState pin_st = state ? GPIO_PIN_SET : GPIO_PIN_RESET;
    set_traffic_leds(GPIO_PIN_RESET, GPIO_PIN_RESET, pin_st, GPIO_PIN_RESET, GPIO_PIN_RESET, pin_st);
}

// Cụm 1: a' -> g' (PB0 -> PB6)
void display_7seg_group1(int num) {
    if (num < 0 || num > 9) return;
    uint8_t code = char_7seg[num];
    for (int i = 0; i < 7; i++) {
        HAL_GPIO_WritePin(GPIOB, (GPIO_PIN_0 << i), ((code >> i) & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}

// Cụm 2: a -> g (PA7 -> PA13)
void display_7seg_group2(int num) {
    if (num < 0 || num > 9) return;
    uint8_t code = char_7seg[num];
    for (int i = 0; i < 7; i++) {
        HAL_GPIO_WritePin(GPIOA, (GPIO_PIN_7 << i), ((code >> i) & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}

static int scan_index = 0;

void scan_7seg(int num1, int num2) {
    int tens1 = num1 / 10;
    int units1 = num1 % 10;
    int tens2 = num2 / 10;
    int units2 = num2 % 10;

    // Tắt toàn bộ transistor (PB12..PB15 = HIGH)
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);

    if (scan_index == 0) {
        display_7seg_group1(tens1);
        display_7seg_group2(tens2);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); // Bật EN0
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET); // Bật EN2
        scan_index = 1;
    } else {
        display_7seg_group1(units1);
        display_7seg_group2(units2);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET); // Bật EN1
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET); // Bật EN3
        scan_index = 0;
    }
}
