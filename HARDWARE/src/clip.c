#include "clip.h"
#include "exti.h"
#include "eeprom.h"
#include "hardware_config.h"
void clip1_gpio_init(void)
{
      /* enable  clock */
    crm_periph_clock_enable(CLIP1_PIN1_CLOCK, TRUE);
    crm_periph_clock_enable(CLIP1_PIN2_CLOCK, TRUE);
    gpio_set_dir_out(CLIP1_PIN1_PORT, CLIP1_PIN1);
    gpio_set_dir_out(CLIP1_PIN2_PORT, CLIP1_PIN2);

    gpio_bits_write(CLIP1_PIN1_PORT, CLIP1_PIN1, FALSE);
    gpio_bits_write(CLIP1_PIN2_PORT, CLIP1_PIN2, FALSE);
}
void clip2_gpio_init(void)
{
      /* enable  clock */
    crm_periph_clock_enable(CLIP2_PIN1_CLOCK, TRUE);
    crm_periph_clock_enable(CLIP2_PIN2_CLOCK, TRUE);    
    gpio_set_dir_out(CLIP2_PIN1_PORT, CLIP2_PIN1);
    gpio_set_dir_out(CLIP2_PIN2_PORT, CLIP2_PIN2);

    gpio_bits_write(CLIP2_PIN1_PORT, CLIP2_PIN1, FALSE);
    gpio_bits_write(CLIP2_PIN2_PORT, CLIP2_PIN2, FALSE);
}
void clip_init()
{
    clip1_gpio_init();
    clip2_gpio_init();

    clip1_g_gpio_init();
    clip2_g_gpio_init(); 

    clip1_g_exti_config();
    clip2_g_exti_config();  

    flash_ee_init();
}
bool clip1_run_status(){
  if(gpio_input_data_bit_read(CLIP1_PIN1_PORT,CLIP1_PIN1) != gpio_input_data_bit_read(CLIP1_PIN2_PORT,CLIP1_PIN2))
    return 1;
  return 0;
}
bool clip2_run_status(){
  if(gpio_input_data_bit_read(CLIP2_PIN1_PORT,CLIP1_PIN1) != gpio_input_data_bit_read(CLIP2_PIN2_PORT,CLIP1_PIN2))
    return 1;
  return 0;  
}
bool clip1_status()
{
    return gpio_input_data_bit_read(G_CLIP1_PORT, G_CLIP1_PIN);
}
bool clip2_status()
{
    return gpio_input_data_bit_read(G_CLIP2_PORT, G_CLIP2_PIN);
}

void EXINT4_IRQHandler(void)
{
  if(exint_flag_get(EXINT_LINE_4) != RESET)
  {
    exint_flag_clear(EXINT_LINE_4);
  }
}
void EXINT9_5_IRQHandler(void)
{
  if(exint_flag_get(EXINT_LINE_5) != RESET)
  {
    exint_flag_clear(EXINT_LINE_5);
  }
}

