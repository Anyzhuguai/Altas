#include "pid.h"
#include "tim.h" // 必须包含这个，因为要用 htim2, htim3

// 引入外部句柄
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2; // 左编码器
extern TIM_HandleTypeDef htim3; // 右编码器

// --- 循迹 PID 参数 (保持不变) ---
float Kp = 6.0f; 
float Kd = 4.5f;  
float error = 0;
float last_error = 0;
int base_speed = 150; // 这里现在的含义是“目标脉冲数/每循环”，而不是PWM了

// --- 新增：速度 PID 参数 ---
// 需要你自己调，先给一组经验值
float Vel_Kp = 0.5f;  
float Vel_Ki = 0.0f;
// 速度环通常不需要 Kd，或者很小

// 记录左右电机速度控制的累积误差 (用于积分项)
float error_sum_L = 0;
float error_sum_R = 0;

/**
 * @brief 读取编码器当前速度 (脉冲数)
 * 注意：读取后会清零计数器，得到的数值代表“这段时间内的脉冲数”
 */
void Read_Encoder(int* speed_L, int* speed_R)
{
    // 强制转换为 int16_t 以处理反转时的负数 (0 -> 65535 -> -1)
    *speed_L = -(int16_t)__HAL_TIM_GET_COUNTER(&htim2);
    *speed_R = (int16_t)__HAL_TIM_GET_COUNTER(&htim3); 
    // 注意：如果右轮读数是负的但车是往前跑，可以在这里加个负号: -(*speed_R)

    // 清零计数器，为下一次测量做准备
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    __HAL_TIM_SET_COUNTER(&htim3, 0);
}

/**
 * @brief 增量式/位置式 PID 计算 PWM
 * @param target_speed: 期望的速度 (编码器脉冲数)
 * @param current_speed: 当前真实速度
 * @param error_sum: 积分项累积 (指针)
 * @return: 计算出的 PWM 值
 */
int Speed_PID_Calc(int target_speed, int current_speed, float* error_sum)
{
    int pwm_out;
    int err = target_speed - current_speed;
    
    *error_sum += err; // 积分累加
    
    // 积分限幅 (防止长时间堵转导致数值过大)
    if(*error_sum > 2000) *error_sum = 2000;
    if(*error_sum < -2000) *error_sum = -2000;

    // 简单的 PI 控制 (速度环主要靠积分保持力度)
    pwm_out = (int)(Vel_Kp * err + Vel_Ki * *error_sum);

    return pwm_out;
}


/**
 * @brief 电机控制底层函数
 * @param motor_L: 左电机速度 (-1000 ~ +1000)
 * @param motor_R: 右电机速度 (-1000 ~ +1000)
 */
void Motor_Set(int motor_L, int motor_R)
{
    // --- 左电机控制 (PB12, PB13, PA9/TIM1_CH2) ---
    if (motor_L > 0) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
    } else {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
        motor_L = -motor_L; // 取绝对值
    }
    // 限幅
    if (motor_L > 1000) motor_L = 1000;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, motor_L); // PA9

    // --- 右电机控制 (PB14, PB15, PA10/TIM1_CH3) ---
    if (motor_R > 0) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
    } else {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
        motor_R = -motor_R;
    }
    // 限幅
    if (motor_R > 1000) motor_R = 1000;
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, motor_R); // PA10
}

/**
 * @brief 计算位置偏差 (加权平均法)
 * 假设 ir_x1 是最左边，ir_x8 是最右边
 */
float Calc_Error(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t d8)
{
    // 简单的加权算法
    // 左侧传感器给负权重，右侧给正权重
    // 越靠边的传感器权重越大
    // 假设 1 代表检测到黑线
    long total_val = 0;
    int sensor_count = d1+d2+d3+d4+d5+d6+d7+d8;

    if (sensor_count == 0) return last_error; // 丢失线条时保持上一次的状态

    total_val += d1 * (-40) + d2 * (-30) + d3 * (-20) + d4 * (-10); // 左边
    total_val += d5 * (10)  + d6 * (20)  + d7 * (30)  + d8 * (40);  // 右边

    return (float)total_val / sensor_count;
}

uint8_t Is_Horizontal_Line(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t d8)
{
    int count = d1 + d2 + d3 + d4 + d5 + d6 + d7 + d8;
    // 如果大部分传感器（比如 >= 6个）都是黑的，说明遇到路口了
	if (count <= 1) return 1;
    return 0;
}



/* USER CODE END 4 */

