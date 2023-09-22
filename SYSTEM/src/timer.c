#include "timer.h"
#include "at32f415.h"
#include "at32f415_clock.h"
typedef struct
{
    uint16_t tick_1000_ms;
    uint8_t tick_100_ms;
    uint8_t tick_10_ms;


    uint8_t check_10_ms:1;
    uint8_t check_100_ms:1;
    uint8_t check_1000_ms:1;
}systick_t;
static systick_t sg_systick;

/**
  * @brief  this function handles timer1 overflow handler.
  * @param  none
  * @retval none
  */
void TMR1_OVF_TMR10_IRQHandler(void)
{
    if (tmr_flag_get(TMR1, TMR_OVF_FLAG) != RESET)
    {
        /* add user code... */
        sg_systick.tick_1000_ms++;
        sg_systick.tick_100_ms++;
        sg_systick.tick_10_ms++;

        if (sg_systick.tick_1000_ms >= 1000)
        {
            sg_systick.check_1000_ms = 1;
            sg_systick.tick_1000_ms = 0;
        }
        if (sg_systick.tick_100_ms >= 100)
        {
            sg_systick.check_100_ms = 1;
            sg_systick.tick_100_ms = 0;
        }
        if (sg_systick.tick_10_ms >= 10)
        {
            sg_systick.check_10_ms = 1;
            sg_systick.tick_10_ms = 0;
        }
        tmr_flag_clear(TMR1, TMR_OVF_FLAG);
    }
}

crm_clocks_freq_type crm_clocks_freq_struct = { 0 };

int pal_tmr_init()
{
    /* get system clock */
    crm_clocks_freq_get(&crm_clocks_freq_struct);

    /* enable tmr1 clock */
    crm_periph_clock_enable(CRM_TMR1_PERIPH_CLOCK, TRUE);

    /* tmr1 configuration */
    /* time base configuration */
    /* systemclock/14400/10000 = 1hz */
    tmr_base_init(TMR1, 9, (crm_clocks_freq_struct.ahb_freq / 10000) - 1);
    tmr_cnt_dir_set(TMR1, TMR_COUNT_UP);

    /* overflow interrupt enable */
    tmr_interrupt_enable(TMR1, TMR_OVF_INT, TRUE);

    /* tmr1 overflow interrupt nvic init */
    nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
    nvic_irq_enable(TMR1_OVF_TMR10_IRQn, 0, 0);

    /* enable tmr1 */
    tmr_counter_enable(TMR1, TRUE);
    return 0;
}

//int pal_tmr_loop()
//{
//    if (sg_systick.check_10_ms)
//    {
//        sg_systick.check_10_ms = 0;
//        pal_loop_10ms();
//    }
//    if (sg_systick.check_100_ms)
//    {
//        sg_systick.check_100_ms = 0;
//        pal_loop_100ms();
//        app_loop_100ms();
//        runtick_100ms_loop();
//    }
//    if (sg_systick.check_1000_ms)
//    {
//        sg_systick.check_1000_ms = 0;
//        runtick_loop();
//    }
//    return 0;
//}

