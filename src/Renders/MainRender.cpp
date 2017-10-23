//
// Created by Dmitriy on 21.10.2017.
//

#include "windows.h"
#include "MainRender.h"

void MainRender::initialize(HWND hwnd)
{
    this->hwnd = hwnd;
    this->hdc = GetDC(hwnd);

    RECT clientRect;
    GetClientRect(this->hwnd, &clientRect);

    this->windowWidth = clientRect.right - clientRect.left;
    this->windowHeight = clientRect.bottom - clientRect.top;
    this->backBrush = CreateSolidBrush(RGB(255, 255, 255));

    this->backbufferDC = CreateCompatibleDC(hdc);
    auto bitmap = CreateCompatibleBitmap(hdc, windowWidth, windowHeight);
    SelectObject(backbufferDC, bitmap);
}

void MainRender::redraw(const GameState & gameState)
{
    beginGraphics();

	gameState.player.getRender()->render(backbufferDC);

	for (auto const &dropItem : gameState.dropItems)
	{
		dropItem->getRender()->render(backbufferDC);
	}

	gameState.livesUI.getRender()->render(backbufferDC);

    endGraphics();
}

void MainRender::beginGraphics()
{
    RECT rectangle = { 0, 0, windowWidth, windowHeight };
    FillRect(backbufferDC, &rectangle, this->backBrush);
}

void MainRender::endGraphics()
{
    BitBlt(hdc, 0, 0, windowWidth, windowHeight, backbufferDC, 0, 0, SRCCOPY);
}
