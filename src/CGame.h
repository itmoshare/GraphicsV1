//
// Created by Dmitriy on 11.10.2017.
//

#ifndef GRAPHICSV1_CGAME_H
#define GRAPHICSV1_CGAME_H

#include "windows.h"
#include "GameObject.h"
#include "Renders/MainRender.h"
#include "GameState.h"
#include "FruitsBuilder.h"

class CGame {
public:

    CGame();

    bool init(HWND hwnd, HINSTANCE hinst); // Init the game application
    void StartLoop(); // Run the game
	void CGame::frameTick();

	void CGame::handleFruitsSpawn(const int32_t frame);
	void CGame::handleFruitsMove();
	void CGame::handleFruitsSpeed(const int32_t frame);

private:
    MainRender render;

    void handleUserInput();
    GameState gameState; // All other game data
	FruitsBuilder fruitsBuilder;

	int32_t frame = 1;
};


#endif //GRAPHICSV1_CGAME_H
