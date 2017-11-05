//
// Created by Dmitriy on 11.10.2017.
//

#include <chrono>
#include "CGame.h"
#include "UserInput.h"
#include "Renders/UITextRender.h"
#include <thread>
#include <memory>
#include <glm/glm.hpp>
#include <string>
#include "HitpointsController.h"

// Constructor
CGame::CGame() : fruitsBuilder(gameState.dropItems, 
{
	{ "D:/projects/GraphicsV1/objects/Apple/apple.obj", "D:/projects/GraphicsV1/objects/Apple/Maps/skin.bmp", glm::vec3(0.5f, 0.5f, 0.5f) },
	{ "D:/projects/GraphicsV1/objects/Pear/pear.obj", "D:/projects/GraphicsV1/objects/Pear/Grusha_DIFFUSE.bmp", glm::vec3(0.5f, 0.5f, 0.5f) },
})
{
}

bool CGame::init(HWND hwnd, HINSTANCE hinst)
{
	if (hwnd == NULL || hinst == NULL)
		return false;

	gameState.mainCamera.initialize(hwnd);
	gameState.mainCamera.setBackBrush(CreateSolidBrush(RGB(255, 250, 205)));
	auto wndSize = gameState.mainCamera.getSize();
	gameState.mainCamera.setProjectionMatrix(glm::perspective(glm::radians(45.0f), wndSize.x / (float)wndSize.y, 550.0f, 650.0f));
	gameState.mainCamera.setViewMatrix(glm::lookAt(
		glm::vec3(wndSize.x / 2, 200, 600.f),
		glm::vec3(wndSize.x / 2, 200, 0),
		glm::vec3(0, 1, 0)
	));

	auto *playerRender = new ObjRender(gameState.player.getTransformMut());
	playerRender->loadObj("D:/projects/GraphicsV1/objects/Basket/basket.obj");
	playerRender->loadBmp("D:/projects/GraphicsV1/objects/Basket/wicker.bmp");
	playerRender->setScale(glm::vec3(0.5f, 0.5f, 0.5f));

	gameState.player.setRender(std::unique_ptr<IRender>(playerRender));

	gameState.player.getColliderMut().fitSize(glm::tvec2<float>(playerRender->getSize().x, playerRender->getSize().y / 3));
	gameState.player.getTransformMut().setPosition(glm::tvec3<float>(wndSize.x / 2, playerRender->getSize().y / 2, 0));

	gameState.bottom.getTransformMut().setPosition(glm::tvec3<float>(0, -25, 0));
	gameState.bottom.getColliderMut().setLeftDownCornerLocal(glm::tvec2<float>(0, 0));
	gameState.bottom.getColliderMut().setRightTopCornerLocal(glm::tvec2<float>(wndSize.x, 1));
	
	Transform t;
	t.setPosition(glm::vec3(0, 400, 1));
	auto hitPointsRender = new HitpointsController(std::move(t));
	hitPointsRender->init(5);
	gameState.hitpoints.setRender(std::unique_ptr<IRender>(hitPointsRender));
	
	fruitsBuilder.setMinX(50);
	fruitsBuilder.setMaxX((float)wndSize.x - 50);
	fruitsBuilder.setYSpawn((float)wndSize.y + 50);

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
	MSG msg = { 0 };

	while (gameState.gameOver == false)
	{
		if (LockFrameRate(60))
		{
			handleUserInput();
			frameTick();

			gameState.mainCamera.beginRender();
			gameState.player.getRender()->render(gameState.mainCamera);
			for (auto const &dropItem : gameState.dropItems)
			{
				dropItem->getRender()->render(gameState.mainCamera);
			}
			gameState.hitpoints.getRender()->render(gameState.mainCamera);
			gameState.mainCamera.endRender();
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
	if (UserInput::IsKeyDown(VK_UP)) {

	}
	else if (UserInput::IsKeyDown(VK_RIGHT)) {
		if (gameState.player.getCollider().getRightTopCornerGlobal().x < gameState.mainCamera.getSize().x)
		{
			gameState.player.getTransformMut().movePosition(glm::tvec3<float>(7, 0, 0));
		}
	}
	else if (UserInput::IsKeyDown(VK_DOWN)) {

	}
	else if (UserInput::IsKeyDown(VK_LEFT)) {
		if (gameState.player.getCollider().getLeftDownCornerGlobal().x > 0)
		{
			gameState.player.getTransformMut().movePosition(glm::tvec3<float>(-7, 0, 0));
		}
	}

	UserInput::HandleWindowsMessages();
}

void CGame::handleFruitsSpawn(const int32_t frame)
{
	if (frame - gameState.lastFruitSpawned > gameState.spawnEvery)
	{
		fruitsBuilder.spawnRandomFruit();
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
	auto it = gameState.dropItems.begin();
	while (it != gameState.dropItems.end())
	{
		it->get()->getTransformMut().movePosition(glm::tvec3<float>(0, -gameState.fallSpeed, 0));
		auto collider = it->get()->getCollider();
		if (BoxCollider::areIntersect(collider, gameState.player.getCollider()))
		{
			it = gameState.dropItems.erase(it);
			return;
		}
		if (BoxCollider::areIntersect(collider, gameState.bottom.getCollider()))
		{
			it = gameState.dropItems.erase(it);
			gameState.decLive();
			dynamic_cast<HitpointsController*>(gameState.hitpoints.getRenderMut())->dec();
			return;
		}
		it++;
	}
}
