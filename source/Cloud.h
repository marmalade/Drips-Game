#if !defined(_CLOUD_H_)
#define _CLOUD_H_

#include "s3e.h"
#include "Iw2D.h"

#include "Sprite.h"

//
//
// Cloud - A cloud sprite simply drifts across the screen and wraps around to the other side when it reaches the right hand side of the screen
//
// 
class Cloud : public CSprite
{
	/// Properties
protected:
	CIwSVec2	Velocity;		// Velocity of cloud

public:
	void		setVelocity(int vx, int vy)	{ Velocity.x = vx; Velocity.y = vy; }
	/// Properties End
protected:

public:
	Cloud() : CSprite() {}
	virtual ~Cloud()	{}

	void	Init();				// Initialise the cloud game object
	bool	Update();			// Update our cloud game object
};



#endif // _CLOUD_H_
