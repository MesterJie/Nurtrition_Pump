#include "motor.h"
#include "hardware_config.h"

void crm_configuration(void)
{
    /* tmr3 clock enable */
    crm_periph_clock_enable(CRM_TMR3_PERIPH_CLOCK, TRUE);

    /* gpioa gpiob clock enable */
    crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

    crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
}
/**
  * @brief  configure the tmr3 pins.
  * @param  none
  * @retval none
  */
void gpio_configuration(void)
{
    gpio_init_type gpio_init_struct;

    gpio_default_para_init(&gpio_init_struct);
    gpio_pin_remap_config(TMR3_MUX_10, TRUE);
    gpio_pin_remap_config(SWJTAG_MUX_010, TRUE);

    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;

    gpio_init_struct.gpio_pins = GPIO_PINS_4;
    gpio_init(GPIOB, &gpio_init_struct);
}
#define PWM_ARR (800)
void tmr3_pwm_config(void)
{
    tmr_output_config_type tmr_oc_init_structure;
    /* compute the div value */
    uint16_t div_value = (uint16_t)(system_core_clock / 8000000) - 1;

    /* tmr3 time base configuration */
    tmr_base_init(TMR3, PWM_ARR, div_value);
    tmr_cnt_dir_set(TMR3, TMR_COUNT_UP);
    tmr_clock_source_div_set(TMR3, TMR_CLOCK_DIV1);

    tmr_output_default_para_init(&tmr_oc_init_structure);
    tmr_oc_init_structure.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
    tmr_oc_init_structure.oc_idle_state = FALSE;
    tmr_oc_init_structure.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
    tmr_oc_init_structure.oc_output_state = TRUE;
    tmr_output_channel_config(TMR3, TMR_SELECT_CHANNEL_1, &tmr_oc_init_structure);
    tmr_output_channel_buffer_enable(TMR3, TMR_SELECT_CHANNEL_1, TRUE);

    tmr_period_buffer_enable(TMR3, TRUE);


}
void pwm_set(uint16_t te)
{
    float cc1_cnt = te;
    cc1_cnt = (cc1_cnt / 100) * PWM_ARR;
    tmr_channel_value_set(TMR3, TMR_SELECT_CHANNEL_1, cc1_cnt);
    /* tmr enable counter */
    tmr_counter_enable(TMR3, TRUE);
}

void pwm_stop()
{
    TMR3->pr = 0;
    TMR3->div = 0;
    tmr_counter_enable(TMR3, FALSE);
}
#define MOTOR_TMR   TMR2
void timer_init(void)
{
    /* enable tmr1 clock */
    crm_periph_clock_enable(CRM_TMR2_PERIPH_CLOCK, TRUE);

    /* tmr1 configuration */
    /* time base configuration */
    /* systemclock/14400/10000 = 1hz */
    tmr_32_bit_function_enable(MOTOR_TMR, TRUE);
    tmr_base_init(MOTOR_TMR, 14400 - 1, 0);
    tmr_cnt_dir_set(MOTOR_TMR, TMR_COUNT_UP);

    /* overflow interrupt enable */
    tmr_interrupt_enable(MOTOR_TMR, TMR_OVF_INT, TRUE);

    /* tmr1 overflow interrupt nvic init */

    nvic_irq_enable(TMR2_GLOBAL_IRQn, 0, 0);

    /* enable tmr1 */
    tmr_counter_enable(MOTOR_TMR, FALSE);
}

void motor_step_set(uint32_t hz)
{
    //systemclock
    tmr_base_init(MOTOR_TMR, 144000000 / hz, 0);
    tmr_counter_enable(MOTOR_TMR, TRUE);
}

void tmr_stop()
{
    tmr_counter_enable(MOTOR_TMR, FALSE);
}
void motor_init(){

    crm_periph_clock_enable(CRM_TMR3_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
    crm_configuration();
    gpio_configuration();
    tmr3_pwm_config();
    gpio_set_dir_out(MOTOR_12V_PORT, MOTOR_12V_PIN);
    gpio_bits_write(MOTOR_12V_PORT, MOTOR_12V_PIN, (confirm_state)MOTOR_12V_VALUE_ON);

    gpio_set_dir_out(MOTOR_ENABLE_PORT, MOTOR_ENABLE_PIN);
    gpio_bits_write(MOTOR_ENABLE_PORT, MOTOR_ENABLE_PIN, (confirm_state)MOTOR_ENABLE_VALUE_ON);

    gpio_set_dir_out(MOTOR_DIR_PORT, MOTOR_DIR_PIN);
    gpio_bits_write(MOTOR_DIR_PORT, MOTOR_DIR_PIN, (confirm_state)MOTOR_DIR_VALUE_ON);

    gpio_set_dir_out(MOTOR_STEP_PORT, MOTOR_STEP_PIN);
    gpio_bits_write(MOTOR_STEP_PORT, MOTOR_STEP_PIN, (confirm_state)0);

    gpio_set_dir_in(G1_MOTOR_PORT, G1_MOTOR_PIN);
    gpio_set_dir_in(G2_MOTOR_PORT, G2_MOTOR_PIN);
    timer_init();  
    
    motor_step_set(5000);//≤‚ ‘
}

void TMR2_GLOBAL_IRQHandler()
{
    /* overflow interrupt enable */
    if (tmr_flag_get(MOTOR_TMR, TMR_OVF_INT) != RESET)
    {
        tmr_flag_clear(MOTOR_TMR, TMR_OVF_INT);
        
    }

}

