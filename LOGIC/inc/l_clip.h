#ifndef __L_CLIP_H
#define __L_CLIP_H
#include "at32f415.h"
#include "stdbool.h"
//ֹҺ��״̬
typedef enum{
    PROTO_CLIP_STATE_INIT,
    PROTO_CLIP_STATE_ALL_CLOSE, 
    PROTO_CLIP_STATE_ALL_OPEN,
    PROTO_CLIP_STATE_NURTRITION,   
    PROTO_CLIP_STATE_WATER,   
    PROTO_CLIP_STATE_ERROR,  

    PROTO_CLIP_STATE_NORMAL_RUN,

    PROTO_CLIP1_STATE_INIT_CLOSING,
    PROTO_CLIP1_STATE_INIT_OPENNING,    
    PROTO_CLIP2_STATE_INIT_CLOSING,
    PROTO_CLIP2_STATE_INIT_OPENNING,
    PROTO_CLIP_STATE_INIT_ALL_CLOSEING,
    PROTO_CLIP_STATE_INIT_ALL_OPENNING,   
}clip_state_en;
typedef enum{
    CLIP_STATE_OPENING,
    CLIP_STATE_CLOSING,
    CLIP_STATE_OPEN,
    CLIP_STATE_CLOSE,

    CLIP_STATE_ERR,
    CLIP_STATE_INIT_OPENNING,
    CLIP_STATE_INIT_CLOSING,
}sig_clip_state_en;
typedef enum{
    EE_CLIP_STATE_UNKNOWN,
    EE_CLIP_STATE_NURTRITION,
    EE_CLIP_STATE_WATER,
    EE_CLIP_STATE_ALL_OPEN,
    EE_CLIP_STATE_ALL_CLOSE,
}ee_clip_state_en;

typedef struct{
    clip_state_en clip_cur_state;    
    clip_state_en clip_set_state;  
    sig_clip_state_en clip1_cur_state;
    sig_clip_state_en clip2_cur_state;
    bool clip1_runtic_start_flag;
    bool clip2_runtic_start_flag;
    uint32_t clip1_runtick;     
    uint32_t clip2_runtick; 
}Clip_t;

extern Clip_t Clip;
ee_clip_state_en get_clip_state_from_flash(void);
void set_clip_state_to_flash(ee_clip_state_en state);
#endif
