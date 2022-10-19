#include "GameAPI/Game.h"
#include "GameOver.h"
#include "SaveGame.h"
#include "StarPost.h"

ObjectGameOver *GameOver;

void GameOver_State_Exit(void)
{
    RSDK_THIS(GameOver);

    if (self->timer < 120) {
        for (int32 i = 0; i < GAMEOVER_LETTER_COUNT; ++i) {
            self->letterPositions[i].x += self->letterPosMove[i].x;
            self->letterPositions[i].y += self->letterPosMove[i].y;
            self->letterRotations[i] += self->letterRotateSpeed[i];
        }
        self->verts[0].x -= TO_FIXED(16);
        self->verts[0].y -= TO_FIXED(8);
        self->verts[1].x += TO_FIXED(16);
        self->verts[1].y -= TO_FIXED(8);
        self->verts[2].x += TO_FIXED(16);
        self->verts[2].y += TO_FIXED(8);
        self->verts[3].x -= TO_FIXED(16);
        self->verts[3].y += TO_FIXED(8);
        self->scale.x += 0x20;
        self->scale.y += 0x20;
        ++self->timer;
    }

    if (self->timer == 90) {
        self->timer = 0;

        if (self->animator.animationID != 6) {
            StarPost->storedMS      = 0;
            StarPost->storedSeconds = 0;
            StarPost->storedMinutes = 0;
            RSDK.LoadScene();
        }
        else {
            SaveRAM *saveRAM = SaveGame_GetSaveRAM();
            if (globals->gameMode >= MODE_TIMEATTACK) {
                RSDK.SetScene("Presentation", "Thanks For Playing");
                RSDK.LoadScene();
            }
            else if (globals->continues > 0) {
                saveRAM->storedStageID = SceneInfo->listPos;
                saveRAM->lives         = 3;
                saveRAM->score         = 0;
                saveRAM->score1UP      = 0;
                RSDK.SetScene("Presentation", "Continue");
                RSDK.LoadScene();
            }
            else {
                saveRAM->lives    = 3;
                saveRAM->score    = 0;
                saveRAM->score1UP = 0;
                RSDK.SetScene("Presentation", "Thanks For Playing");
                RSDK.LoadScene();
            }
        }
    }
}
