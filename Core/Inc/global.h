#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"

// Các hằng số Mode
#define MODE_AUTO       1
#define MODE_SET_RED    2
#define MODE_SET_YELLOW 3
#define MODE_SET_GREEN  4

// Định nghĩa kiểu dữ liệu trạng thái FSM Automatic
typedef enum {
    AUTO_INIT,
    AUTO_RED1_GREEN2,
    AUTO_RED1_YELLOW2,
    AUTO_GREEN1_RED2,
    AUTO_YELLOW1_RED2
} AutoState;

// KHAI BÁO BIẾN TOÀN CỤC (EXTERN)
extern int current_mode;
extern AutoState auto_state;

extern int red_time;
extern int yellow_time;
extern int green_time;
extern int temp_time;

extern int count_road1;
extern int count_road2;

#endif /* INC_GLOBAL_H_ */
