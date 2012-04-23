#include "WaterDrop.h"
#include "Game.h"

//
//
// Water drop objects are spawned at the top of the screen fall downwards until they hit the ground or are collected by the player bucket
//
//

//
//
// Bucket implementation
//
//

void WaterDrop::Init()
{
	Destroyed = false;
	Type = ST_WaterDrop;
	Velocity.x = 0;
	Velocity.y = 2 + (rand() * 6) / RAND_MAX;
	Position.x = 20 + (rand() * (Iw2DGetSurfaceWidth() - 40)) / RAND_MAX;
	Position.y = -20;
}

bool WaterDrop::Update()
{
	if (Destroyed)
		return false;	// Tell the sprite manager to remove this water drop

	CSprite::Update();

	Position.x += Velocity.x;
	Position.y += Velocity.y;

	if (Position.y >= Iw2DGetSurfaceHeight() + 20)
	{
		return false;	// Tell the sprite manager to remove this water drop
	}

	return true;

}

