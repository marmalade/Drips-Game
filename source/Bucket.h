#if !defined(_BUCKET_H_)
#define _BUCKET_H_

#include "s3e.h"
#include "Iw2D.h"

#include "Sprite.h"

//
//
// Bucket - The main buucket object that the player can move around to collect water drops
//
// Bucket is derived from sprite so we can make use of sprites inherent sprite rendering capabilities
//
// 
class Bucket : public CSprite
{
	/// Properties
protected:
public:
	/// Properties End
protected:
	void	DoCollision();

public:
	Bucket() : CSprite() { }
	virtual ~Bucket() {}

	void	Init();				// Initialise the bucket game object
	bool	Update();			// Update the bucket game object
};



#endif // _BUCKET_H_
