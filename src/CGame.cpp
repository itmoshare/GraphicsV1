//
// Created by Dmitriy on 11.10.2017.
//

#include <chrono>
#include "CGame.h"
#include "UserInput.h"
#include <thread>
#include <memory>
#include <glm/glm.hpp>

// Constructor
CGame::CGame() : fruitsController(gameState.dropItems, {"D:/projects/GraphicsV1/images/fruit_1.bmp"})
{
}

bool CGame::init(HWND hwnd, HINSTANCE hinst)
{
    if(hwnd == NULL || hinst == NULL)
        return false;

    this->render.initialize(hwnd);
	
	auto wndSize = render.getWindowSize();

	gameState.player.getRenderMut().loadImage("D:/projects/GraphicsV1/images/basket.bmp");
	gameState.player.getRenderMut().fitImageSize();

	gameState.player.getColliderMut().fitSize(gameState.player.getRender().getSize());

	gameState.player.getTransformMut().setPosition(glm::tvec2<float>(wndSize.x / 2, wndSize.y - gameState.player.getRender().getSize().y / 2));

	fruitsController.setMinX(0);
	fruitsController.setMaxX((float)wndSize.x);

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
			frameTick();
			this->render.redraw(gameState);
		}
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void CGame::frameTick()
{
	frame++;
	handleFruitsSpeed(frame);
	handleFruitsSpawn(frame);
	handleFruitsMove();
}

void CGame::handleUserInput()
{
    if (UserInput::IsKeyDown(VK_UP)){

    } else if (UserInput::IsKeyDown(VK_RIGHT)) {
		if (gameState.player.getCollider().getRightTopCornerGlobal().x < render.getWindowSize().x)
		{
			gameState.player.getTransformMut().movePosition(glm::tvec2<float>(7, 0));
		}
    } else if (UserInput::IsKeyDown(VK_DOWN)) {

    } else if (UserInput::IsKeyDown(VK_LEFT)) {
		if (gameState.player.getCollider().getLeftDownCornerGlobal().x > 0)
		{
			gameState.player.getTransformMut().movePosition(glm::tvec2<float>(-7, 0));
		}
    }

    UserInput::HandleWindowsMessages();
}

void CGame::handleFruitsSpawn(const int32_t frame)
{
	if (frame - gameState.lastFruitSpawned > gameState.spawnEvery)
	{
		fruitsController.spawnRandomFruit();
		gameState.lastFruitSpawned = frame;
	}
}

void CGame::handleFruitsSpeed(const int32_t frame)
{
	if (frame % gameState.spawnIncEvery == 0)
	{
		gameState.spawnEvery -= 10;
		if (gameState.spawnEvery < 1)
			gameState.spawnEvery = 1;
	}
	if (frame % gameState.fallSpeedIncEvery == 0)
	{
		gameState.fallSpeed += 1;
	}
	//gameState.spawnEvery = (int32_t)round(300 / (pow(frame, 0.2f) + 1));
	//gameState.fallSpeed = gameState.maxFallSpeed / (gameState.maxFallSpeed - frame);
}

void CGame::handleFruitsMove()
{
	for (auto & fruit : gameState.dropItems)
	{
		fruit.get()->getTransformMut().movePosition(glm::tvec2<float>(0, gameState.fallSpeed));
	}
}
