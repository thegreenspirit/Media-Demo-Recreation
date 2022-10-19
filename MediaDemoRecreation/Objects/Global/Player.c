#include "GameAPI/Game.h"
#include "Player.h"

ObjectPlayer *Player;

void Player_StageLoad(void)
{
    if (!globals->playerID)
        globals->playerID = RSDK.CheckSceneFolder("MSZCutscene") ? ID_KNUCKLES : ID_SONIC;

    SceneInfo->debugMode = globals->medalMods & MEDAL_DEBUGMODE;
#if MANIA_USE_PLUS
    RSDK.AddViewableVariable("Debug Mode", &SceneInfo->debugMode, VIEWVAR_BOOL, false, true);
#endif

    if (globals->medalMods & MEDAL_ANDKNUCKLES) {
        globals->playerID &= 0xFF;
        globals->playerID |= ID_KNUCKLES_ASSIST;
    }

    Player->playerCount = 0;
    Player->active      = ACTIVE_ALWAYS;

    // Sprite loading & characterID management
    if (globals->gameMode == MODE_COMPETITION)
        Player_LoadSpritesVS();
    else
        Player_LoadSprites();

    Player->playerCount = RSDK.GetEntityCount(Player->classID, false);

    // Handle Sidekick stuff setup
    Player->nextLeaderPosID = 1;
    Player->lastLeaderPosID = 0;
#if GAME_VERSION != VER_100
    Player->disableP2KeyCheck = false;
#endif

    Player->upState        = false;
    Player->downState      = false;
    Player->leftState      = false;
    Player->rightState     = false;
    Player->jumpPressState = false;
    Player->jumpHoldState  = false;

    // Sfx Loading
    Player->sfxJump        = RSDK.GetSfx("Global/Jump.wav");
    Player->sfxLoseRings   = RSDK.GetSfx("Global/LoseRings.wav");
    Player->sfxHurt        = RSDK.GetSfx("Global/Hurt.wav");
    Player->sfxRoll        = RSDK.GetSfx("Global/Roll.wav");
    Player->sfxCharge      = RSDK.GetSfx("Global/Charge.wav");
    Player->sfxRelease     = RSDK.GetSfx("Global/Release.wav");
    Player->sfxPeelCharge  = RSDK.GetSfx("Global/PeelCharge.wav");
    Player->sfxPeelRelease = RSDK.GetSfx("Global/PeelRelease.wav");
    Player->sfxDropdash    = RSDK.GetSfx("Global/DropDash.wav");
    Player->sfxSkidding    = RSDK.GetSfx("Global/Skidding.wav");
    Player->sfxGrab        = RSDK.GetSfx("Global/Grab.wav");
    Player->sfxFlying      = RSDK.GetSfx("Global/Flying.wav");
    Player->sfxTired       = RSDK.GetSfx("Global/Tired.wav");
    Player->sfxLand        = RSDK.GetSfx("Global/Land.wav");
    Player->sfxSlide       = RSDK.GetSfx("Global/Slide.wav");
    Player->sfxOuttahere   = RSDK.GetSfx("Global/OuttaHere.wav");
    Player->sfxTransform2  = RSDK.GetSfx("Stage/Transform2.wav");

    // Handle gotHit values (used for TMZ1 achievement)
    for (int32 p = 0; p < PLAYER_COUNT; ++p) Player->gotHit[p] = false;
}

void Player_SetOuttaHere(void)
{
    RSDK_THIS(Player);

    // Wait for ~3 minutes to do outta here
    if (self->outtaHereTimer >= 10620 && self->characterID == ID_SONIC) {
        RSDK.SetSpriteAnimation(self->aniFrames, ANI_OUTTA_HERE, &self->animator, false, 0);
        self->state           = Player_State_OuttaHere;
        self->tileCollisions  = TILECOLLISION_NONE;
        self->interaction     = false;
        self->nextAirState    = StateMachine_None;
        self->nextGroundState = StateMachine_None;
        self->velocity.x      = 0;
        self->velocity.y      = 0;
        RSDK.PlaySfx(Player->sfxOuttahere, false, 255);
    }
}