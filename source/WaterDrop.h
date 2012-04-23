#if !defined(_WATER_DROP_H_)
#define _WATER_DROP_H_

#include "s3e.h"
#include "Iw2D.h"

#include "Sprite.h"

//
//
// WaterDrop - Water drop objects are spawned at the top of the screen fall downwards until they hit the ground or are collected by the player bucket
//
// 
class WaterDrop : public CSprite
{
	/// Properties
protected:
	bool		Destroyed;		// If true then the water drop will destroy itself
	CIwSVec2	Velocity;		// Velocity of water drop

public:
	void		setVelocity(int vx, int vy)	{ Velocity.x = vx; Velocity.y = vy; }
	void		Destroy()					{ Destroyed = true; }
	/// Properties End
protected:

public:
	WaterDrop() : CSprite() {}
	virtual ~WaterDrop()	{}

	void	Init();				// Initialise the water drop game object
	bool	Update();			// Update our water drop object
};



#endif // _WATER_DROP_H_
