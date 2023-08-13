#ifndef OBJ_SAVEGAME_H
#define OBJ_SAVEGAME_H

#include "GameAPI/Game.h"

typedef enum {
    SAVEGAME_BLANK,
    SAVEGAME_INPROGRESS,
    SAVEGAME_COMPLETE,
} SaveGameStates;

typedef enum {
    SAVERECALL_NORMAL,
    SAVERECALL_DISABLED,
    SAVERECALL_BROKENITEMBOX,
} SaveRecallStates;

typedef struct {
    uint8 padding[0x58];

    int32 saveState;
    int32 characterID;
    int32 zoneID;
    int32 lives;
    int32 score;
    int32 score1UP;
    int32 collectedEmeralds;
    int32 continues;
    int32 storedStageID;
    int32 nextSpecialStage;
    int32 collectedSpecialRings;
    int32 medalMods;
#if MANIA_USE_PLUS
    //(AIZ if encore) + GHZ-TMZ + (ERZ if not encore)
    // Bonus stage is [28]
    // Special stage is [29]
    // the rest are unused
    int32 zoneTimes[32];
    int32 characterFlags;
    int32 stock;
    int32 playerID; // encore playerID
#endif
} SaveRAM;

// Object Class
typedef struct {
#if !MANIA_USE_PLUS
    RSDK_OBJECT
    Entity *loadEntityPtr;
    void (*loadCallback)(bool32 success);
    Entity *saveEntityPtr;
    void (*saveCallback)(void);
#else
    Entity *loadEntityPtr;
    void (*loadCallback)(bool32 success);
    Entity *saveEntityPtr;
    void (*saveCallback)(bool32 success);
#endif
    SaveRAM *saveRAM;
    int32 unused1;
} ObjectSaveGame;

// Entity Class
typedef struct {
    RSDK_ENTITY
    uint8 padding[sizeof(SaveRAM) - sizeof(Entity)];
} EntitySaveGame;

extern ObjectSaveGame *SaveGame;

extern SaveRAM* (*SaveGame_GetSaveRAM)(void);

#endif //! OBJ_SAVEGAME_H
