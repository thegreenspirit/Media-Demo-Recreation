#ifndef OBJ_PAUSEMENU_H
#define OBJ_PAUSEMENU_H

#include "GameAPI/Game.h"
#include "../Menu/UIControl.h"
#include "../Menu/UIButton.h"

#define PAUSEMENU_BUTTON_COUNT (3)

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 sfxBleep;
    uint16 sfxAccept;
    bool32 disableEvents;
    bool32 controllerDisconnect;
    bool32 forcedDisconnect;
    bool32 signOutDetected;
#if MANIA_USE_PLUS
    bool32 plusChanged;
#endif
    bool32 activeChannels[0x10];
#if MANIA_USE_PLUS
    uint16 tintLookupTable[0x10000];
#endif
    uint16 aniFrames;
} ObjectPauseMenu;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int32 timer;
    int32 tintAlpha;
    Vector2 headerPos;
    Vector2 yellowTrianglePos;
    EntityUIControl *manager;
    uint8 triggerPlayer;
    bool32 disableRestart;
    int32 buttonCount;
    uint8 buttonIDs[PAUSEMENU_BUTTON_COUNT];
    void (*buttonActions[PAUSEMENU_BUTTON_COUNT])(void);
    EntityUIButton* buttonPtrs[PAUSEMENU_BUTTON_COUNT];
    int32 paused;
    int32 fadeTimer;
    bool32 (*disconnectCheck)(void);
    int32 forcePaused;
    Animator animator;
    void (*fadeoutCB)(void);
    int32 unused1;
    int32 unused2; // these may possibly be leftover or editor things
} EntityPauseMenu;

// Object Struct
extern ObjectPauseMenu *PauseMenu;

// Regular states
void PauseMenu_Update(void);
void PauseMenu_LateUpdate(void);
void PauseMenu_StageLoad(void);

// Functions
void PauseMenu_ExitButton(void);
void (*PauseMenu_ExitButtonCB)(void);
void PauseMenu_RestartButton(void);
void (*PauseMenu_RestartButtonCB)(void);
void PauseMenu_Draw_Regular(void);
void (*PauseMenu_Draw_RegularPause)(void);
void PauseMenu_DrawPause(void);
void (*PauseMenu_DrawPauseMenu)(void);
void PauseMenu_ExitFade(void);
void (*PauseMenu_ExitFadeCB)(void);
void PauseMenu_State_SetupButton(void);
void (*PauseMenu_State_SetupButtons)(void);
void PauseMenu_AddUIButton(uint8 id, void* action);
void (*PauseMenu_AddButton)(void);

void (*PauseMenu_RestartFadeCB)(void);
void (*PauseMenu_ActionCB_Button)(void);
void (*PauseMenu_State_HandleFadeout)(void);
void (*PauseMenu_State_SetupButtons)(void);
void (*PauseMenu_SetupMenu)(void);
void (*PauseMenu_PauseSound)(void);
void (*PauseMenu_StopSound)(void);
void (*PauseMenu_IsDisconnected)(void);
void (*PauseMenu_State_ForcedPause)(void);
void (*PauseMenu_Draw_ForcePause)(void);
void (*PauseMenu_State_StartPause)(void);
void (*PauseMenu_ResumeButtonCB)(void);

#endif //! OBJ_PAUSEMENU_H