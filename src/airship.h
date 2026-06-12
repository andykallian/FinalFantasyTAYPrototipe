#ifndef AIRSHIP_H
#define AIRSHIP_H

#include <snes.h>

typedef enum {
    AIRSHIP_OFF = 0,
    AIRSHIP_ON  = 1
} AirshipState;

extern AirshipState airship_state;
extern s32 PerspectiveDY[];

void airshipEnter(void);
void airshipExit(void);
void airshipFlush(s16 cam_x, s16 cam_y);
void fadeIn(void);
void fadeOut(void);


#endif