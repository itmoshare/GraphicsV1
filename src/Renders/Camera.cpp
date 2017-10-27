#include "Camera.h"

void Camera::initialize(HWND hwnd)
{
	this->hwnd = hwnd;
	this->mainDC = GetDC(hwnd);
	this->backDC = CreateCompatibleDC(mainDC);

	RECT clientRect;
	GetClientRect(this->hwnd, &clientRect);
	this->size = glm::tvec2<int32_t>(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);

	auto bitmap = CreateCompatibleBitmap(mainDC, size.x, size.y);
	SelectObject(backDC, bitmap);
}

void Camera::unInitialize()
{
	ReleaseDC(hwnd, mainDC);
}

void Camera::fillBackground() const
{
	RECT rectangle = { 0, 0, size.x, size.y };
	FillRect(backDC, &rectangle, this->backBrush);
}

void Camera::beginRender()
{
	fillBackground();
}

void Camera::endRender()
{
	BitBlt(mainDC, 0, 0, size.x, size.y, backDC, 0, 0, SRCCOPY);
}

const glm::tvec2<int32_t> Camera::transformGlobalToCamera(glm::tvec2<float> globalCoord) const
{
	return glm::tvec2<int32_t>(globalCoord.x, size.y - globalCoord.y);
}

Camera::~Camera()
{
	unInitialize();
}
