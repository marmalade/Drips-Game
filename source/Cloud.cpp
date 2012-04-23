#include "Cloud.h"
#include "Game.h"

//
//
// Cloud sprites are inert sprites that simply drift across the screen
//
//

//
//
// Bucket implementation
//
//

void Cloud::Init()
{
	Type = ST_None;
	Velocity.x = 0;
	Velocity.y = 0;
}

bool Cloud::Update()
{
	CSprite::Update();

	// Move the cloud
	Position.x += Velocity.x;
	Position.y += Velocity.y;

	// If cloud exits right hand side of screen then wrap it to the left hand side
	if (Position.x >= Iw2DGetSurfaceWidth() + Width)
	{
		Position.x = -Width;
	}

	return true;

}

