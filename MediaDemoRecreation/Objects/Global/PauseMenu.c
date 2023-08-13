#include "GameAPI/Game.h"
#include "PauseMenu.h"
#include "Music.h"
#include "Player.h"
#include "StarPost.h"
#include "SaveGame.h"
#include "../Menu/UIButton.h"
#include "../Menu/UIControl.h"

ObjectPauseMenu* PauseMenu;
ObjectUIControl* UIControl;

void PauseMenu_Update(void)
{
    RSDK_THIS(PauseMenu);

    StateMachine_Run(self->state);

    self->position.x = (ScreenInfo->position.x + ScreenInfo->center.x) << 16;
    self->position.y = (ScreenInfo->position.y + ScreenInfo->center.y) << 16;

    if (self->manager) {
        self->manager->position.x = self->position.x;
        self->manager->position.y = self->position.y;
    }
}

void PauseMenu_LateUpdate(void)
{
    RSDK_THIS(PauseMenu);

    if (self->state) {
        if (RSDK.ChannelActive(Music->channelID))
            RSDK.PauseChannel(Music->channelID);
    }
    else {
        StateMachine(state) = RSDK_GET_ENTITY(self->triggerPlayer, Player)->state;

        if (state == Player_State_Death || state == Player_State_Drown) {
            destroyEntity(self);
        }
        else {
            self->visible = true;
            self->drawGroup = DRAWGROUP_COUNT - 1;
            RSDK.SetEngineState(ENGINESTATE_FROZEN);
            RSDK.SetSpriteAnimation(PauseMenu->aniFrames, 3, &self->animator, true, 0);
            PauseMenu_PauseSound();
            self->state = PauseMenu_State_SetupButton;
        }
    }
}

void PauseMenu_StageLoad(void)
{
    PauseMenu->active = ACTIVE_ALWAYS;

    PauseMenu->sfxBleep = RSDK.GetSfx("Global/MenuBleep.wav");
    PauseMenu->sfxAccept = RSDK.GetSfx("Global/MenuAccept.wav");
    PauseMenu->aniFrames = RSDK.LoadSpriteAnimation("Global/Pause.bin", SCOPE_STAGE);

    PauseMenu->disableEvents = false;
    PauseMenu->controllerDisconnect = false;
    PauseMenu->forcedDisconnect = false;
    PauseMenu->signOutDetected = false;
#if MANIA_USE_PLUS
    PauseMenu->plusChanged = false;

    if (!globals->hasPlusInitial) {
        globals->lastHasPlus = API.CheckDLC(DLC_PLUS);
        globals->hasPlusInitial = true;
    }
#endif

    for (int32 i = 0; i < CHANNEL_COUNT; ++i) {
        PauseMenu->activeChannels[i] = false;
    }
}

void PauseMenu_RestartButton(void)
{
    RSDK_GET_ENTITY(SLOT_PAUSEMENU, PauseMenu);

    if (StarPost) {
        StarPost->postIDs[0] = 0;
        StarPost->postIDs[1] = 0;
        StarPost->postIDs[2] = 0;
        StarPost->postIDs[3] = 0;
    }
    RSDK.StopChannel(Music->channelID);

    int32 x = (ScreenInfo->position.x + ScreenInfo->center.x) << 16;
    int32 y = (ScreenInfo->position.y + ScreenInfo->center.y) << 16;
    EntityPauseMenu* fadeout = CREATE_ENTITY(PauseMenu, INT_TO_VOID(true), x, y);
    fadeout->fadeoutCB = PauseMenu_RestartFadeCB;
    fadeout->state = PauseMenu_State_HandleFadeout;
}

void PauseMenu_ExitButton(void)
{
    RSDK_GET_ENTITY(SLOT_PAUSEMENU, PauseMenu);

    globals->recallEntities = false;
    globals->initCoolBonus = false;

    if (StarPost) {
        StarPost->postIDs[0] = 0;
        StarPost->postIDs[1] = 0;
        StarPost->postIDs[2] = 0;
        StarPost->postIDs[3] = 0;
    }

    SaveRAM* saveRAM = SaveGame_GetSaveRAM();
    saveRAM->lives = 3;
    saveRAM->score = 0;
    saveRAM->score1UP = 0;
    RSDK.StopChannel(Music->channelID);

    int32 x = (ScreenInfo->position.x + ScreenInfo->center.x) << 16;
    int32 y = (ScreenInfo->position.y + ScreenInfo->center.y) << 16;
    EntityPauseMenu* fadeout = CREATE_ENTITY(PauseMenu, INT_TO_VOID(true), x, y);
    fadeout->fadeoutCB = PauseMenu_ExitFade;
    fadeout->state = PauseMenu_State_HandleFadeout;
}

