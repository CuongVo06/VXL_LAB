#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define MAX_TIMERS 10

extern int timer_flag[MAX_TIMERS];

void setTimer(int index, int duration);
void timerRun(void);

#endif /* INC_SOFTWARE_TIMER_H_ */
