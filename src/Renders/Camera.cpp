#include "Camera.h"

void Camera::initialize(HWND hwnd)
{
	this->hwnd = hwnd;
	this->mainDC = GetDC(hwnd);
	this->backDC = CreateCompatibleDC(mainDC);

	RECT clientRect;
	GetClientRect(this->hwnd, &clientRect);
	this->size = glm::tvec2<int32_t>(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);

	this->bitmapInfo = { 0 };
	this->bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	this->bitmapInfo.bmiHeader.biBitCount = 24;
	this->bitmapInfo.bmiHeader.biWidth = size.x;
	this->bitmapInfo.bmiHeader.biHeight = size.y;
	this->bitmapInfo.bmiHeader.biPlanes = 1;
	this->bitmapInfo.bmiHeader.biCompression = 0;

	bytes = new char[3 * size.x * size.y];
}

void Camera::unInitialize()
{
	ReleaseDC(hwnd, mainDC);
}

void Camera::fillBackground() const
{
	RECT rectangle = { 0, 0, size.x, size.y };
	for (int i = 0; i < this->bitmapInfo.bmiHeader.biWidth * this->bitmapInfo.bmiHeader.biHeight * 3; i += 3)
	{
		bytes[i] = 255;
		bytes[i + 1] = 255;
		bytes[i + 2] = 255;
	}
}

void Camera::beginRender()
{
	fillBackground();
}

void Camera::endRender()
{
	SetDIBitsToDevice(mainDC, 0, 0, size.x, size.y, 0, 0, 0, size.y, bytes, &bitmapInfo, DIB_RGB_COLORS);
}

const glm::tvec2<int32_t> Camera::transformGlobalToCamera(glm::tvec2<float> globalCoord) const
{
	return glm::tvec2<int32_t>(globalCoord.x, size.y - globalCoord.y);
}

Camera::~Camera()
{
	unInitialize();
}