void PauseMenu_ExitFade(void)
{
    if (StarPost) {
        StarPost->postIDs[0] = 0;
        StarPost->postIDs[1] = 0;
        StarPost->postIDs[2] = 0;
        StarPost->postIDs[3] = 0;
    }
    globals->specialRingID = 0;

    RSDK.SetScene("Presentation", "Thanks For Playing");
    PauseMenu_StopSound();
    RSDK.LoadScene();
}

void PauseMenu_AddUIButton(uint8 id, uint8 id2, void* action)
{
    RSDK_THIS(PauseMenu);

    int32 buttonID = self->buttonCount;
    if (buttonID < PAUSEMENU_BUTTON_COUNT) {
        self->buttonIDs[buttonID] = id;
        self->buttonActions[buttonID] = action;

        int32 buttonSlot = self->buttonCount + 18;
        RSDK.ResetEntitySlot(buttonSlot, UIButton->classID, NULL);
        EntityUIButton* button = RSDK_GET_ENTITY(buttonSlot, UIButton);

        button->position.x = (ScreenInfo->position.x + ScreenInfo->center.x) << 16;
        button->position.y = (ScreenInfo->position.y + ScreenInfo->center.y) << 16;
        RSDK.SetSpriteAnimation(PauseMenu->aniFrames, 0, &button->animator, false, id);
        RSDK.SetSpriteAnimation(PauseMenu->aniFrames, 4, &button->highlightAnimator, false, id2);
        button->actionCB = PauseMenu_ActionCB_Button;
        button->size.x = 0;
        button->size.y = 0;
        button->bgEdgeSize = 0;
        button->align = UIBUTTON_ALIGN_CENTER;
        button->drawGroup = self->drawGroup;
        button->active = ACTIVE_ALWAYS;
        self->buttonPtrs[buttonID] = button;
        ++self->buttonCount;
    }
}

void PauseMenu_State_SetupButton(void)
{
    RSDK_THIS(PauseMenu);

    self->timer = 0;
    PauseMenu->forcedDisconnect = false;

#if MANIA_USE_PLUS
    if (PauseMenu->controllerDisconnect || PauseMenu->signOutDetected || PauseMenu->plusChanged) {
#else
    if (PauseMenu->controllerDisconnect || PauseMenu->signOutDetected) {
#endif
        if (PauseMenu->controllerDisconnect) {
            self->disconnectCheck = PauseMenu_IsDisconnected;
            self->state = PauseMenu_State_ForcedPause;
            self->stateDraw = PauseMenu_Draw_ForcePause;
        }
    }
    else {
        RSDK.PlaySfx(PauseMenu->sfxAccept, false, 255);

        PauseMenu_AddUIButton(0, 0, PauseMenu_ResumeButtonCB);

        if (!self->disableRestart)
            PauseMenu_AddUIButton(2, 1, PauseMenu_RestartButton);

        PauseMenu_AddUIButton(4, 2, PauseMenu_ExitButton);

        PauseMenu_SetupMenu();

        self->state = PauseMenu_State_StartPause;
        self->stateDraw = PauseMenu_Draw_RegularPause;
    }
    StateMachine_Run(self->state);
}

void PauseMenu_DrawPause(void)
{
    RSDK_THIS(PauseMenu);

    Vector2 drawPos;
    // Draw the Pause BG
    drawPos.x = self->position.x + ScreenInfo->center.x;
    drawPos.y = self->position.y + ScreenInfo->center.y;
    RSDK.DrawSprite(&self->animator, &drawPos, false);
}

bool32 PauseMenu_Draw_Regular(bool32 skipState)
{
    RSDK_THIS(PauseMenu);

    if (self->state != PauseMenu_State_HandleFadeout) {
        PauseMenu_DrawPause();
    }
	return true;
}