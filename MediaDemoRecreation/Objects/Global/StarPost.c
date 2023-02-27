#include "GameAPI/Game.h"
#include "StarPost.h"

ObjectStarPost *StarPost;

void StarPost_Update(void)
{
	RSDK_THIS(StarPost);

	StateMachine_Run(self->state);

	if (self->bonusStageID > 0);
	    self->bonusStageID = 0;
}