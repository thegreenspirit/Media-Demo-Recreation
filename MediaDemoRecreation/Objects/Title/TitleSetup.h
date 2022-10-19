#ifndef OBJ_TITLESETUP_H
#define OBJ_TITLESETUP_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    bool32 useAltIntroMusic;
    uint16 aniFrames;
    uint16 sfxMenuBleep;
    uint16 sfxMenuAccept;
    uint16 sfxRing;
#if MANIA_USE_PLUS
    uint8 cheatCode[8];
#endif
} ObjectTitleSetup;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int32 timer;
    Vector2 drawPos;
    int32 touched;
    Animator animator;
} EntityTitleSetup;

// Object Struct
extern ObjectTitleSetup *TitleSetup;

// Extra Entity Functions
void (*TitleSetup_State_WaitForSonic)(void);
void TitleSetup_State_WaitForSonic_Hook(void);
void (*TitleSetup_State_SetupLogo)(void);
void TitleSetup_State_SetupLogo_Hook(void);
void (*TitleSetup_State_WaitForEnter)(void);
void TitleSetup_State_WaitForEnter_Hook(void);

void TitleSetup_State_LogoRise(void);
void TitleSetup_State_CreateDemoMenu(void);
void TitleSetup_Dummy(void);

void (*TitleSetup_State_FadeToMenu)(void);
void (*TitleSetup_State_FadeBlack)(void);

#endif //! OBJ_TITLESETUP_H
