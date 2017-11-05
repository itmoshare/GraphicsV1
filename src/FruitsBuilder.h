#pragma once
#include <string>
#include <vector>
#include <list>
#include "GameState.h"
#include <memory>
#include "Renders/ObjRender.h"

struct FruitDescription
{
	std::string modelPath;
	std::string texturePath;
	glm::vec3 scale;
};

class FruitsBuilder
{
public:
	FruitsBuilder(GameState::GameObjectList &gameObjects, std::vector<FruitDescription> fruitDescriptions);

	void spawnRandomFruit();
	void setMinX(const float value) { minX = value; }
	void setMaxX(const float value) { maxX = value; }

	void setYSpawn(const float value) { ySpawn = value; }
private:
	void spawnFruit(float xPos, FruitDescription fruitDescription);

	float ySpawn = 0;
	float minX = 0;
	float maxX = 1;
	std::vector<FruitDescription> fruitDescriptions;
	GameState::GameObjectList & gameObjects;
};

