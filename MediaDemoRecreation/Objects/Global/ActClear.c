#include "GameAPI/Game.h"
#include "../Menu/MenuParam.h"
#include "ActClear.h"
#include "Animals.h"
#include "HUD.h"
#include "Music.h"
#include "Zone.h"
#include "SaveGame.h"
#include "../Helpers/TimeAttackData.h"

ObjectActClear *ActClear;
ObjectZone *Zone;
int32 (*Zone_GetZoneID)(void);
void (*Zone_StartFadeOut)(int32 fadeSpeed, int32 fadeColor);

void ActClear_Draw(void)
{
    RSDK_THIS(ActClear);

    Vector2 drawPos;
    Vector2 verts[4];
#if MANIA_USE_PLUS
    int32 milliseconds = 0;
    int32 seconds      = 0;
    int32 minutes      = 0;
#endif
    int32 offset = 0;

    drawPos.x  = self->gotThroughPos.x;
    drawPos.y  = self->gotThroughPos.y;
    verts[0].y = drawPos.y - TO_FIXED(20);
    verts[1].y = drawPos.y - TO_FIXED(20);
    verts[2].y = drawPos.y - TO_FIXED(4);
    verts[3].y = drawPos.y - TO_FIXED(4);
    if ((GET_CHARACTER_ID(1)) == ID_KNUCKLES) {
        int32 center = TO_FIXED(ScreenInfo->center.x + 16);

        drawPos.x  = 2 * self->gotThroughPos.x + center;
        verts[0].x = drawPos.x - TO_FIXED(145);
        verts[1].x = drawPos.x + TO_FIXED(52);
        verts[2].x = drawPos.x + TO_FIXED(68);
        verts[3].x = drawPos.x - TO_FIXED(129);
        RSDK.DrawFace(verts, 4, 0x00, 0x00, 0x00, 0xFF, INK_NONE);

        drawPos.x  = 2 * self->playerNamePos.x + center;
        drawPos.y  = self->playerNamePos.y;
        verts[0].x = drawPos.x - TO_FIXED(124);
        verts[0].y = drawPos.y + TO_FIXED(28);
        verts[1].x = drawPos.x + TO_FIXED(80);
        verts[2].x = drawPos.x + TO_FIXED(96);
        verts[3].x = drawPos.x - TO_FIXED(108);
        verts[1].y = drawPos.y + TO_FIXED(28);
        verts[2].y = drawPos.y + TO_FIXED(44);
        verts[3].y = drawPos.y + TO_FIXED(44);
        RSDK.DrawFace(verts, 4, 0x00, 0x00, 0x00, 0xFF, INK_NONE);

        drawPos.x = self->playerNamePos.x + center;
        drawPos.y = self->playerNamePos.y;
        RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

        self->gotThroughAnimator.frameID = 2;
        RSDK.DrawSprite(&self->gotThroughAnimator, &drawPos, true);

        drawPos.x                        = self->gotThroughPos.x + center;
        drawPos.y                        = self->gotThroughPos.y;
        self->gotThroughAnimator.frameID = 3;
        RSDK.DrawSprite(&self->gotThroughAnimator, &drawPos, true);
        RSDK.DrawSprite(&self->actNumAnimator, &drawPos, true);

        offset = center - TO_FIXED(10);
    }
    else {
        int32 center = TO_FIXED(ScreenInfo->center.x);

        drawPos.x  = 2 * self->gotThroughPos.x + center;
        verts[0].x = drawPos.x - TO_FIXED(109);
        verts[1].x = drawPos.x + TO_FIXED(52);
        verts[2].x = drawPos.x + TO_FIXED(68);
        verts[3].x = drawPos.x - TO_FIXED(93);
        RSDK.DrawFace(verts, 4, 0x00, 0x00, 0x00, 0xFF, INK_NONE);

        drawPos.x  = 2 * self->playerNamePos.x + center;
        drawPos.y  = self->playerNamePos.y;
        verts[0].x = drawPos.x - TO_FIXED(88);
        verts[0].y = drawPos.y + TO_FIXED(28);
        verts[1].x = drawPos.x + TO_FIXED(80);
        verts[2].x = drawPos.x + TO_FIXED(96);
        verts[3].x = drawPos.x - TO_FIXED(72);
        verts[1].y = drawPos.y + TO_FIXED(28);
        verts[2].y = drawPos.y + TO_FIXED(44);
        verts[3].y = drawPos.y + TO_FIXED(44);
        RSDK.DrawFace(verts, 4, 0x00, 0x00, 0x00, 0xFF, INK_NONE);

        drawPos.x = self->playerNamePos.x + center;
        drawPos.y = self->playerNamePos.y;
        RSDK.DrawSprite(&self->playerNameAnimator, &drawPos, true);

#if MANIA_USE_PLUS
        if ((GET_CHARACTER_ID(1)) == ID_MIGHTY)
            self->gotThroughAnimator.frameID = 2;
        else
#endif
            self->gotThroughAnimator.frameID = 0;
        RSDK.DrawSprite(&self->gotThroughAnimator, &drawPos, true);

        drawPos.x                        = self->gotThroughPos.x + center;
        drawPos.y                        = self->gotThroughPos.y;
        self->gotThroughAnimator.frameID = 1;
        RSDK.DrawSprite(&self->gotThroughAnimator, &drawPos, true);
        RSDK.DrawSprite(&self->actNumAnimator, &drawPos, true);

        offset = center + TO_FIXED(6);
    }

    // Draw Time Bonus
    drawPos.x                         = offset + self->timeBonusPos.x - TO_FIXED(92);
    drawPos.y                         = self->timeBonusPos.y;

    self->hudElementsAnimator.frameID = 1; // "Time"
    RSDK.DrawSprite(&self->hudElementsAnimator, &drawPos, true);

    drawPos.x += TO_FIXED(50);
    self->hudElementsAnimator.frameID = 8; // "Bonus"
    RSDK.DrawSprite(&self->hudElementsAnimator, &drawPos, true);

    // Draw Time Bonus BG thingy
    self->hudElementsAnimator.frameID = 10;
    drawPos.x += TO_FIXED(52);
    RSDK.DrawSprite(&self->hudElementsAnimator, &drawPos, true);

    // Draw Time Bonus numbers
    drawPos.x += TO_FIXED(67);
    drawPos.y += TO_FIXED(14);
    ActClear_DrawNumbers(&drawPos, self->timeBonus, 0); // Draw Time Bonus

    // Draw Ring Bonus
    drawPos.x = offset + self->ringBonusPos.x - TO_FIXED(92);
    drawPos.y = self->ringBonusPos.y;

    self->hudElementsAnimator.frameID = 5; // "Ring"
    RSDK.DrawSprite(&self->hudElementsAnimator, &drawPos, true);

    drawPos.x += TO_FIXED(50);
    self->hudElementsAnimator.frameID = 8; // "Bonus"
    RSDK.DrawSprite(&self->hudElementsAnimator, &drawPos, true);

    // Draw Ring Bonus BG thingy
    self->hudElementsAnimator.frameID = 10;
    drawPos.x += TO_FIXED(52);
    RSDK.DrawSprite(&self->hudElementsAnimator, &drawPos, true);

    // Draw Ring Bonus numbers
    drawPos.x += TO_FIXED(67);
    drawPos.y += TO_FIXED(14);
    ActClear_DrawNumbers(&drawPos, self->ringBonus, 0);

    drawPos.x = self->totalScorePos.x;
    drawPos.y = self->totalScorePos.y;

    // Draw Total Score
    drawPos.x                         = offset + self->totalScorePos.x - TO_FIXED(68);
    self->hudElementsAnimator.frameID = 9; // "Total"
    RSDK.DrawSprite(&self->hudElementsAnimator, &drawPos, true);

    // Draw Total Score BG thingy
    self->hudElementsAnimator.frameID = 10;
    drawPos.x += TO_FIXED(52);
    RSDK.DrawSprite(&self->hudElementsAnimator, &drawPos, true);

    // Draw Total Score numbers
    drawPos.x += TO_FIXED(67);
    drawPos.y += TO_FIXED(14);
    ActClear_DrawNumbers(&drawPos, self->totalScore, 0);
}

