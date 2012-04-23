#include "IwResManager.h"
#include "Input.h"

#include "Game.h"
#include "Bucket.h"
#include "WaterDrop.h"
#include "Cloud.h"

//
// Global declaration of the CGame class. Allows global access to the game class
//
CGame g_Game;

//
//
// CGame implementation
//
//
void CGame::Init()
{
	// Allocate the sprite manager
	SpriteManager = new CSpriteManager();

	// Load the resource group that contains our graphics
	IwGetResManager()->LoadGroup("Level1.group");

	// Create images that we can use to render our objects
	background_image	= Iw2DCreateImageResource("background");
	bucket_image		= Iw2DCreateImageResource("bucket");
	water_drop_image	= Iw2DCreateImageResource("water_drop");
	cloud_image			= Iw2DCreateImageResource("cloud");

	// Create the font that is used to display the score
	Font = Iw2DCreateFontResource("trebuchet_12");

	// Get screen dimentions
	int screen_width = Iw2DGetSurfaceWidth();
	int screen_height = Iw2DGetSurfaceHeight();

	// Create background sprite
	CSprite* background_sprite = new CSprite();
	background_sprite->Init();
	background_sprite->setPosAngScale(screen_width / 2, screen_height / 2, 0, IW_GEOM_ONE);
	background_sprite->setImage(background_image);
	background_sprite->setDestSize(screen_width, screen_height);
	SpriteManager->addSprite(background_sprite);

	// Create a bunch of clouds
	Cloud* cloud_sprite = new Cloud();
	cloud_sprite->Init();
	cloud_sprite->setPosAngScale(0, 50, 0, IW_GEOM_ONE);
	cloud_sprite->setImage(cloud_image);
	cloud_sprite->setVelocity(2, 0);
	SpriteManager->addSprite(cloud_sprite);
	cloud_sprite = new Cloud();
	cloud_sprite->Init();
	cloud_sprite->setPosAngScale(200, 150, 0, IW_GEOM_ONE);
	cloud_sprite->setImage(cloud_image);
	cloud_sprite->setVelocity(4, 0);
	SpriteManager->addSprite(cloud_sprite);
	cloud_sprite = new Cloud();
	cloud_sprite->Init();
	cloud_sprite->setPosAngScale(300, 100, 0, IW_GEOM_ONE);
	cloud_sprite->setImage(cloud_image);
	cloud_sprite->setVelocity(3, 0);
	SpriteManager->addSprite(cloud_sprite);

	// Create bucket sprite
	Bucket* bucket_sprite = new Bucket();
	bucket_sprite->Init();
	bucket_sprite->setPosAngScale(screen_width / 2, (screen_height * 3) / 4, 0, IW_GEOM_ONE);
	bucket_sprite->setImage(bucket_image);
	SpriteManager->addSprite(bucket_sprite);

	// Set-up game data
	WaterDropTimer = 10;

}

void CGame::Release()
{
	// Clean-up sprite manager
	if (SpriteManager != NULL)
	{
		delete SpriteManager;
		SpriteManager = NULL;
	}

	// Clean-up font
	if (Font != NULL)
	{
		delete Font;
		Font = NULL;
	}

	// Clean-up shared images
	if (background_image != NULL)
	{
		delete background_image;
		background_image = NULL;
	}
	if (cloud_image != NULL)
	{
		delete cloud_image;
		cloud_image = NULL;
	}
	if (bucket_image != NULL)
	{
		delete bucket_image;
		bucket_image = NULL;
	}
	if (water_drop_image != NULL)
	{
		delete water_drop_image;
		water_drop_image = NULL;
	}
}

void CGame::Update()
{
	// Update the games sprite objects
	SpriteManager->Update();

	// Updaste water drop timer
	WaterDropTimer--;
	if (WaterDropTimer <= 0)
	{
		// Create water drop
		WaterDropTimer = 10;
		WaterDrop* drop_sprite = new WaterDrop();
		drop_sprite->Init();
		drop_sprite->setImage(water_drop_image);
		SpriteManager->addSprite(drop_sprite);
	}
}

void CGame::Draw()
{
	// Clear screen 
	Iw2DSurfaceClear(0xff000000);

	// Draw the games sprite objects
	SpriteManager->Draw();

	// Draw the score text
	DrawScore();

	// Show surface
	Iw2DSurfaceShow();
}

void CGame::updateScore(int amount)
{
	// Adjust score
	Score += amount;
}

void CGame::DrawScore()
{
	// Set the current font
	Iw2DSetFont(Font);

	// Reset the visual transform
	Iw2DSetTransformMatrix(CIwMat2D::g_Identity);

	// Set teh texts colour to black
	Iw2DSetColour(0xff000000);

	// Draw the score label
	Iw2DDrawString("Score:", CIwSVec2(10, 10), CIwSVec2(200, 30), IW_2D_FONT_ALIGN_LEFT, IW_2D_FONT_ALIGN_TOP);

	// Convert the score number to text
	char str[32];
	snprintf(str, 32, "%d", Score);

	// Draw the score number
	Iw2DDrawString(str, CIwSVec2(100, 10), CIwSVec2(200, 30), IW_2D_FONT_ALIGN_LEFT, IW_2D_FONT_ALIGN_TOP);
}


