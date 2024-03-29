#ifndef OBJ_STARPOST_H
#define OBJ_STARPOST_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitbox;
    bool32 hasAchievement;
    Vector2 playerPositions[PLAYER_COUNT];
    uint8 playerDirections[PLAYER_COUNT];
    uint16 postIDs[PLAYER_COUNT];
    uint8 storedMinutes;
    uint8 storedSeconds;
    uint8 storedMS;
    uint8 interactablePlayers;
    uint16 aniFrames;
    uint16 sfxStarPost;
    uint16 sfxWarp;
} ObjectStarPost;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    int32 id;
    bool32 vsRemove;
    int32 ballSpeed;
    int32 timer;
    int32 starTimer;
    int32 bonusStageID;
    int32 starAngleX;
    int32 starAngleY;
    int32 starRadius;
    Vector2 ballPos;
    Animator poleAnimator;
    Animator ballAnimator;
    Animator starAnimator;
    Hitbox hitboxStars;
    uint8 interactedPlayers;
} EntityStarPost;

// Object Struct
extern ObjectStarPost *StarPost;

void StarPost_Update(void);

#endif //! OBJ_STARPOST_H
