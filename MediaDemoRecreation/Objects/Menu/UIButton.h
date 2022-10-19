#ifndef OBJ_UIBUTTON_H
#define OBJ_UIBUTTON_H

#include "GameAPI/Game.h"

typedef enum {
    UIBUTTON_ALIGN_LEFT,
    UIBUTTON_ALIGN_CENTER,
    UIBUTTON_ALIGN_RIGHT,
} UIButtonAlignments;

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectUIButton;

// Entity Class
typedef struct {
    MANIA_UI_ITEM_BASE
    Vector2 size;
    int32 listID;
    int32 frameID;
    int32 align;
    int32 choiceCount;
    uint8 choiceDir;
    bool32 invisible;
    bool32 assignsP1;
    bool32 freeBindP2;
    bool32 transition;
    bool32 stopMusic;
    bool32 isDisabled;
    int32 bgEdgeSize;
    int32 textBounceOffset;
    int32 buttonBounceOffset;
    int32 textBounceVelocity;
    int32 buttonBounceVelocity;
    bool32 textVisible;
    bool32 clearParentState;
    Vector2 firstChoicePos;
    int32 selection;
    void (*choiceChangeCB)(void);
    Animator animator;
    uint16 textFrames;
    int32 startListID;
    int32 startFrameID;
    Animator highlightAnimator;
    bool32 highlightVisible;
} EntityUIButton;

// Object Struct
extern ObjectUIButton *UIButton;

// Standard Entity Events

void UIButton_Update(void);
void UIButton_Draw(void);

// Extra Entity Functions

void UIButton_State_HideHighlight(void);
void (*UIButton_State_HandleButtonLeave)(void);
void UIButton_State_ShowHighlight(void);
void (*UIButton_State_HandleButtonEnter)(void);
void UIButton_State_Select(void);
void (*UIButton_State_Selected)(void);

void (*UIButton_ButtonLeaveCB)(void);
void* (*UIButton_GetActionCB)(void);
EntityUIButton* (*UIButton_GetChoicePtr)(EntityUIButton* button, int32 selection);

#endif //! OBJ_UIBUTTON_H
