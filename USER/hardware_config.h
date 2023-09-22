#ifndef __HARDWARE_CONFIG_H
#define __HARDWARE_CONFIG_H
#include "at32f415.h"

/*********************LED引脚定义********************************/
#define SYS_LED_PIN GPIO_PINS_13
#define SYS_LED_PORT GPIOC

#define BAT_LED_PIN GPIO_PINS_12
#define BAT_LED_PORT GPIOA

#define AC_LED_PIN GPIO_PINS_7
#define AC_LED_PORT GPIOF

#define BAT_LED_ON() gpio_bits_reset(BAT_LED_PORT, BAT_LED_PIN)
#define BAT_LED_OFF() gpio_bits_set(BAT_LED_PORT, BAT_LED_PIN)

#define AC_LED_ON() gpio_bits_reset(AC_LED_PORT, AC_LED_PIN)
#define AC_LED_OFF() gpio_bits_set(AC_LED_PORT, AC_LED_PIN)

#define SYS_LED_ON() gpio_bits_set(SYS_LED_PORT, SYS_LED_PIN)
#define SYS_LED_OFF() gpio_bits_reset(SYS_LED_PORT, SYS_LED_PIN)
/************************电源引脚定义***********************************/
#define MOTOR_12V_PORT GPIOB
#define MOTOR_12V_PIN GPIO_PINS_3
#define MOTOR_12V_VALUE_ON (1) // 上电
// 12电源状态设定控制电机和加温管电源
#define EN_12V_ON() gpio_bits_set(EN_12V_PORT, EN_12V_PIN)
#define EN_12V_OFF() gpio_bits_reset(EN_12V_PORT, EN_12V_PIN)

#define EN_6V_PIN GPIO_PINS_6
#define EN_6V_PORT GPIOF
// 6V电源状态设定,下位机供电
#define EN_5V_ON() gpio_bits_set(EN_5V_PORT, EN_5V_PIN)
#define EN_5V_OFF() gpio_bits_reset(EN_5V_PORT, EN_5V_PIN)

#define EN_LCD_PIN GPIO_PINS_12
#define EN_LCD_PORT GPIOB
// LCD6V电源控制上位机
#define EN_LCD_ON() gpio_bits_set(EN_LCD_PORT, EN_LCD_PIN)
#define EN_LCD_OFF() gpio_bits_reset(EN_LCD_PORT, EN_LCD_PIN)

// 判断下位机电池是否充满电(高电平充满)
#define CN3762_CHRG_PIN GPIO_PINS_14
#define CN3762_CHRG_PORT GPIOC
#define CN3762_CHRG gpio_input_data_bit_read(CN3762_CHRG_PORT, CN3762_CHRG_PIN);

// 读取此位为高电平，代表充电中
#define AC_DET_PIN GPIO_PINS_5
#define AC_DET_PORT GPIOA
#define AC_DET gpio_input_data_bit_read(AC_DET_PORT, AC_DET_PIN)
/**************************止液夹引脚定义************************************/
#define CLIP1_PIN1 GPIO_PINS_8
#define CLIP1_PIN1_PORT GPIOA
#define CLIP1_PIN1_CLOCK CRM_GPIOA_PERIPH_CLOCK

#define CLIP1_PIN2 GPIO_PINS_9
#define CLIP1_PIN2_PORT GPIOA
#define CLIP1_PIN2_CLOCK CRM_GPIOA_PERIPH_CLOCK

#define CLIP2_PIN1 GPIO_PINS_10
#define CLIP2_PIN1_PORT GPIOA
#define CLIP2_PIN1_CLOCK CRM_GPIOA_PERIPH_CLOCK

#define CLIP2_PIN2 GPIO_PINS_11
#define CLIP2_PIN2_PORT GPIOA
#define CLIP2_PIN2_CLOCK CRM_GPIOA_PERIPH_CLOCK

/**********************电机引脚定义*******************************************/
#define MOTOR_CURRENT_PORT GPIOB
#define MOTOR_CURRENT_PIN GPIO_PINS_6

#define MOTOR_DIR_PORT GPIOB
#define MOTOR_DIR_PIN GPIO_PINS_7
#define MOTOR_DIR_VALUE_ON (1) // 正转
// 电机方向设定
#define MOTOR_DIR_FORWARD() gpio_bits_set(MOTOR_DIR_PORT, MOTOR_DIR_PIN)
#define MOTOR_DIR_BACKWARD() gpio_bits_reset(MOTOR_DIR_PORT, MOTOR_DIR_PIN)

#define MOTOR_ENABLE_PORT GPIOB
#define MOTOR_ENABLE_PIN GPIO_PINS_9
#define MOTOR_ENABLE_VALUE_ON (0) // 使能
// 电机使能位设定
#define MOTOR_EN_ON() gpio_bits_set(MOTOR_ENABLE_PORT, MOTOR_ENABLE_PIN)
#define MOTOR_EN_OFF() gpio_bits_reset(MOTOR_ENABLE_PORT, MOTOR_ENABLE_PIN)

#define MOTOR_STEP_PORT GPIOB
#define MOTOR_STEP_PIN GPIO_PINS_8
// 步进电机信号输入设定
#define MOTOR_STEP_ON() gpio_bits_set(MOTOR_STEP_PORT, MOTOR_STEP_PIN)
#define MOTOR_STEP_OFF() gpio_bits_reset(MOTOR_STEP_PORT, MOTOR_STEP_PIN)

