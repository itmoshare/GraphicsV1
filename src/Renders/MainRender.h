//
// Created by Dmitriy on 21.10.2017.
//

#ifndef GRAPHICSV1_RENDER_H
#define GRAPHICSV1_RENDER_H


#include "../GameState.h"
#include <glm/glm.hpp>

class MainRender {
public:
	MainRender() = default;
    void initialize(HWND hwnd);

    void redraw(const GameState &gameState);
    void drawPlayer(const Player & player);
    void beginGraphics();
    void endGraphics();

	const auto & getWindowSize() const { return glm::tvec2<int32_t>(windowWidth, windowHeight); }
private:
    HWND hwnd;
    HDC hdc;
    HDC backbufferDC;
    HBRUSH backBrush;
    int32_t windowWidth;
    int32_t windowHeight;
};


#endif //GRAPHICSV1_RENDER_H
