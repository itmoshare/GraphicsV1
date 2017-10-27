#pragma once

#include "windows.h"
#include <glm/glm.hpp>

class Camera
{
public:
	void initialize(HWND hwnd);
	void unInitialize();

	const auto getMainDC() const { return mainDC; }
	const HDC getBackDC() const { return backDC; }

	const auto getSize() const { return size; }

	void setBackBrush(HBRUSH value) { backBrush = value; }

	void beginRender();
	void endRender();

	~Camera();
private:
	HWND hwnd;
	HDC mainDC;
	HDC backDC;

	glm::tvec2<int32_t> size;

	HBRUSH backBrush;
	void fillBackground() const;

};