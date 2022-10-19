#include "GameAPI/Game.h"
#include "TitleLogo.h"
#include "TitleSonic.h"
#include "TitleSetup.h"
#include "../Menu/DemoMenu.h"
#include "../Global/APICallback.h"
#include "../Global/Music.h"

ObjectDemoMenu *DemoMenu;
ObjectTitleSetup *TitleSetup;
ObjectTitleSonic *TitleSonic;
ObjectTitleLogo *TitleLogo;
ObjectMusic *Music;

void TitleSetup_State_WaitForSonic_Hook(void)
{
    RSDK_THIS(TitleSetup);

    if (self->timer <= 0) {
        self->stateDraw = StateMachine_None;
        self->state = TitleSetup_State_SetupLogo_Hook;
    }
    else {
        self->timer -= 16;
    }
}

void TitleSetup_State_SetupLogo_Hook(void) 
{
    RSDK_THIS(TitleSetup);

    if (++self->timer == 150) {
        foreach_all(TitleLogo, titleLogo)
        {
            if (titleLogo->type == TITLELOGO_PRESSSTART) {
                titleLogo->active  = ACTIVE_NORMAL;
                titleLogo->visible = true;

#if MANIA_USE_PLUS
                Entity *store     = SceneInfo->entity;
                SceneInfo->entity = (Entity *)titleLogo;
                TitleLogo_SetupPressStart();
                SceneInfo->entity = store;
#endif
            }
        }
        self->timer = 0;
        self->state = TitleSetup_State_WaitForEnter_Hook;
    }
}

void TitleSetup_State_WaitForEnter_Hook(void)
{
    RSDK_THIS(TitleSetup);

    bool32 anyButton = ControllerInfo->keyA.press || ControllerInfo->keyB.press || ControllerInfo->keyC.press || ControllerInfo->keyX.press
                       || ControllerInfo->keyY.press || ControllerInfo->keyZ.press || ControllerInfo->keyStart.press
                       || ControllerInfo->keySelect.press;
#if MANIA_USE_PLUS
        int32 id = API_GetFilteredInputDeviceID(false, false, 5);
#else
        int32 id = API_GetFilteredInputDeviceID(INPUT_NONE);
#endif
        API_ResetInputSlotAssignments();
        API_AssignInputSlotToDevice(CONT_P1, id);

    if (anyButton) {
        RSDK.StopChannel(Music->channelID);
        RSDK.PlaySfx(TitleSetup->sfxMenuAccept, false, 0xFF);
        self->state = TitleSetup_State_LogoRise;
        self->timer = 0;
    }
}

void TitleSetup_State_LogoRise(void)
{
    RSDK_THIS(TitleSetup);
    if (++self->timer == 1) {
        self->timer = 0;

        foreach_all(TitleSonic, titleSonic) {
            if (titleSonic)
                titleSonic->position.y -= 0x100000;

            if (titleSonic->position.y <= -0x80000)
                destroyEntity(titleSonic);
        }

        foreach_all(TitleLogo, titleLogo) {
            if (titleLogo)
                titleLogo->position.y -= 0x100000;

            if (titleLogo->position.y <= -0x750000) {
                destroyEntity(titleLogo);
                self->state = TitleSetup_State_CreateDemoMenu;
                self->timer = 0;
            }
        }
    }
}

void TitleSetup_State_CreateDemoMenu(void)
{
    RSDK_THIS(TitleSetup);

    if (++self->timer == 20) {
        RSDK.PlayStream("MainMenu.ogg", Music->channelID, 0, 198430, false);
        CREATE_ENTITY(DemoMenu, NULL, 0, 0);
        self->state = TitleSetup_Dummy;
    }
}

void TitleSetup_Dummy(void) {}