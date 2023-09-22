#include "l_clip.h"
#include "eeprom.h"
#include "clip.h"
#include "hardware_config.h"

#define MS_2_TICK(ms) (ms / 10)
#define NORMAL_MS 5000
#define INIT_CLOSE_MS 1200
#define INIT_OPENNING_MS    10000
Clip_t Clip;

ee_clip_state_en get_clip_state_from_flash()
{
    uint16_t address = 0;
    uint16_t pdata;
    flash_ee_data_read(address, &pdata);
    if (pdata != 0xFE)
    {
        return EE_CLIP_STATE_UNKNOWN;
    }
    else
    {
        ++address;
        flash_ee_data_read(address, &pdata);
        return (ee_clip_state_en)pdata;
    }
}
void set_clip_state_to_flash(ee_clip_state_en state)
{
    uint16_t address = 0;
    uint16_t data = state;
    flash_ee_data_write(address, 0xFE);
    ++address;
    flash_ee_data_write(address, data);
}
void set_clip1_opening(void)
{
    Clip.clip1_runtic_start_flag = true;
    gpio_bits_write(CLIP1_PIN1_PORT, CLIP1_PIN1, TRUE);
    gpio_bits_write(CLIP1_PIN2_PORT, CLIP1_PIN2, FALSE);
}
void set_clip1_closing(void)
{
    Clip.clip1_runtic_start_flag = true;
    gpio_bits_write(CLIP1_PIN1_PORT, CLIP1_PIN1, FALSE);
    gpio_bits_write(CLIP1_PIN2_PORT, CLIP1_PIN2, TRUE);
}
void set_clip2_opening(void)
{
    Clip.clip2_runtic_start_flag = true;
    gpio_bits_write(CLIP2_PIN1_PORT, CLIP2_PIN1, TRUE);
    gpio_bits_write(CLIP2_PIN2_PORT, CLIP2_PIN2, FALSE);
}
void set_clip2_closing(void)
{
    Clip.clip2_runtic_start_flag = true;
    gpio_bits_write(CLIP2_PIN1_PORT, CLIP2_PIN1, FALSE);
    gpio_bits_write(CLIP2_PIN2_PORT, CLIP2_PIN2, TRUE);
}
void clip1_stop(void)
{
    Clip.clip1_runtic_start_flag = false;
    Clip.clip1_runtick = 0;    
    gpio_bits_write(CLIP1_PIN1_PORT, CLIP1_PIN1, FALSE);
    gpio_bits_write(CLIP1_PIN2_PORT, CLIP1_PIN2, FALSE);
}
void clip2_stop(void)
{
    Clip.clip2_runtic_start_flag = false;
    Clip.clip2_runtick = 0;
    gpio_bits_write(CLIP2_PIN1_PORT, CLIP2_PIN1, FALSE);
    gpio_bits_write(CLIP2_PIN2_PORT, CLIP2_PIN2, FALSE);
}
void _check_normal_run(){
    if(Clip.clip1_runtic_start_flag){
        if (Clip.clip1_runtick > MS_2_TICK(NORMAL_MS)) {
            clip1_stop();
        } 
    }
    if(Clip.clip2_runtic_start_flag)
    {
        if (Clip.clip2_runtick > MS_2_TICK(NORMAL_MS)) {
            clip2_stop();
        } 
    }

}
void _check_clip1_init_closing(){
    if(Clip.clip1_runtic_start_flag){
        if (Clip.clip1_runtick > MS_2_TICK(INIT_CLOSE_MS)) {
            clip1_stop();//除停止外，同时刷新runtic计时
            set_clip1_opening();
            if(clip1_status()){
            Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
            }
            else{
            Clip.clip_cur_state = PROTO_CLIP1_STATE_INIT_OPENNING;
            }                       
        } 
    }
    if(Clip.clip2_runtic_start_flag)
    {
        if (Clip.clip2_runtick > MS_2_TICK(NORMAL_MS)) {
            clip2_stop();
        } 
    }

}
void _check_clip1_init_openning(){
    if(Clip.clip1_runtic_start_flag){
        if (Clip.clip1_runtick > MS_2_TICK(INIT_OPENNING_MS)) {
            clip1_stop();
        } 
    }
    if(Clip.clip2_runtic_start_flag)
    {
        if (Clip.clip2_runtick > MS_2_TICK(NORMAL_MS)) {
            clip2_stop();
        } 
    }
}
void _check_clip2_init_closing(){
    if(Clip.clip1_runtic_start_flag){
        if (Clip.clip1_runtick > MS_2_TICK(NORMAL_MS)) {
            clip1_stop();
        } 
    }
    if(Clip.clip2_runtic_start_flag)
    {
        if (Clip.clip2_runtick > MS_2_TICK(INIT_CLOSE_MS)) {
            clip2_stop();//除停止外，同时刷新runtic计时
            set_clip2_opening();
            if(clip2_status()){
            Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
            }
            else{
            Clip.clip_cur_state = PROTO_CLIP2_STATE_INIT_OPENNING;
            } 
        }
    }
}
void _check_clip2_init_openning(){
    if(Clip.clip1_runtic_start_flag){
        if (Clip.clip1_runtick > MS_2_TICK(NORMAL_MS)) {
            clip1_stop();
        } 
    }
    if(Clip.clip2_runtic_start_flag)
    {
        if (Clip.clip2_runtick > MS_2_TICK(INIT_OPENNING_MS)) {
            clip2_stop();
        } 
    }
}
void _check_all_init_closing(){
    if(Clip.clip1_runtic_start_flag){
        if (Clip.clip1_runtick > MS_2_TICK(INIT_CLOSE_MS)) {
            clip1_stop();
            if(clip2_run_status())
            {
                ;
            }else{
                if(clip1_status()){
                Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
                }
                else{
                Clip.clip_cur_state = PROTO_CLIP_STATE_INIT_ALL_OPENNING;
                }
                set_clip1_opening();
                set_clip2_opening();
            }
        } 
    }
    if(Clip.clip2_runtic_start_flag)
    {
        if (Clip.clip2_runtick > MS_2_TICK(INIT_CLOSE_MS)) {
            clip2_stop();
            if(clip1_run_status())
            {
                ;
            }
            else{
               if(clip2_status()){
                Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
                }
                else{
                Clip.clip_cur_state = PROTO_CLIP_STATE_INIT_ALL_OPENNING;
                }                
                set_clip1_opening();
                set_clip2_opening();
            }
        } 
    }
}
void _check_all_init_openning(){
    if(Clip.clip1_runtic_start_flag){
        if (Clip.clip1_runtick > MS_2_TICK(INIT_OPENNING_MS)) {
            clip1_stop();
        } 
    }
    if(Clip.clip2_runtic_start_flag)
    {
        if (Clip.clip2_runtick > MS_2_TICK(INIT_OPENNING_MS)) {
            clip2_stop();
        } 
    }    
}
int _init()
{
    Clip.clip1_runtick = 0;
    Clip.clip2_runtick = 0;
    Clip.clip_set_state = PROTO_CLIP_STATE_ALL_OPEN;
    // 读取flash
    if (get_clip_state_from_flash() == EE_CLIP_STATE_NURTRITION)
    {
        Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
        set_clip2_opening();
        set_clip_state_to_flash(EE_CLIP_STATE_UNKNOWN);
    }
    else if (get_clip_state_from_flash() == EE_CLIP_STATE_WATER)
    {
        Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
        set_clip1_opening();
        set_clip_state_to_flash(EE_CLIP_STATE_UNKNOWN);
    }
    else if (get_clip_state_from_flash() == EE_CLIP_STATE_ALL_OPEN)
    {
        Clip.clip_cur_state = PROTO_CLIP_STATE_ALL_OPEN;
        clip1_stop();
        clip2_stop();
    }
    else if (get_clip_state_from_flash() == EE_CLIP_STATE_ALL_CLOSE)
    {
        Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
        set_clip1_opening();
        set_clip2_opening();
        set_clip_state_to_flash(EE_CLIP_STATE_UNKNOWN);
    }
    // 读取失败进行初始化
    else
    {
        // 已经在档住的情况下，直接关闭
        if (clip1_status() == true && clip2_status() == true)
        {
            Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
            set_clip_state_to_flash(EE_CLIP_STATE_UNKNOWN);
            set_clip1_opening();
            set_clip2_opening();
        }
        else if (clip1_status() == true && clip2_status() == false)
        {
            Clip.clip_cur_state = PROTO_CLIP2_STATE_INIT_CLOSING;

            set_clip_state_to_flash(EE_CLIP_STATE_UNKNOWN);
            set_clip1_opening();
            set_clip2_closing();
        }
        else if (clip1_status() == false && clip2_status() == true)
        {
            Clip.clip_cur_state = PROTO_CLIP1_STATE_INIT_CLOSING;
            set_clip_state_to_flash(EE_CLIP_STATE_UNKNOWN);
            set_clip1_closing();
            set_clip2_opening();
        }
        else if (clip1_status() == false && clip2_status() == false)
        {
            Clip.clip_cur_state = PROTO_CLIP_STATE_INIT_ALL_CLOSEING;
            set_clip_state_to_flash(EE_CLIP_STATE_UNKNOWN);
            set_clip1_closing();
            set_clip2_closing();
        }
    }
    return 0;
}
void _run()
{
    if (Clip.clip1_runtic_start_flag || Clip.clip2_runtic_start_flag)
    {
        if(Clip.clip1_runtic_start_flag)
            Clip.clip1_runtick++;
        if(Clip.clip2_runtic_start_flag)                    
            Clip.clip2_runtick++;
    }
    else
    {
        if (Clip.clip_set_state != Clip.clip_cur_state)
        {
            if (Clip.clip_set_state == PROTO_CLIP_STATE_NURTRITION)
            {
                switch (Clip.clip_cur_state)
                {
                case PROTO_CLIP_STATE_ALL_OPEN:
                    Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
                    set_clip_state_to_flash(EE_CLIP_STATE_UNKNOWN);
                    set_clip2_opening();

                    break;
                case PROTO_CLIP_STATE_ALL_CLOSE:
                    Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
                    set_clip_state_to_flash(EE_CLIP_STATE_UNKNOWN);
                    set_clip1_closing();
                    break;
                case PROTO_CLIP_STATE_WATER:
                    Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
                    set_clip_state_to_flash(EE_CLIP_STATE_UNKNOWN);
                    set_clip1_closing();
                    set_clip2_opening();
                    break;
                case PROTO_CLIP_STATE_NURTRITION:
                    break;
                default:
                    break;
                }
            }
            else if (Clip.clip_set_state == PROTO_CLIP_STATE_WATER)
            {
                switch (Clip.clip_cur_state)
                {
                case PROTO_CLIP_STATE_ALL_OPEN:
                    Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
                    set_clip_state_to_flash(EE_CLIP_STATE_UNKNOWN);
                    set_clip1_opening();
                    break;
                case PROTO_CLIP_STATE_ALL_CLOSE:
                    Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
                    set_clip_state_to_flash(EE_CLIP_STATE_UNKNOWN);
                    set_clip2_closing();
                    break;
                case PROTO_CLIP_STATE_WATER:
                    break;
                case PROTO_CLIP_STATE_NURTRITION:
                    Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
                    set_clip_state_to_flash(EE_CLIP_STATE_UNKNOWN);
                    set_clip1_opening();
                    set_clip2_closing();
                    break;
                default:
                    break;
                }
            }
            else if (Clip.clip_set_state == PROTO_CLIP_STATE_ALL_OPEN)
            {
                switch (Clip.clip_cur_state)
                {
                case PROTO_CLIP_STATE_ALL_OPEN:
                    break;
                case PROTO_CLIP_STATE_ALL_CLOSE:
                    Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
                    set_clip_state_to_flash(EE_CLIP_STATE_UNKNOWN);

                    set_clip1_closing();
                    set_clip2_closing();
                    break;
                case PROTO_CLIP_STATE_WATER:
                    Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
                    set_clip_state_to_flash(EE_CLIP_STATE_UNKNOWN);

                    set_clip1_closing();
                    break;
                case PROTO_CLIP_STATE_NURTRITION:
                    Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
                    set_clip_state_to_flash(EE_CLIP_STATE_UNKNOWN);

                    set_clip2_closing();
                    break;
                default:
                    break;
                }
            }
            else if (Clip.clip_set_state == PROTO_CLIP_STATE_ALL_CLOSE)
            {
                switch (Clip.clip_cur_state)
                {
                case PROTO_CLIP_STATE_ALL_OPEN:
                    Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
                    set_clip_state_to_flash(EE_CLIP_STATE_UNKNOWN);

                    set_clip1_opening();
                    set_clip2_closing();
                    break;
                case PROTO_CLIP_STATE_ALL_CLOSE:
                    break;
                case PROTO_CLIP_STATE_WATER:
                    Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
                    set_clip_state_to_flash(EE_CLIP_STATE_UNKNOWN);

                    set_clip2_opening();
                    break;
                case PROTO_CLIP_STATE_NURTRITION:
                    Clip.clip_cur_state = PROTO_CLIP_STATE_NORMAL_RUN;
                    set_clip_state_to_flash(EE_CLIP_STATE_UNKNOWN);

                    set_clip1_opening(); 
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            ;
        }
    }
    switch (Clip.clip_cur_state)
    {
    case PROTO_CLIP_STATE_NORMAL_RUN:
        _check_normal_run();
        break;
    case PROTO_CLIP1_STATE_INIT_CLOSING:
        _check_clip1_init_closing();
        break;
    case PROTO_CLIP1_STATE_INIT_OPENNING:
        _check_clip1_init_openning();
        break;
    case PROTO_CLIP2_STATE_INIT_CLOSING:
        _check_clip2_init_closing();
        break;
    case PROTO_CLIP2_STATE_INIT_OPENNING:
        _check_clip2_init_openning();
    case PROTO_CLIP_STATE_INIT_ALL_CLOSEING:
        _check_all_init_closing();
        break;
    case PROTO_CLIP_STATE_INIT_ALL_OPENNING:
        _check_all_init_openning();
        break;
    default:
        break;
    }
}
void _clip_state_update(){
    if(Clip.clip1_cur_state == CLIP_STATE_OPEN && Clip.clip2_cur_state == CLIP_STATE_OPEN)
    {
        Clip.clip_cur_state = PROTO_CLIP_STATE_ALL_OPEN;
    }
    else if(Clip.clip1_cur_state == CLIP_STATE_CLOSE && Clip.clip2_cur_state == CLIP_STATE_CLOSE)
    {
        Clip.clip_cur_state = PROTO_CLIP_STATE_ALL_CLOSE;
    }
    else if(Clip.clip1_cur_state == CLIP_STATE_OPEN && Clip.clip2_cur_state == CLIP_STATE_CLOSE)
    {
        Clip.clip_cur_state = PROTO_CLIP_STATE_NURTRITION;
    }
    else if(Clip.clip1_cur_state == CLIP_STATE_CLOSE && Clip.clip2_cur_state == CLIP_STATE_OPEN)
    {
        Clip.clip_cur_state = PROTO_CLIP_STATE_WATER;
    }
    else{
        ;
    }
}
void clip_loop_10ms()
{
    if (Clip.clip_cur_state == PROTO_CLIP_STATE_INIT)
    {
        _init();
    }
    else
    {
        _run();
    }
    _clip_state_update();
}

void EXINT15_10_IRQHandler(void)
{
    if (exint_flag_get(EXINT_LINE_14) != RESET)
    {
        exint_flag_clear(EXINT_LINE_14);
        if(Clip.clip1_cur_state == CLIP_STATE_OPENING){
            clip1_stop();
            Clip.clip1_cur_state = CLIP_STATE_OPEN;
        }
        else if(Clip.clip1_cur_state == CLIP_STATE_CLOSING){
            clip1_stop();
            Clip.clip1_cur_state = CLIP_STATE_CLOSE;

        }
        else if(Clip.clip1_cur_state == CLIP_STATE_INIT_OPENNING){
            clip1_stop();
            Clip.clip1_cur_state = CLIP_STATE_OPEN;

        }
        else if(Clip.clip1_cur_state == CLIP_STATE_INIT_CLOSING){
            clip1_stop();
            Clip.clip1_cur_state = CLIP_STATE_ERR;
            
        }        
    }
    if (exint_flag_get(EXINT_LINE_15) != RESET)
    {
        exint_flag_clear(EXINT_LINE_15);
        if(Clip.clip2_cur_state == CLIP_STATE_OPENING){
            clip1_stop();
            Clip.clip2_cur_state = CLIP_STATE_OPEN;
        }
        else if(Clip.clip2_cur_state == CLIP_STATE_CLOSING){
            clip1_stop();
            Clip.clip2_cur_state = CLIP_STATE_CLOSE;

        }
        else if(Clip.clip2_cur_state == CLIP_STATE_INIT_OPENNING){
            clip1_stop();
            Clip.clip2_cur_state = CLIP_STATE_OPEN;

        }
        else if(Clip.clip2_cur_state == CLIP_STATE_INIT_CLOSING){
            clip1_stop();
            Clip.clip2_cur_state = CLIP_STATE_ERR;
            
        }          
    }
}

