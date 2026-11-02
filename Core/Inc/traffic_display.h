#ifndef INC_TRAFFIC_DISPLAY_H_
#define INC_TRAFFIC_DISPLAY_H_

#include "main.h"

void set_traffic_leds(GPIO_PinState r1, GPIO_PinState y1, GPIO_PinState g1,
                      GPIO_PinState r2, GPIO_PinState y2, GPIO_PinState g2);

void blink_red_leds(int state);
void blink_yellow_leds(int state);
void blink_green_leds(int state);

void display_7seg_group1(int num);
void display_7seg_group2(int num);
void scan_7seg(int num1, int num2);

#endif /* INC_TRAFFIC_DISPLAY_H_ */
