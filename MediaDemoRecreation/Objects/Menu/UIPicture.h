#ifndef OBJ_UIPICTURE_H
#define OBJ_UIPICTURE_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT 
    uint16 aniFrames;
} ObjectUIPicture;

// Entity Class
typedef struct {
    RSDK_ENTITY
    int32 listID;
    int32 frameID;
    int32 tag;
    uint8 zonePalette;
    int32 zoneID;
    Animator animator;
} EntityUIPicture;

// Object Struct
extern ObjectUIPicture *UIPicture;

// Standard Entity Events
void UIPicture_Create(void *data);

#endif //! OBJ_UIPICTURE_H
