#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer1_flag; // Dùng cho đếm ngược 1s
extern int timer2_flag; // Dùng cho chớp tắt LED 2Hz (250ms)
extern int timer3_flag; // Dùng cho quét LED 7 đoạn (10ms)

void setTimer1(int duration);
void setTimer2(int duration);
void setTimer3(int duration);
void timerRun(void);

#endif /* INC_SOFTWARE_TIMER_H_ */
