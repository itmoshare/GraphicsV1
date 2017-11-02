#pragma once
#include <string>
#include <vector>
#include <list>
#include "GameState.h"
#include <memory>
#include "Renders/ImagePixelsRender.h"

class FruitsBuilder
{
public:
	FruitsBuilder(GameState::GameObjectList &gameObjects, std::vector<std::string> imagePaths);

	void spawnRandomFruit();
	void setMinX(const float value) { minX = value; }
	void setMaxX(const float value) { maxX = value; }

	void setYSpawn(const float value) { ySpawn = value; }
private:
	void spawnFruit(float xPos, std::string imagePath);

	float ySpawn = 0;
	float minX = 0;
	float maxX = 1;
	std::vector<std::string> imagePaths;
	GameState::GameObjectList & gameObjects;
};

