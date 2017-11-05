//
// Created by Dmitriy on 21.10.2017.
//

#ifndef GRAPHICSV1_GAMESTATE_H
#define GRAPHICSV1_GAMESTATE_H

#include "GameObject.h"
#include <memory>
#include <list>
#include "Renders/Camera.h"

class GameState {
public:
	using GameObjectList = std::list<std::unique_ptr<GameObject>>;
    GameObject player;
	GameObject bottom;
	GameObject hitpoints;
	GameObjectList dropItems;
	
	Camera mainCamera;

	void decLive() 
	{ 
		lives--; 
		if (lives == 0)
			gameOver = true;
	}
	const auto getLives() const { return lives; }

	int32_t lastFruitSpawned = 0;
	int32_t spawnEvery = 120;
	int32_t spawnIncEvery = 300;
	float fallSpeed = 2.0f;
	int32_t fallSpeedIncEvery = 300;
	bool gameOver;
private:
	int32_t lives = 5;
};


#endif //GRAPHICSV1_GAMESTATE_H
