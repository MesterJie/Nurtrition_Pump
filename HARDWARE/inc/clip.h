#ifndef __CLIP_H
#define __CLIP_H
#include "stdbool.h"
#include "at32f415.h"


void clip_init(void);
bool clip1_status(void);
bool clip2_status(void);
bool clip1_run_status(void);
bool clip2_run_status(void);
#endif

