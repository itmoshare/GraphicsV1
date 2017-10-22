#pragma once

#include "../GameState.h"

class CollisionHandler
{
public:
	CollisionHandler(GameState::GameObjectList &gameObjects);
	void handleCollisions();
private:
	GameState::GameObjectList & gameObjects;
};