//
// Created by Dmitriy on 11.10.2017.
//

#include <chrono>
#include "CGame.h"
#include "UserInput.h"
#include <thread>
#include <glm/glm.hpp>

// Constructor
CGame::CGame()
{
}

bool CGame::init(HWND hwnd, HINSTANCE hinst)
{
    if(hwnd == NULL || hinst == NULL)
        return false;

    this->render.initialize(hwnd);
	
	auto wndSize = render.getWindowSize();

	gameState.player.getRenderMut().setImagePath("D:/projects/GraphicsV1/images/basket.bmp");
	gameState.player.getRenderMut().setSize(glm::tvec2<float>(50, 24));

	gameState.player.getColliderMut().setLeftDownCornerLocal(glm::tvec2<float>(-25, -12));
	gameState.player.getColliderMut().setRightTopCornerLocal(glm::tvec2<float>(25, 12));

	gameState.player.getTransformMut().setPosition(glm::tvec2<float>(wndSize.x / 2, wndSize.y - gameState.player.getRender().getSize().y / 2));

	gameState.gameOver = false;

    return true;
}

bool LockFrameRate(int frameRate)
{
	static float lastTime = GetTickCount() * 0.001f;
	static float elapsedTime = 0.0f;

	float currentTime = GetTickCount() * 0.001f;	// Get the time (milliseconds = seconds * .001)
	float deltaTime = currentTime - lastTime;		// Get the slice of time
	float desiredFPS = 1.0f / frameRate;			// Store 1 / desiredFrameRate

	elapsedTime += deltaTime;						// Add to the elapsed time
	lastTime = currentTime;							// Update lastTime

													// Check if the time since we last checked is greater than our desiredFPS
	if (elapsedTime > desiredFPS)
	{
		elapsedTime -= desiredFPS; // Adjust our elapsed time
		return true; // Time to draw
	}

	// Still waiting...
	return false;
}

// Run the game -- This is the game loop
void CGame::StartLoop()
{
    MSG msg = {0};

    while(gameState.gameOver == false)
    {
		if (LockFrameRate(60))
		{
			handleUserInput();
			this->render.redraw(gameState);
		}
//        else if(win_obj.lockToFrameRate())
//        {
//            win_obj.clear();
//
//            process(win_obj.getDT());
//            redraw();
//
//            // Draw frame rate
//#ifdef DRAW_FPS
//            win_obj.drawFPS();
//#endif
//
//            win_obj.redraw(); // Draw the back buffer to the screen
//
//            SleepEx(1, true);  // Give OS a little time.  This makes the Task Manager CPU Usage not
//            // spike at 100%.  **NOTE** This lowers overall frame rate and shouldn't
//            // be done in a speed critical application
//        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void CGame::handleUserInput()
{
    if (UserInput::IsKeyDown(VK_UP)){

    } else if (UserInput::IsKeyDown(VK_RIGHT)) {
		if (gameState.player.getCollider().getRightTopCornerGlobal().x < render.getWindowSize().x)
		{
			gameState.player.getTransformMut().movePosition(glm::tvec2<float>(5, 0));
		}
    } else if (UserInput::IsKeyDown(VK_DOWN)) {

    } else if (UserInput::IsKeyDown(VK_LEFT)) {
		if (gameState.player.getCollider().getLeftDownCornerGlobal().x > 0)
		{
			gameState.player.getTransformMut().movePosition(glm::tvec2<float>(-5, 0));
		}
    }

    UserInput::HandleWindowsMessages();
}
