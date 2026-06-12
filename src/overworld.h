#ifndef OVERWORLD_H
#define OVERWORLD_H

#include <snes.h>

extern u8 water_timer;


void overworldInit(s16 cam_x, s16 cam_y, u16 zoom);
void overworldScroll(s16 cam_x, s16 cam_y);
void overworldPrepare(s16 cam_x, s16 cam_y);
void overworldFlush(void);
void overworldScroll(s16 cam_x, s16 cam_y);
void overworldRestoreZoom(void);
void overworldAnimateWaterTick(void);
void overworldAnimateWaterFlush(void);
void overworldGetScroll(s16 cam_x, s16 cam_y, s16 *sx,s16 *sy);

#endif