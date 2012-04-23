#if !defined(_C_GAME_H_)
#define _C_GAME_H_

#include "s3e.h"
#include "Iw2D.h"
#include "IwGxFont.h"

#include "Sprite.h"

enum eSpriteType
{
	ST_None, 
	ST_Bucket, 
	ST_WaterDrop, 
};

//
//
// CGame - General game class 
//
// CGame is responsible for updating input, screen and sprites
// 
//

class CGame
{
	/// Properties
protected:
	CSpriteManager*				SpriteManager;					// The sprite manager handles a collection of game sprites
	int							Score;							// Game score
public:
	CSpriteManager*				getSpriteManager()				{ return SpriteManager; }
	void						addSprite(CSprite* sprite)		{ SpriteManager->addSprite(sprite); }
	void						removeSprite(CSprite* sprite)	{ SpriteManager->removeSprite(sprite); }
	void						updateScore(int amount);
	/// Properties End
protected:
	int							WaterDropTimer;

	// Shared images
	CIw2DImage*					background_image;
	CIw2DImage*					bucket_image;
	CIw2DImage*					water_drop_image;
	CIw2DImage*					cloud_image;

	// Font
	CIw2DFont*					Font;

	void	DrawScore();		// Draw the score on screen

public:
	CGame() : SpriteManager(NULL)	{}

	void	Init();				// Initialise the game
	void	Release();			// Release the game
	void	Update();			// Update the game
	void	Draw();				// Draw the game
};

extern CGame g_Game;




#endif // _C_GAME_H_
