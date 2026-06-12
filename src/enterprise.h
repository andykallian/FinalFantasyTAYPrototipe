#ifndef ENTERPRISE_H
#define ENTERPRISE_H

#include <snes.h>

// =========================================================
// POSES
// =========================================================
#define ENTERPRISE_POSE_GROUND   0
#define ENTERPRISE_POSE_FLY_ALT  1
#define ENTERPRISE_POSE_UP_A     2
#define ENTERPRISE_POSE_UP_B     3
#define ENTERPRISE_POSE_DOWN_A   4
#define ENTERPRISE_POSE_DOWN_B   5

// =========================================================
// POSIÇÃO NO MUNDO (Modificado de #define para extern)
// =========================================================
extern s16 ENTERPRISE_WORLD_X;
extern s16 ENTERPRISE_WORLD_Y;

// =========================================================
// ESTADO DA NAVE
// =========================================================
typedef enum {
    ENTERPRISE_STATE_GROUND,
    ENTERPRISE_STATE_BOARDING,
    ENTERPRISE_STATE_LIFTOFF,
    ENTERPRISE_STATE_LANDING,
    ENTERPRISE_STATE_UNBOARDING // <--- Adicione este
} EnterpriseState;

extern EnterpriseState enterprise_state;
extern u8 enterprise_boarding_done;
extern u8 enterprise_liftoff_done;
extern u8 enterprise_landing_done; // Nova flag exposta para o player.c

// =========================================================
// FUNÇÕES
// =========================================================
void enterpriseInit(void);
void enterpriseUpdate(void);
void enterpriseFlush(void);
void enterpriseDraw(s16 cam_x, s16 cam_y);
void enterpriseSetPose(u8 pose);
void enterpriseStartBoarding(void);
void enterpriseStartLiftoff(void);
void enterpriseStartLanding(void); // Nova função declarada

#endif