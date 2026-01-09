#ifndef __PID_H_
#define __PID_H_

#include "stm32f1xx_hal.h"

extern float Kp, Kd;
extern int base_speed; // 这里的 base_speed 现在代表目标编码器脉冲数

extern float error;
extern float last_error;

void Motor_Set(int motor_L, int motor_R);
float Calc_Error(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t d8);
uint8_t Is_Horizontal_Line(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t d8);

// --- 新增声明 ---
void Read_Encoder(int* speed_L, int* speed_R);
int Speed_PID_Calc(int target_speed, int current_speed, float* error_sum);
// 导出积分变量以便清零
extern float error_sum_L; 
extern float error_sum_R;

#endif