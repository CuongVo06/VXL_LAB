#include "global.h"

// ĐỊNH NGHĨA VÀ KHỞI TẠO BIẾN TOÀN CỤC
int current_mode = MODE_AUTO;
AutoState auto_state = AUTO_INIT;

int red_time = 5;     // Thời gian đèn Đỏ (giây)
int yellow_time = 2;  // Thời gian đèn Vàng (giây)
int green_time = 3;   // Thời gian đèn Xanh (giây)
int temp_time = 0;    // Thời gian tạm thời khi cài đặt

int count_road1 = 0;  // Bộ đếm thời gian thực tế đường 1
int count_road2 = 0;  // Bộ đếm thời gian thực tế đường 2
