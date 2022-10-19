#ifndef OBJ_TIMEATTACKDATA_H
#define OBJ_TIMEATTACKDATA_H

#include "GameAPI/Game.h"

typedef enum {
    CHAR_SONIC_AND_TAILS,
    CHAR_SONIC,
    CHAR_TAILS,
    CHAR_KNUX,
#if MANIA_USE_PLUS
    CHAR_MIGHTY,
    CHAR_RAY,
#endif
} CharacterIDs;

typedef enum {
    ACT_1,
    ACT_2,
    ACT_3,
    ACT_NONE,
} ActIDs;

// Using a seperate TimeAttackRAM struct
// Normally (and officially) the ObjectGameProgress struct was used here
// but due to v5U updating the entity (and thus the TimeAttackRAM "spec")
// ObjectGameProgress is no longer easily compatible across versions
// so I gave it dummy data and will be using this struct to interact with TimeAttackRAM
// this one was also broken with plus since medals[] were aligned by 1 byte
// so when "filter" was added, all medals were offset by 1 without this fix
typedef struct {
    uint8 padding[0x56]; // aka sizeof(Entity) for pre-plus
    uint16 records[3][12][2][3];
} TimeAttackRAM;

// Object Class
typedef struct {
#if !MANIA_USE_PLUS
    RSDK_OBJECT
#endif
    bool32 loaded;
    uint8 zoneID;
    uint8 act;
    uint8 characterID;
    bool32 encore;
    int32 uuid;
    int32 rowID;
    int32 personalRank;
    int32 leaderboardRank;
    bool32 isMigratingData;
    Entity *loadEntityPtr;
    void (*loadCallback)(bool32 success);
    Entity *saveEntityPtr;
    void (*saveCallback)(bool32 success);
} ObjectTimeAttackData;

#if !MANIA_USE_PLUS
// Entity Class
typedef struct {
    RSDK_ENTITY
    // padding to match whatever it would be normally
    // not required, but its for safety :)
    uint8 padding[sizeof(TimeAttackRAM) - sizeof(Entity)];
} EntityTimeAttackData;
#endif

// Object Entity
extern ObjectTimeAttackData *TimeAttackData;

// Extra Entity FUnctions
#if MANIA_USE_PLUS
void (*TimeAttackData_TrackActClear)(StatInfo *stat, uint8 zone, uint8 act, uint8 charID, int32 time, int32 rings, int32 score);
void TimeAttackData_TrackActClear_Hook(StatInfo *stat, uint8 zone, uint8 act, uint8 charID, int32 time, int32 rings, int32 score);
#endif

uint32 (*TimeAttackData_GetPackedTime)(int32 minutes, int32 seconds, int32 milliseconds);
uint32 TimeAttackData_GetPackedTime_Hook(int32 minutes, int32 seconds, int32 milliseconds);
void (*TimeAttackData_GetUnpackedTime)(int32 time, int32 *minutes, int32 *seconds, int32 *milliseconds);
void TimeAttackData_GetUnpackedTime_Hook(int32 time, int32 *minutes, int32 *seconds, int32 *milliseconds);

#if MANIA_USE_PLUS
int32 (*TimeAttackData_GetScore)(uint8 zoneID, uint8 act, uint8 characterID, bool32 encore, int32 rank);
int32 TimeAttackData_GetScore_Hook(uint8 zoneID, uint8 act, uint8 characterID, bool32 encore, int32 rank);
void (*TimeAttackData_ConfigureTableView)(uint8 zoneID, uint8 act, uint8 characterID, bool32 encore);
#endif

#endif //! OBJ_TIMEATTACKDATA_H
