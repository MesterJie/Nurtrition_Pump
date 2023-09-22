#ifndef __MOTOR_H
#define __MOTOR_H
#include "at32f415.h"

void pwm_set(uint16_t te);
void pwm_stop(void);
void motor_step_set(uint32_t step_s);
void tmr_stop(void);
void motor_init(void);
#endif

