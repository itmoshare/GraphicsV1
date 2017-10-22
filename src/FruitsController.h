#pragma once
#include <string>
#include <vector>
#include <list>
#include "GameState.h"
#include <memory>

class FruitsController
{
public:
	FruitsController(GameState::GameObjectList &gameObjects, std::vector<std::string> imagePaths);

	void spawnRandomFruit();
	void setMinX(const float value) { minX = value; }
	void setMaxX(const float value) { maxX = value; }
private:
	void spawnFruit(float xPos, std::string imagePath);

	float minX = 0;
	float maxX = 1;
	std::vector<std::string> imagePaths;
	GameState::GameObjectList & gameObjects;
};

