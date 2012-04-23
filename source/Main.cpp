// Marmalade headers
#include "s3e.h"
#include "Iw2D.h"
#include "IwResManager.h"

#include "Input.h"
#include "Game.h"

int main()
{
	// Initialise Marmalade 2D graphics system
    Iw2DInit();

	// Initialise the resource manager
	IwResManagerInit();

	// initialise the input system
	g_Input.Init();

	// Initialise the game object
	g_Game.Init();

	// Main Loop
	while (!s3eDeviceCheckQuitRequest())	// Exit main loop if device quit request received
	{
		// Update input system
		g_Input.Update();

		// If back button is pressed then exit the main loop
		if (g_Input.isKeyDown(s3eKeyAbsBSK))
			break;

		// Update the game
		g_Game.Update();

		// Draw the game
		g_Game.Draw();

		// Yield to the operating system
		s3eDeviceYield(0);
	}

	// Clean up game object
	g_Game.Release();

	// Shut down the input system
	g_Input.Release();

	// Shut down the resource manager
	IwResManagerTerminate();

	// Shut down Marmalade 2D graphics system
	Iw2DTerminate();

    return 0;
}

