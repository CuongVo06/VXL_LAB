#include "button.h"

static GPIO_PinState buttonBuffer[NO_OF_BUTTONS] = {GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET};
static GPIO_PinState debounceBuffer1[NO_OF_BUTTONS] = {GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET};
static GPIO_PinState debounceBuffer2[NO_OF_BUTTONS] = {GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET};

static int button_flag[NO_OF_BUTTONS] = {0, 0, 0};

// Đúng theo sơ đồ Proteus: Nút 1 (Mode): PB9 | Nút 2 (Up): PB10 | Nút 3 (Set): PB11
static uint16_t button_pins[NO_OF_BUTTONS] = {GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11};

void button_reading(void) {
    for (int i = 0; i < NO_OF_BUTTONS; i++) {
        debounceBuffer2[i] = debounceBuffer1[i];
        debounceBuffer1[i] = HAL_GPIO_ReadPin(GPIOB, button_pins[i]);

        if (debounceBuffer1[i] == debounceBuffer2[i]) {
            if (buttonBuffer[i] != debounceBuffer1[i]) {
                buttonBuffer[i] = debounceBuffer1[i];
                if (buttonBuffer[i] == GPIO_PIN_RESET) {
                    button_flag[i] = 1;
                }
            }
        }
    }
}

int is_button_pressed(int index) {
    if (index < 0 || index >= NO_OF_BUTTONS) return 0;
    if (button_flag[index] == 1) {
        button_flag[index] = 0;
        return 1;
    }
    return 0;
}
