#ifndef OBJ_DEMOMENU_H
#define OBJ_DEMOMENU_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectDemoMenu;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 timer;
    int32 selectedZone;
    Vector2 zoneSelPos;
    Vector2 ghzPos;
    Vector2 spzPos;
    float vDelta;
    Animator zoneSelAnimator;
    Animator blackBarAnimator;
    Animator flashBarAnimator;
    Animator ghzAnimator;
    Animator spzAnimator;
    SpriteFrame *ghzFrame;
    SpriteFrame *spzFrame;
} EntityDemoMenu;

// Object Entity
extern ObjectDemoMenu *DemoMenu;

#endif //! OBJ_DEMOMENU_H
