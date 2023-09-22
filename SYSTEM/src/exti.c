#include "hardware_config.h"
#include "at32f415.h"
#include "exti.h"
void clip1_g_gpio_init(void)
{
  /* enable  clock */
  crm_periph_clock_enable(G_CLIP1_CLOCK, TRUE);
  gpio_set_dir_in(G_CLIP1_PORT,G_CLIP1_PIN);
}
void clip2_g_gpio_init(void)
{
  /* enable  clock */
  crm_periph_clock_enable(G_CLIP2_CLOCK, TRUE);
  gpio_set_dir_in(G_CLIP2_PORT,G_CLIP2_PIN);   
}
void motor_g1_gpio_init(void)
{
  /* enable  clock */
  crm_periph_clock_enable(G1_MOTOR_CLOCK, TRUE);
  gpio_set_dir_in(G1_MOTOR_PORT,G1_MOTOR_PIN); 
}
void motor_g2_gpio_init(void)
{
  /* enable  clock */
  crm_periph_clock_enable(G2_MOTOR_CLOCK, TRUE);
  gpio_set_dir_in(G2_MOTOR_PORT,G2_MOTOR_PIN);   
}
void clip1_g_exti_config()
{
  exint_init_type exint_init_struct;

  crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(G_CLIP1_CLOCK, TRUE);  

  gpio_exint_line_config(G_CLIP1_PORT_SOURCE, G_CLIP1_PINS_SOURCE);

  exint_default_para_init(&exint_init_struct);
  exint_init_struct.line_enable = TRUE;
  exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
  exint_init_struct.line_select = G_CLIP1_EXTI_LINE;
  exint_init_struct.line_polarity = EXINT_TRIGGER_BOTH_EDGE;
  exint_init(&exint_init_struct);    
  nvic_irq_enable(G_CLIP1_IRQN, 1, 0);
}
void clip2_g_exti_config()
{
  exint_init_type exint_init_struct;

  crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(G_CLIP2_CLOCK, TRUE);  

  gpio_exint_line_config(G_CLIP2_PORT_SOURCE, G_CLIP2_PINS_SOURCE);

  exint_default_para_init(&exint_init_struct);
  exint_init_struct.line_enable = TRUE;
  exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
  exint_init_struct.line_select = G_CLIP2_EXTI_LINE;
  exint_init_struct.line_polarity = EXINT_TRIGGER_BOTH_EDGE;
  exint_init(&exint_init_struct);    
  nvic_irq_enable(G_CLIP2_IRQN, 1, 0);
}
void motor_g1_exti_config()
{
  exint_init_type exint_init_struct;

  crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(G1_MOTOR_CLOCK, TRUE);  

  gpio_exint_line_config(G1_MOTOR_PORT_SOURCE, G1_MOTOR_PINS_SOURCE);

  exint_default_para_init(&exint_init_struct);
  exint_init_struct.line_enable = TRUE;
  exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
  exint_init_struct.line_select = G1_MOTOR_EXTI_LINE;
  exint_init_struct.line_polarity = EXINT_TRIGGER_BOTH_EDGE;
  exint_init(&exint_init_struct);    
  nvic_irq_enable(G1_MOTOR_IRQN, 1, 0);
}
void motor_g2_exti_config()
{
  exint_init_type exint_init_struct;

  crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(G2_MOTOR_CLOCK, TRUE);  

  gpio_exint_line_config(G2_MOTOR_PORT_SOURCE, G2_MOTOR_PINS_SOURCE);

  exint_default_para_init(&exint_init_struct);
  exint_init_struct.line_enable = TRUE;
  exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
  exint_init_struct.line_select = G2_MOTOR_EXTI_LINE;
  exint_init_struct.line_polarity = EXINT_TRIGGER_BOTH_EDGE;
  exint_init(&exint_init_struct);    
  nvic_irq_enable(G2_MOTOR_IRQN, 1, 0);
}



