#ifndef OBJ_TITLESONIC_H
#define OBJ_TITLESONIC_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectTitleSonic;

// Entity Class
typedef struct {
    RSDK_ENTITY
    Animator animatorSonic;
    Animator animatorFinger;
} EntityTitleSonic;

// Object Struct
extern ObjectTitleSonic *TitleSonic;

#endif //! OBJ_TITLESONIC_H
