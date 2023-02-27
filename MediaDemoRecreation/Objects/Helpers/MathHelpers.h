#ifndef OBJ_MATHHELPERS_H
#define OBJ_MATHHELPERS_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
} ObjectMathHelpers;

// Entity Class
typedef struct {
    RSDK_ENTITY
} EntityMathHelpers;

// Object Entity
extern ObjectMathHelpers *MathHelpers;

// Extra Entity Functions

// Lerp
void (*MathHelpers_Lerp2Sin1024)(Vector2 *pos, int32 percent, int32 startX, int32 startY, int32 endX, int32 endY);

#endif //! OBJ_MATHHELPERS_H
