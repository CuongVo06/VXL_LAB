#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define MODE_AUTO       1
#define MODE_SET_RED    2
#define MODE_SET_YELLOW 3
#define MODE_SET_GREEN  4

extern int current_mode;

extern int red_time;
extern int yellow_time;
extern int green_time;
extern int temp_time;

#endif /* INC_GLOBAL_H_ */
