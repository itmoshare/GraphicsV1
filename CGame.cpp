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

// Run the game -- This is the game loop
void CGame::StartLoop()
{
    MSG msg = {0};

    while(gameState.gameOver == false)
    {
        handleUserInput();
        this->render.redraw(gameState);
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
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void CGame::handleUserInput()
{
    if (UserInput::IsKeyDown(VK_UP)){

    } else if (UserInput::IsKeyDown(VK_RIGHT)) {
		if (gameState.player.getCollider().getRightTopCornerGlobal().x < render.getWindowSize().x)
		{
			gameState.player.getTransformMut().movePosition(glm::tvec2<float>(1, 0));
		}
    } else if (UserInput::IsKeyDown(VK_DOWN)) {

    } else if (UserInput::IsKeyDown(VK_LEFT)) {
		if (gameState.player.getCollider().getLeftDownCornerGlobal().x > 0)
		{
			gameState.player.getTransformMut().movePosition(glm::tvec2<float>(-1, 0));
		}
    }

    UserInput::HandleWindowsMessages();
}
