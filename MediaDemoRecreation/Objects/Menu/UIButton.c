#include "GameAPI/Game.h"
#include "UIButton.h"
#include "UIControl.h"

ObjectUIButton *UIButton;

void UIButton_Update(void)
{
    RSDK_THIS(UIButton);

    if (self->state != UIButton_State_HideHighlight) {
        self->textVisible = false;
        self->highlightVisible = false;
    }

    if (self->textFrames != self->textFrames || self->startListID != self->listID || self->startFrameID != self->frameID
        || self->isDisabled != self->disabled)
    {
        self->textFrames = self->textFrames;
        self->startListID = self->listID;
        self->startFrameID = self->frameID;
        self->isDisabled = self->disabled;
    }

    EntityUIButton* choice = UIButton_GetChoicePtr(self, self->selection);
    if (choice)
        choice->visible = true;

    StateMachine_Run(self->state);

    EntityUIControl* parent = (EntityUIControl*)self->parent;
    if (parent && self->state == UIButton_State_ShowHighlight
        && (parent->state != UIControl_ProcessInputs || parent->buttons[parent->buttonID] != self)) {
        self->isSelected = false;
        UIButton_ButtonLeaveCB();
    }
}

void UIButton_Draw(void)
{
    RSDK_THIS(UIButton);

    Vector2 drawPos;
    int32 width = (self->size.x + self->size.y) >> 16;

    drawPos.x = self->position.x + ScreenInfo->center.x;
    drawPos.y = self->position.y + ScreenInfo->center.y;

    if (self->highlightVisible)
        RSDK.DrawSprite(&self->highlightAnimator, &drawPos, false);

    if (self->textVisible) {

        switch (self->align) {
            case UIBUTTON_ALIGN_LEFT: drawPos.x += -0x60000 - (self->size.x >> 1); break;

            case UIBUTTON_ALIGN_CENTER: break;

            case UIBUTTON_ALIGN_RIGHT:
                drawPos.x -= 0x60000;
                drawPos.x += self->size.x >> 1;
                break;
        }

        if (self->disabled && self->align == UIBUTTON_ALIGN_LEFT)
            drawPos.x += 0x150000;

        RSDK.DrawSprite(&self->animator, &drawPos, false);
    }
}

void UIButton_State_Select(void)
{
    RSDK_THIS(UIButton);

    UIButton_State_ShowHighlight();

    if (++self->timer == 30) {
        self->timer = 0;

        if (!self->transition) {
            StateMachine(actionCB) = UIButton_GetActionCB();
            StateMachine_Run(actionCB);
        }

        self->state = UIButton_State_ShowHighlight;
    }

    self->textVisible = !((self->timer >> 1) & 1);
    self->highlightVisible = true;
}


void UIButton_State_HideHighlight(void)
{
    RSDK_THIS(UIButton);

    self->textVisible = false;
    self->highlightVisible = false;
}

void UIButton_State_ShowHighlight(void)
{
    RSDK_THIS(UIButton);

    self->textVisible = true;
    self->highlightVisible = true;
}