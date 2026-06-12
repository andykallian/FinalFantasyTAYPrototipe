#include <snes.h>
#include "src/player.h"
#include "src/overworld.h"
#include "src/airship.h"
#include "src/airship_subscreen.h"
#include "src/enterprise.h"
#include "src/heros/ceodore_def.h"
#include "src/splash.h"

extern u16 m7sx, m7sy;

s16 cam_x = 1576;
s16 cam_y = 2176;
u16 zoom  = 0x0100;

int main(void)
{
    
    // initDreamsSplash();
    // updateDreamsSplash();
    // consoleInit();

    oamInit();
    oamInitDynamicSprite(0x6000, 0x8000, 0, 0, OBJ_SIZE16_L32);

    m7sx = zoom;
    m7sy = zoom;

    overworldInit(cam_x, cam_y, zoom);

    setScreenOn();
    REG_INIDISP = 0x80;

    playerInit(cam_x, cam_y, &PLAYER_CEODORE);
    enterpriseInit();

    REG_INIDISP = 0x0F;

    while(1)
    {
        playerUpdate();
        enterpriseUpdate();

        if(enterprise_liftoff_done)
        {
            enterprise_liftoff_done = 0;
            airshipEnter();
            enterpriseUpdate();
            enterpriseDraw(cam_x, cam_y);
            enterpriseFlush();
            oamUpdate();
            fadeIn();
        }

        extern u8 airship_wants_to_land;
        if(airship_wants_to_land)
        {
            airship_wants_to_land = 0;
            airshipExit();
            enterpriseStartLanding();
            enterpriseDraw(cam_x, cam_y);
            enterpriseFlush();
            oamUpdate();
            fadeIn();
        }

        if(enterprise_landing_done)
        {
            enterprise_landing_done = 0;
            enterpriseStartUnboarding();
        }

        extern u8 enterprise_unboarding_done;
        if(enterprise_unboarding_done)
        {
            enterprise_unboarding_done = 0;

            extern u8 player_visible;
            extern u8 playerDir;
            extern u16 currentFrame;
            player_visible = 1;
            playerDir = DIR_DOWN;
            currentFrame = FRAME_FRONT_IDLE;
        }

        playerDraw();
        enterpriseDraw(cam_x, cam_y);

        overworldPrepare(cam_x, cam_y);
        overworldAnimateWaterTick();

        if(airship_state == AIRSHIP_ON)
            airshipFlush(cam_x, cam_y);

        WaitForVBlank();

        if(airship_state == AIRSHIP_OFF)
            overworldScroll(cam_x, cam_y);
        else
            airshipVBlank();

        overworldFlush();
        overworldAnimateWaterFlush();
        playerFlush();
        enterpriseFlush();
        oamUpdate();
    }

    return 0;
}