void ActClear_Create(void *data)
{
    RSDK_THIS(ActClear);
    if (!SceneInfo->inEditor) {
#if MANIA_USE_PLUS
        ActClear->actClearActive = true;
#endif
        self->active           = ACTIVE_NORMAL;
        self->visible          = true;
        self->drawGroup        = Zone->hudDrawGroup;
        self->state            = ActClear_State_EnterText;
        self->stageFinishTimer = 0;
        self->newRecordTimer   = 0;

        EntityPlayer *player1 = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);
        self->targetPlayer    = player1;

        if (Zone_GetZoneID() > ZONE_INVALID) {
            uint16 time = TimeAttackData_GetPackedTime_Hook(SceneInfo->minutes, SceneInfo->seconds, SceneInfo->milliseconds);

#if MANIA_USE_PLUS
            StatInfo stat;
            switch (GET_CHARACTER_ID(1)) {
                case ID_SONIC: TimeAttackData_TrackActClear_Hook(&stat, Zone_GetZoneID(), Zone->actID, 1, time, player1->rings, player1->score); break;
                case ID_TAILS: TimeAttackData_TrackActClear_Hook(&stat, Zone_GetZoneID(), Zone->actID, 2, time, player1->rings, player1->score); break;
                case ID_KNUCKLES: TimeAttackData_TrackActClear_Hook(&stat, Zone_GetZoneID(), Zone->actID, 3, time, player1->rings, player1->score); break;
                case ID_MIGHTY: TimeAttackData_TrackActClear_Hook(&stat, Zone_GetZoneID(), Zone->actID, 4, time, player1->rings, player1->score); break;
                default:
                case ID_RAY:
                    if ((GET_CHARACTER_ID(1)) == ID_RAY)
                        TimeAttackData_TrackActClear_Hook(&stat, Zone_GetZoneID(), Zone->actID, 5, time, player1->rings, player1->score);
                    else
                        TimeAttackData_TrackActClear_Hook(&stat, Zone_GetZoneID(), Zone->actID, 1, time, player1->rings, player1->score);
                    break;
            }
            API.TryTrackStat(&stat);
#else
            switch (GET_CHARACTER_ID(1)) {
                case ID_SONIC: APICallback_TrackActClear(Zone_GetZoneID(), Zone->actID, 1, time, player1->rings, player1->score); break;
                case ID_TAILS: APICallback_TrackActClear(Zone_GetZoneID(), Zone->actID, 2, time, player1->rings, player1->score); break;
                case ID_KNUCKLES: APICallback_TrackActClear(Zone_GetZoneID(), Zone->actID, 3, time, player1->rings, player1->score); break;
                default: break;
            }
#endif
        }

#if MANIA_USE_PLUS
        if (!ActClear->disableTimeBonus) {
#endif
            switch (SceneInfo->minutes) {
                case 0:
                    if (SceneInfo->seconds >= 30)
                        self->timeBonus = SceneInfo->seconds < 45 ? 10000 : 5000;
                    else
                        self->timeBonus = 50000;
                    break;

                case 1: self->timeBonus = SceneInfo->seconds < 30 ? 4000 : 3000; break;
                case 2: self->timeBonus = 2000; break;
                case 3: self->timeBonus = 1000; break;
                case 4: self->timeBonus = 500; break;
                case 5: self->timeBonus = 100; break;

                case 9:
                    if (!SceneInfo->debugMode && globals->gameMode < MODE_TIMEATTACK && SceneInfo->seconds == 59) {
#if MANIA_USE_PLUS
                        if (globals->gameMode != MODE_ENCORE && !(globals->medalMods & MEDAL_NOTIMEOVER))
#endif
                            self->timeBonus = 100000;
                    }
                    break;

                default: break;
            }
#if MANIA_USE_PLUS
        }
#endif

        self->ringBonus        = 100 * player1->rings;
        globals->initCoolBonus = false;
        self->showCoolBonus   = false;
        self->playerNamePos.x = TO_FIXED(224);
        self->playerNamePos.y = TO_FIXED(88);
        self->gotThroughPos.x = -TO_FIXED(224);
        self->gotThroughPos.y = TO_FIXED(112);
        self->timeBonusPos.x  = TO_FIXED(488);
        self->timeBonusPos.y = TO_FIXED(128);
        self->ringBonusPos.x = TO_FIXED(776);
        self->ringBonusPos.y = TO_FIXED(144);
        self->totalScorePos.x = -TO_FIXED(1064);
        self->totalScorePos.y = TO_FIXED(192);

        RSDK.SetSpriteAnimation(ActClear->aniFrames, 0, &self->hudElementsAnimator, true, 0);
        RSDK.SetSpriteAnimation(ActClear->aniFrames, 1, &self->numbersAnimator, true, 0);

        switch (GET_CHARACTER_ID(1)) {
            default:
            case ID_SONIC: RSDK.SetSpriteAnimation(ActClear->aniFrames, 3, &self->playerNameAnimator, true, 0); break;
            case ID_TAILS: RSDK.SetSpriteAnimation(ActClear->aniFrames, 3, &self->playerNameAnimator, true, 1); break;
            case ID_KNUCKLES: RSDK.SetSpriteAnimation(ActClear->aniFrames, 3, &self->playerNameAnimator, true, 2); break;
        }
        RSDK.SetSpriteAnimation(ActClear->aniFrames, 4, &self->gotThroughAnimator, true, 0);

        // Used in cases like OOZ1 outro where the act clear actually happens in OOZ2
        if (ActClear->displayedActID <= 0)
            RSDK.SetSpriteAnimation(ActClear->aniFrames, 5, &self->actNumAnimator, true, Zone->actID);
        else
            RSDK.SetSpriteAnimation(ActClear->aniFrames, 5, &self->actNumAnimator, true, ActClear->displayedActID - 1);
    }
}

void ActClear_ExitActClear(void)
{
    RSDK_THIS(ActClear);

    if (++self->timer == 120) {
        RSDK.SetScene("Presentation", "Thanks For Playing");
        self->state = StateMachine_None;
        Zone_StartFadeOut(10, 0x000000);
    }
}