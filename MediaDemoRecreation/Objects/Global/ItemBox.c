#include "GameAPI/Game.h"
#include "ItemBox.h"
#include "DebugMode.h"

ObjectItemBox *ItemBox;

void ItemBox_StageLoad(void)
{
    ItemBox->aniFrames = RSDK.LoadSpriteAnimation("Global/ItemBox.bin", SCOPE_STAGE);

    ItemBox->hitboxItemBox.left = -15;
    ItemBox->hitboxItemBox.top = -16;
    ItemBox->hitboxItemBox.right = 15;
    ItemBox->hitboxItemBox.bottom = 16;

    ItemBox->hitboxHidden.left = -15;
    ItemBox->hitboxHidden.top = -24;
    ItemBox->hitboxHidden.right = 15;
    ItemBox->hitboxHidden.bottom = 16;

    DEBUGMODE_ADD_OBJ(ItemBox);

    ItemBox->sfxDestroy = RSDK.GetSfx("Global/Destroy.wav");
    ItemBox->sfxTeleport = RSDK.GetSfx("Global/Teleport.wav");
    ItemBox->sfxHyperRing = RSDK.GetSfx("");
#if MANIA_USE_PLUS
    ItemBox->sfxPowerDown = RSDK.GetSfx("Stage/PowerDown.wav");
    ItemBox->sfxRecovery = RSDK.GetSfx("Global/Recovery.wav");
#endif
}