/**********************光电开关引脚定义****************************************/
// 止液夹1的光电开关
#define G_CLIP1_PIN GPIO_PINS_14
#define G_CLIP1_PORT GPIOB
#define G_CLIP1_CLOCK    CRM_GPIOB_PERIPH_CLOCK
#define G_CLIP1_PORT_SOURCE          GPIO_PORT_SOURCE_GPIOB
#define G_CLIP1_PINS_SOURCE          GPIO_PINS_SOURCE14
#define G_CLIP1_EXTI_LINE            EXINT_LINE_14
#define G_CLIP1_IRQN                 EXINT15_10_IRQn
#define G_CLIP1_READ gpio_input_data_bit_read(G_CLIP1_PORT, G_CLIP1_PIN)

// 止液夹2的光电开关
#define G_CLIP2_PIN GPIO_PINS_15
#define G_CLIP2_PORT GPIOB
#define G_CLIP2_CLOCK    CRM_GPIOB_PERIPH_CLOCK
#define G_CLIP2_PORT_SOURCE          GPIO_PORT_SOURCE_GPIOB
#define G_CLIP2_PINS_SOURCE          GPIO_PINS_SOURCE15
#define G_CLIP2_EXTI_LINE            EXINT_LINE_15
#define G_CLIP2_IRQN                 EXINT15_10_IRQn
#define G_CLIP2_READ gpio_input_data_bit_read(G_CLIP2_PORT, G_CLIP2_PIN)

// 电机的光电开关
#define G1_MOTOR_PIN GPIO_PINS_5 // 靠近泵外围的光电开关
#define G1_MOTOR_PORT GPIOB
#define G1_MOTOR_CLOCK   CRM_GPIOB_PERIPH_CLOCK
#define G1_MOTOR_PORT_SOURCE          GPIO_PORT_SOURCE_GPIOB
#define G1_MOTOR_PINS_SOURCE          GPIO_PINS_SOURCE5
#define G1_MOTOR_EXTI_LINE            EXINT_LINE_5
#define G1_MOTOR_IRQN                 EXINT9_5_IRQn
#define G1_MOTOR_READ gpio_input_data_bit_read(G1_MOTOR_PORT, G1_MOTOR_PIN)

#define G2_MOTOR_PIN GPIO_PINS_4 // 靠近泵内侧的光电开关
#define G2_MOTOR_PORT GPIOB
#define G2_MOTOR_CLOCK   CRM_GPIOB_PERIPH_CLOCK
#define G2_MOTOR_PORT_SOURCE          GPIO_PORT_SOURCE_GPIOB
#define G2_MOTOR_PINS_SOURCE          GPIO_PINS_SOURCE4
#define G2_MOTOR_EXTI_LINE            EXINT_LINE_4
#define G2_MOTOR_IRQN                 EXINT4_IRQn
#define G2_MOTOR_READ gpio_input_data_bit_read(G2_MOTOR_PORT, G2_MOTOR_PIN)

/********************按键引脚定义*****************************************************/
#define POWER_KEY_PIN GPIO_PINS_13
#define POWER_KEY_PORT GPIOB
#define POWER_KEY_READ gpio_input_data_bit_read(POWER_KEY_PORT, POWER_KEY_PIN)

/********************ADC1通道引脚定义************************************************/
#define PRESSURE_ADC_PIN GPIO_PINS_4
#define PRESSURE_ADC_PORT GPIOA
#define BAT_ADC_PIN GPIO_Pins_6
#define BAT_ADC_PORT GPIOA

#define BUBBLE1_ADC_PIN GPIO_PINS_0
#define BUBBLE1_ADC_PORT GPIOB
#define BUBBlE2_ADC_PIN GPIO_PINS_1
#define BUBBlE2_ADC_PORT GPIOB

#define WARM1_PIN GPIO_PINS_0
#define WARM1_PORT GPIOA
#define WARM2_PIN GPIO_PINS_1
#define WARM2_PORT GPIOA

#define HTG_CUR_PIN GPIO_PINS_7
#define HTG_CUR_PORT GPIOA
/********************************加温管引脚定义*******************************/
#define HTG_PWM_PIN         GPIO_PINS_15
#define HTG_PWM_PORT        GPIOA

/********************ADC1通道**************************************************/
#define BUBBlE1_ADC1_CHANNEL ADC_CHANNEL_8
#define BAT_ADC1_CHANNEL ADC_CHANNEL_6
#define PRESS_ADC1_CHANNEL ADC_CHANNEL_4
#define WARM_PIPE1_ADC1_CHANNEL ADC_CHANNEL_0
#define BUBBlE2_ADC1_CHANNEL ADC_CHANNEL_9
#define WARM_PIPE2_ADC1_CHANNEL ADC_CHANNEL_1
#define WARM_HTG_CUR_ADC1_CHANNEL ADC_CHANNEL_7

static inline void gpio_set_dir_out(gpio_type *port, uint32_t pin)
{
    gpio_init_type gpio_init_struct;
    /* set default parameter */
    gpio_default_para_init(&gpio_init_struct);

    /* configure the led gpio */
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_pins = pin;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(port, &gpio_init_struct);
}

static inline void gpio_set_dir_in(gpio_type *port, uint32_t pin)
{
    gpio_init_type gpio_init_struct;
    /* set default parameter */
    gpio_default_para_init(&gpio_init_struct);

    // gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    // gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
    gpio_init_struct.gpio_pins = pin;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(port, &gpio_init_struct);
}
#endif
