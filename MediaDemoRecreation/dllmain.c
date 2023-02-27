#include "GameAPI/Game.h"
#include "Objects/Global/ActClear.h"
#include "Objects/Global/DebugMode.h"
#include "Objects/Global/GameOver.h"
#include "Objects/Global/ItemBox.h"
#include "Objects/Global/Music.h"
#include "Objects/Global/Zone.h"
#include "Objects/Global/PauseMenu.h"
#include "Objects/Global/Player.h"
#include "Objects/Global/SaveGame.h"
#include "Objects/Global/StarPost.h"
#include "Objects/Menu/DemoMenu.h"
#include "Objects/Menu/UIPicture.h"
#include "Objects/Menu/UIButton.h"
#include "Objects/Title/TitleSetup.h"
#include "Objects/Title/TitleSonic.h"
#include "Objects/Title/TitleLogo.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void) 
{ 
    // Overload regular states
    MOD_REGISTER_OBJ_OVERLOAD(ActClear, NULL, NULL, NULL, ActClear_Draw, ActClear_Create, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(UIButton, UIButton_Update, NULL, NULL, UIButton_Draw, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(UIPicture, NULL, NULL, NULL, NULL, UIPicture_Create, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(Player, NULL, NULL, NULL, NULL, NULL, Player_StageLoad, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(StarPost, StarPost_Update, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(PauseMenu, PauseMenu_Update, PauseMenu_LateUpdate, NULL, NULL, NULL, PauseMenu_StageLoad, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(ItemBox, NULL, NULL, NULL, NULL, NULL, ItemBox_StageLoad, NULL, NULL, NULL);

    // Register object hooks
    MOD_REGISTER_OBJECT_HOOK(DemoMenu);
    MOD_REGISTER_OBJECT_HOOK(TitleSetup);
    MOD_REGISTER_OBJECT_HOOK(TitleLogo);
    MOD_REGISTER_OBJECT_HOOK(TitleSonic);
    MOD_REGISTER_OBJECT_HOOK(Music);
    MOD_REGISTER_OBJECT_HOOK(Player);
    MOD_REGISTER_OBJECT_HOOK(Zone);
    MOD_REGISTER_OBJECT_HOOK(ActClear);
    MOD_REGISTER_OBJECT_HOOK(PauseMenu);
    MOD_REGISTER_OBJECT_HOOK(UIButton);

    // Get public functions
    // ActClear
    ActClear_DrawTime                 = Mod.GetPublicFunction(NULL, "ActClear_DrawTime");
    ActClear_DrawNumbers              = Mod.GetPublicFunction(NULL, "ActClear_DrawNumbers");
    ActClear_State_SaveGameProgress   = Mod.GetPublicFunction(NULL, "ActClear_State_SaveGameProgress");
    ActClear_State_EnterText          = Mod.GetPublicFunction(NULL, "ActClear_State_EnterText");
    // DebugMode
    DebugMode_AddObject               = Mod.GetPublicFunction(NULL, "DebugMode_AddObject");
    // GameOver
    GameOver_State_ExitLetters        = Mod.GetPublicFunction(NULL, "GameOver_State_ExitLetters");
    // ItemBox
    ItemBox_DebugDraw                 = Mod.GetPublicFunction(NULL, "ItemBox_DebugDraw");
    ItemBox_DebugSpawn                = Mod.GetPublicFunction(NULL, "ItemBox_DebugSpawn");
    // PauseMenu (the public function maniac)
    PauseMenu_DrawPauseMenu           = Mod.GetPublicFunction(NULL, "PauseMenu_DrawPauseMenu");
    PauseMenu_Draw_RegularPause       = Mod.GetPublicFunction(NULL, "PauseMenu_Draw_RegularPause");
    PauseMenu_State_SetupButtons      = Mod.GetPublicFunction(NULL, "PauseMenu_State_SetupButtons");
    PauseMenu_SetupMenu               = Mod.GetPublicFunction(NULL, "PauseMenu_SetupMenu");
    PauseMenu_PauseSound              = Mod.GetPublicFunction(NULL, "PauseMenu_PauseSound");
    PauseMenu_StopSound               = Mod.GetPublicFunction(NULL, "PauseMenu_StopSound");
    PauseMenu_State_HandleFadeout     = Mod.GetPublicFunction(NULL, "PauseMenu_State_HandleFadeout");
    PauseMenu_ExitButtonCB            = Mod.GetPublicFunction(NULL, "PauseMenu_ExitButtonCB");
    PauseMenu_ExitFadeCB              = Mod.GetPublicFunction(NULL, "PauseMenu_ExitFadeCB");
    PauseMenu_RestartButtonCB         = Mod.GetPublicFunction(NULL, "PauseMenu_RestartButtonCB");
    PauseMenu_RestartFadeCB           = Mod.GetPublicFunction(NULL, "PauseMenu_RestartFadeCB");
    PauseMenu_ActionCB_Button         = Mod.GetPublicFunction(NULL, "PauseMenu_ActionCB_Button");
    PauseMenu_ResumeButtonCB          = Mod.GetPublicFunction(NULL, "PauseMenu_ResumeButtonCB");
    PauseMenu_AddButton               = Mod.GetPublicFunction(NULL, "PauseMenu_AddButton");
    PauseMenu_Draw_ForcePause         = Mod.GetPublicFunction(NULL, "PauseMenu_Draw_ForcePause");
    PauseMenu_State_StartPause        = Mod.GetPublicFunction(NULL, "PauseMenu_State_StartPause");
    PauseMenu_IsDisconnected          = Mod.GetPublicFunction(NULL, "PauseMenu_IsDisconnected");
    // Player
    Player_GiveScore                  = Mod.GetPublicFunction(NULL, "Player_GiveScore");
    Player_LoadSprites                = Mod.GetPublicFunction(NULL, "Player_LoadSprites");
    Player_LoadSpritesVS              = Mod.GetPublicFunction(NULL, "Player_LoadSpritesVS");
    Player_State_OuttaHere            = Mod.GetPublicFunction(NULL, "Player_State_OuttaHere");
    Player_State_Death                = Mod.GetPublicFunction(NULL, "Player_State_Death");
    Player_State_Drown                = Mod.GetPublicFunction(NULL, "Player_State_Drown");
    // SaveGame
    SaveGame_GetSaveRAM               = Mod.GetPublicFunction(NULL, "SaveGame_GetSaveRAM");
    // UIButton & UIControl
    UIButton_State_Selected           = Mod.GetPublicFunction(NULL, "UIButton_State_Selected");
    UIButton_GetChoicePtr             = Mod.GetPublicFunction(NULL, "UIButton_GetChoicePtr");
    UIButton_GetActionCB              = Mod.GetPublicFunction(NULL, "UIButton_GetActionCB");
    UIButton_ButtonLeaveCB            = Mod.GetPublicFunction(NULL, "UIButton_ButtonLeaveCB");
    UIButton_State_HandleButtonLeave  = Mod.GetPublicFunction(NULL, "UIButton_State_HandleButtonLeave");
    UIButton_State_HandleButtonEnter  = Mod.GetPublicFunction(NULL, "UIButton_State_HandleButtonEnter");
    UIControl_ProcessInputs           = Mod.GetPublicFunction(NULL, "UIControl_ProcessInputs");
    // TitleLogo & TitleSetup
    TitleLogo_SetupPressStart         = Mod.GetPublicFunction(NULL, "TitleLogo_SetupPressStart");
    TitleSetup_State_WaitForSonic     = Mod.GetPublicFunction(NULL, "TitleSetup_State_WaitForSonic");
    TitleSetup_State_SetupLogo        = Mod.GetPublicFunction(NULL, "TitleSetup_State_SetupLogo");
    TitleSetup_State_WaitForEnter     = Mod.GetPublicFunction(NULL, "TitleSetup_State_WaitForEnter");
    TitleSetup_State_FadeToMenu       = Mod.GetPublicFunction(NULL, "TitleSetup_State_FadeToMenu");
    TitleSetup_State_FadeBlack        = Mod.GetPublicFunction(NULL, "TitleSetup_State_FadeBlack");
    // Zone
    Zone_StartFadeOut                 = Mod.GetPublicFunction(NULL, "Zone_StartFadeOut");
    Zone_GetZoneID                    = Mod.GetPublicFunction(NULL, "Zone_GetZoneID");

    // Register state hooks
    // ActClear
    Mod.RegisterStateHook(ActClear_State_SaveGameProgress, ActClear_ExitActClear, true);
    // GameOver
    Mod.RegisterStateHook(GameOver_State_ExitLetters, GameOver_State_Exit, true);
    // TitleSetup
    Mod.RegisterStateHook(TitleSetup_State_WaitForSonic, TitleSetup_State_WaitForSonic_Hook, false);
    Mod.RegisterStateHook(TitleSetup_State_SetupLogo, TitleSetup_State_SetupLogo_Hook, false);
    Mod.RegisterStateHook(TitleSetup_State_WaitForEnter, TitleSetup_State_WaitForEnter_Hook, false);
    // PauseMenu
    Mod.RegisterStateHook(PauseMenu_DrawPauseMenu, PauseMenu_DrawPause, true);
    Mod.RegisterStateHook(PauseMenu_Draw_RegularPause, PauseMenu_Draw_Regular, true);
    Mod.RegisterStateHook(PauseMenu_ExitButtonCB, PauseMenu_ExitButton, false);
    Mod.RegisterStateHook(PauseMenu_ExitFadeCB, PauseMenu_ExitFade, false);
    Mod.RegisterStateHook(PauseMenu_RestartButtonCB, PauseMenu_RestartButton, false);
    Mod.RegisterStateHook(PauseMenu_State_SetupButtons, PauseMenu_State_SetupButton, false);
    Mod.RegisterStateHook(PauseMenu_AddButton, PauseMenu_AddUIButton, false);
    // UIButton
    Mod.RegisterStateHook(UIButton_State_Selected, UIButton_State_Select, true);
    Mod.RegisterStateHook(UIButton_State_HandleButtonLeave, UIButton_State_HideHighlight, false);
    Mod.RegisterStateHook(UIButton_State_HandleButtonEnter, UIButton_State_ShowHighlight, false);
    // Player
    Mod.RegisterStateHook(Mod.GetPublicFunction(NULL, "Player_State_Ground"), Player_SetOuttaHere, false);
}

#if RETRO_USE_MOD_LOADER
#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))

void InitModAPI(void);

bool32 LinkModLogic(EngineInfo *info, const char *id)
{
#if MANIA_USE_PLUS
    LinkGameLogicDLL(info);
#else
    LinkGameLogicDLL(*info);
#endif

    globals = Mod.GetGlobals();

    modID = id;

    InitModAPI();

    return true;
}
#endif