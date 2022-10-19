#include "GameAPI/Game.h"
#include "UIPicture.h"

ObjectUIPicture *UIPicture;

void UIPicture_Create(void *data)
{
    RSDK_THIS(UIPicture);
    
    RSDK.SetSpriteAnimation(UIPicture->aniFrames, self->listID, &self->animator, true, self->frameID);
    if (!SceneInfo->inEditor) {
        if (RSDK.CheckSceneFolder("Menu")) {
            self->active    = ACTIVE_BOUNDS;
            self->visible   = true;
            self->drawGroup = 2;
        }
        else if (RSDK.CheckSceneFolder("Thanks")) {
            self->active    = ACTIVE_NORMAL;
            self->visible   = true;
            self->drawGroup = 8;
        }
        else {
            if (RSDK.CheckSceneFolder("Logos") || RSDK.CheckSceneFolder("LSelect") || RSDK.CheckSceneFolder("Summary"))
            self->active = ACTIVE_NORMAL;
            self->visible   = true;
            self->drawGroup = 2;
        }
    }
}