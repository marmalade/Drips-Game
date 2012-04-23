#if !defined(_C_SPRITE_H_)
#define _C_SPRITE_H_

#include "s3e.h"
#include "Iw2D.h"

class CSpriteManager;

//
//
// CSprite - A sprite is the visual representation of an on screen game object
//
// The Update() method is resopnsible for updating the sprites logic whilst the Draw() method is responsible for drawing the sprite
// 
//
class CSprite
{
	/// Properties
protected:
	CSpriteManager* Parent;				// Parent sprite manager
	CIwSVec2	Position;				// Position of the sprite
	iwangle		Angle;					// Rotation of sprite (IW_ANGLE_2PI = 360 degrees)
	iwfixed		Scale;					// Scale of sprite (IW_GEOM_ONE = 1.0)
	CIwColour	Colour;					// Colour of sprite
	bool		Visible;				// Sprites visible state
	CIw2DImage*	Image;					// Bitmapped image that represents this sprite
	int			Width, Height;			// Destination width and height
	int			Type;					// Sprite type
public:
	void		setParent(CSpriteManager* parent) { Parent = parent; }
	void		setPosAngScale(int x, int y, iwangle angle, iwfixed scale)
	{
		Position.x = x;
		Position.y = y;
		Angle = angle;
		Scale = scale;
	}
	void		setPosition(int x, int y)
	{
		Position.x = x;
		Position.y = y;
	}
	CIwSVec2	getPosition() const			{ return Position; }
	void		setAngle(iwangle angle)		{ Angle = angle; }
	iwangle		getAngle() const			{ return Angle; }		
	void		setScale(iwfixed scale)		{ Scale = scale; }
	iwfixed		getScale() const			{ return Scale; }
	void		setColour(CIwColour colour) { Colour = colour; }
	CIwColour	getColour() const			{ return Colour; }
	void		setVisible(bool show)		{ Visible = show; }
	bool		isVisible() const			{ return Visible; }
	void		setImage(CIw2DImage* image)
	{
		Image = image;
		Width = Image->GetWidth();
		Height = Image->GetHeight();
	}
	void		setDestSize(int width, int height)
	{
		Width = width;
		Height = height;
	}
	void		setType(int type)			{ Type = type; }
	int			getType() const				{ return Type; }
	/// Properties End
protected:
	CIwMat2D	Transform;				// Transform

public:
	CSprite() : Image(NULL) { Init(); }
	virtual ~CSprite() {}

	virtual void	Init();				// Called to initialise the sprite, used after construction
	virtual bool	Update();			// Handles the sprites game logic
	virtual void	Draw();				// Draws the sprite
};

//
//
// CSpriteManager - A sprite manager 
//
// The sprite manager managers a collection of sprites, including drawing, tracking and clean up
//
//
class CSpriteManager
{
public:
	// Provide public access to iteration of the sprite list
	typedef CIwList<CSprite*>::iterator	Iterator;
	Iterator		begin() { return Sprites.begin(); }
	Iterator		end()	{ return Sprites.end(); }

	// Properties
protected:
	CIwList<CSprite*>	Sprites;			// List of sprites
public:
	void			addSprite(CSprite* sprite);
	void			removeSprite(CSprite* sprite);
	// Properties End

protected:

public:
	CSpriteManager()	{}
	~CSpriteManager();
	
	void			Update();
	void			Draw();
};





#endif // _C_SPRITE_H_
